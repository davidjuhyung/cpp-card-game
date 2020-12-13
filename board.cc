#include "board.h"
#include "card.h"
#include "player.h"
#include "minion.h"
#include "ritual.h"
#include "inputException.h"
#include <iostream>


// getPlayer and setPlayer will use a loop in the future, but for now this is sufficient.
Player* Board::getPlayer(int p)
{
  if (player1->getPlayerNum() == p) {
    return player1.get();
  }
  return player2.get();
}

void Board::setPlayer(std::unique_ptr<Player> player)
{
  if (player->getPlayerNum() == 1) player.swap(player1);
  else if (player->getPlayerNum() == 2) player.swap(player2);
}

void Board::startTurn()
{
  auto activePlayer = getPlayer(active);
  activePlayer->startTurn();
  APNAP();
}

void Board::endturn()
{
  APNAP(When::End);
  active = active % 2 + 1;
  startTurn();
}

// orders minion i to attack the opposing player
void Board::attack(int i)
{
  getPlayer(active)->attack(i-1, active%2+1);
}

// orders the active player’s minion i to attack the opposing player’s minion t.
void Board::attack(int i, int t)
{
  getPlayer(active)->attack(i-1, active%2+1, t-1);
}

// plays the ith card in the active player’s hand with no target.
void Board::play(int i, bool testing)
{
  getPlayer(active)->play(i-1, testing);
}

// plays the ith card in the active player’s hand on card t owned by player p. 
// p may be equal to 1 or 2 to represent player 1 or 2 respectively.
// t is either 1, 2, 3, 4, 5 (the ith minion owned by player p) or
// r (the ritual owned by player p). 
void Board::play(int i, int p, char t, bool testing)
{
  getPlayer(active)->play(i-1, p, t, testing);
}

// i refers to the ith minion owned by the current player
// and the command orders that minion to use its activated ability on the provided target (or on no target).
void Board::use(int i, bool testing)
{
  getPlayer(active)->use(i-1, testing);
}

void Board::use(int i, int p, char t, bool testing)
{
  getPlayer(active)->use(i-1, p, t, testing);
}

/////// testing mode only ////////

// draws a card if their deck is non-empty and their hand has less than 5 cards.
void Board::draw() {
  getPlayer(active)->draw();
}

// discards the ith card in the player’s hand, simply removing it from their hand and destroying it.
void Board::discard(int i) {
  auto player = getPlayer(active);
  if (i >= 1 && i <= player->maxHandSize) {
    getPlayer(active)->discard(i-1);
  } else {
    throw InputException("the paramater must be between 1 and " + std::to_string(player->maxHandSize));
  }
}

void Board::inspect(int i)
{
  std::vector<card_template_t> m = getPlayer(active)->inspectMinion(i-1);
  int numEnchantments = m.size() - 1;
  if (numEnchantments < 0) return;
  card_template_t card = m.at(0);
  int cardSize = card.size();
  for (auto line : card) std::cout << line << std::endl;
  int numLines = numEnchantments / 5;
  if (numEnchantments%5 != 0) numLines++;
  for (int f = 0; f < numLines; ++f) {
    for (int j = 0; j < cardSize; ++j) {
      for (int k = 1; k <= 5; ++k) {
        if (k+f*5 > numEnchantments) break;
        std::cout << m.at(k+f*5).at(j);
      }
      std::cout << std::endl;
    }
  }
}

