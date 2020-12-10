#include "player.h"
#include <sstream>

Player::Player(std::string name, std::vector<std::shared_ptr<Card>> deck)
  : name{name}
  , life{20}
  , magic{3}
  , deck{deck}
  , hand{nullptr}
  , minions{nullptr}
  , graveyard{nullptr}
  , ritual{nullptr}
  {};

// The player gains 1 magic.
// The player draws a card if their deck is non-empty and their hand has less than 5 cards.
void Player::startTurn()
{
  magic++;
  if (deck.size() != 0 && hand.size() < 5) {
    auto deckTopCard = deck.at(deck.size()-1);
    hand.push_back(deckTopCard);
    deck.erase(deck.end());
  }
}

// orders minion i to attack the opposing player o
void Player::attack(int i, int o)
{
  minions.at(i)->attackPlayer(o);
}

// orders the active player’s minion i to attack the opposing player o’s minion t.
void Player::attack(int i, int o, char t)
{
  std::stringstream str;
  str << t;
  int m = t;
  minions.at(i)->attackMinion(o, m);
}

// plays the ith card in the active player’s hand with no target.
void Player::play(int i, int a)
{
  hand.at(i)->play(a, a);
}

// plays the ith card in the active player a’s hand on card t owned by player p. 
// p may be equal to 1 or 2 to represent player 1 or 2 respectively.
// t is either 1, 2, 3, 4, 5 (the ith minion owned by player p) or
// r (the ritual owned by player p). 
// This can be used to play enchantments and spells with targets.
void Player::play(int a, int p, int i, char t)
{
  if (t == 'r') {
    hand.at(i)->play(a, p, 0, true); // true = attack on ritual
    return;
  }
  std::stringstream str;
  str << t;
  int m = t;
  hand.at(i)->play(a, p, m);
}

// i refers to the ith minion owned by the current (active) player, a
// and the command orders that minion to use its activated ability on the provided target (or on no target).
// Using a minion spends one action point and decreases the player’s magic by the ability’s activation cost. 
// Thus, a minion can only be used if they have an action point remaining and the player has enough magic to spend.
void Player::use(int i, int a)
{
  minions[i]->useAbility(a);
}

void Player::use(int i, int a, char t)
{
  std::stringstream str;
  str << t;
  int m = t;
  minions[i]->useAbility(a, m);
}

std::string Player::getName()
{
  return name;
}

std::vector<std::shared_ptr<Card>> Player::getHand()
{
  return hand;
}

std::vector<std::shared_ptr<AbstractMinion>> Player::getMinions()
{
  return minions;
}

std::vector<std::shared_ptr<AbstractMinion>> Player::getGraveyard()
{
  return graveyard;
}

// Any action that would make a minion return to the player’s hand (e.g., Unsummon)
// will instead make the minion vanish from play and be destroyed if the hand is already full.
void Player::moveToHand(int i)
{
  auto minion = minions.at(i);
  minions.erase(minions.begin() + i);
  if (hand.size() != maxHandSize) {
    hand.push_back(minion);
  }
} 

// Resurrect the top minion in your graveyard and set its defence to 1
void Player::resurrect()
{
  auto minion = graveyard.at(graveyard.size()-1);
  graveyard.erase(graveyard.end());
  minions.push_back(minion);
}

int Player::getLife()
{
  return life;
}

void Player::damage(int d)
{
  life -= d;
} 

int Player::getMagic()
{
  return magic;
}

void Player::setMagic(int m)
{
  magic = m;
}

std::shared_ptr<Ritual> Player::getRitual()
{
  return ritual;
}

void Player::setRitual(std::shared_ptr<Ritual> ritual)
{
  this->ritual = ritual;
}

void Player::removeRitual()
{
  ritual = nullptr;
}

std::shared_ptr<AbstractMinion> Player::getMinion(int i)
{
  return minions.at(i);
}

int Player::getNumMinions()
{
  return minions.size();
}

// If all 5 slots are occupied, the minion cannot be played. Minions occupy the leftmost spots on the board, and
// new minions are always added to the right of older minions.
void Player::addMinion(std::shared_ptr<AbstractMinion> m)
{
  minions.push_back(m);
}

void Player::replaceMinion(int i, std::shared_ptr<AbstractMinion> m)
{
  minions.at(i) = m;
}

void Player::removeMinion(int i) {
  minions.erase(minions.begin() + i);
}