void Board::display()
{
  const int width = CARD_TEMPLATE_EMPTY.at(0).length();
  const int height = CARD_TEMPLATE_EMPTY.size();
  std::cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
  for (int i = 0; i < 5*width; ++i) std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  std::cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;

  card_template_t ritual1 = getPlayer(1)->showRitual();
  card_template_t ritual2 = getPlayer(2)->showRitual();
  card_template_t grave1 = getPlayer(1)->showTopGraveyard();
  card_template_t grave2 = getPlayer(2)->showTopGraveyard();
  card_template_t p1 = getPlayer(1)->display();
  card_template_t p2 = getPlayer(2)->display();
  std::vector<card_template_t> minions1 = getPlayer(1)->displayMinions();
  int numMinions1 = minions1.size();
  std::vector<card_template_t> minions2 = getPlayer(2)->displayMinions();
  int numMinions2 = minions2.size();

  for (int i = 0; i < height; ++i) {
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    for (int j = 0; j < 5; ++j) {
      if (j == 0) std::cout << grave1.at(i);
      else if (j == 2) std::cout << p1.at(i);
      else if (j == 4) std::cout << ritual1.at(i);
      else for (int empty = 0; empty < width; empty++) std::cout << " ";
    }
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    std::cout << std::endl;
  }
  for (int i = 0; i < height; ++i) {
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    for (int j = 0; j < 5; ++j) {
      if (j+1 > numMinions1) std::cout << CARD_TEMPLATE_BORDER.at(i);
      else std::cout << minions1.at(j).at(i);
    }
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    std::cout << std::endl;
  }

  for (auto line : CENTRE_GRAPHIC) std::cout << line << std::endl;;

  for (int i = 0; i < height; ++i) {
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    for (int j = 0; j < 5; ++j) {
      if (j+1 > numMinions2) std::cout << CARD_TEMPLATE_BORDER.at(i);
      else std::cout << minions2.at(j).at(i);
    }
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    std::cout << std::endl;
  }
  for (int i = 0; i < height; ++i) {
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    for (int j = 0; j < 5; ++j) {
      if (j == 4) std::cout << grave2.at(i);
      else if (j == 2) std::cout << p2.at(i);
      else if (j == 0) std::cout << ritual2.at(i);
      else for (int empty = 0; empty < width; empty++) std::cout << " ";
    }
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    std::cout << std::endl;
  }
  std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
  for (int i = 0; i < 5*width; ++i) std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;
}

//   std::vector<std::shared_ptr<Card>> hand;
void Board::showHand()
{ 
  std::vector<card_template_t> m = getPlayer(active)->displayHand();
  int num = m.size();
  if (num == 0) return; // This is not possible so remove this line if you want
  card_template_t card = m.at(0);
  int cardSize = card.size();
  for (int j = 0; j < cardSize; ++j) {
    for (int k = 0; k < num; ++k) {
      std::cout << m.at(k).at(j);
    }
    std::cout << std::endl;
  }
}

void Board::APNAP(When when, int playedMinion) 
{
  if (active == 1) {
    for (int i = 0; i < player1->getNumMinions(); ++i) {
      if (i == playedMinion) continue;
      player1->getMinion(i)->useTriggered(1,playedMinion,true,when);
    }
    if (player1->hasRitual()) player1->getRitual()->useAbility(1,playedMinion,true,when);
    if (when == When::Start || when == When::End) return;
    for (int i = 0; i < player2->getNumMinions(); ++i) player2->getMinion(i)->useTriggered(2,playedMinion,false,when);
    if (player2->hasRitual()) player2->getRitual()->useAbility(2,playedMinion,false,when);
  } else {
    for (int i = 0; i < player2->getNumMinions(); ++i) {
      if (i == playedMinion) continue;
      player2->getMinion(i)->useTriggered(2,playedMinion,true,when);
    }
    if (player2->hasRitual()) player2->getRitual()->useAbility(1,playedMinion,true,when);
    if (when == When::Start || when == When::End) return;
    for (int i = 0; i < player1->getNumMinions(); ++i) player1->getMinion(i)->useTriggered(1,playedMinion,false,when);
    if (player1->hasRitual()) player1->getRitual()->useAbility(1,playedMinion,false,when);
  }
}

void Board::displayPlayerDeck() {
  std::vector<card_template_t> m = getPlayer(active)->displayDeck();
  int num = m.size();
  int numLines = num/5;
  if (num%5 != 0) ++numLines;
  if (num == 0) return; // This is not possible so remove this line if you want
  card_template_t card = m.at(0);
  int cardSize = card.size();
  for (int f = 0; f < numLines; ++f) {
    for (int j = 0; j < cardSize; ++j) {
      for (int k = 0; k < 5; ++k) {
        if (k+f*5 >= num) break;
        std::cout << m.at(k+f*5).at(j);
      }
      std::cout << std::endl;
    }
  }
}
