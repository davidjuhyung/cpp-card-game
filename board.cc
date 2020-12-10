#include "board.h"
#include "cardType.h"

Player* Board::getPlayer(int p)
{
  if (p == 1) 
  {
    return player1.get();
  }
  return player2.get();
}

void Board::setPlayer(int p, std::shared_ptr<Player> player)
{
  if (p == 1) 
  {
    player1 = player;
  } 
  else 
  {
    player2 = player;
  }
}

void Board::startTurn()
{
  auto activePlayer = getPlayer(active);
  activePlayer->startTurn();
  APNAP();
}

void Board::endturn()
{
  APNAP(0, When::End);
}

void Board::attack(int i)
{
  getPlayer(active)->attack(i, active);
}

void Board::attack(int i, int j)
{
  getPlayer(active)->attack(i, j, active); // third param active?
}

void Board::play(int i)
{
  getPlayer(active)->play(i, active);
}

void Board::play(int i, int p, char t)
{
  getPlayer(active)->play(i, p, t);
}

void Board::use(int i)
{
  getPlayer(active)->use(i, active);
}

void Board::use(int i, int p, char t)
{
  getPlayer(active)->play(i, p, t);
}


void Board::inspect(int i)
{

}

void Board::display()
{

}

//   std::vector<std::shared_ptr<Card>> hand;
void Board::showHand()
{
  auto currentPlayer = getPlayer(active);
  auto hand = currentPlayer->getHand();

  for (auto n : hand) 
  {
    std::cout << n->getName() << std::endl; // for debugging
  }

  for (auto n : hand) 
  {
    if (n->type == CardType::minion)
    {
      currentPlayer->getMinion();
    }
    else if (n->type == CardType::enchantment)
    {

    }
    else if (n->type == CardType::ritual)
    {
      currentPlayer->getRitual()
    }
    else if (n->type == CardType::spell)
    {

    }
    else 
    {
      throw;
    }
  }
}

void Board::APNAP(int playedminion = 0, When when = When::Start) 
{
  if (active == 1) {
    for (int i = 1; i <= player1->getNumMinions(); ++i) {
      if (i == playedminion) continue;
      player1->getMinion(i)->useTriggered(1,playedminion,true,when);
    }
    player1->getRitual()->useAbility(1,playedminion,true,when);
    for (int i = 1; i <= player2->getNumMinions(); ++i) player2->getMinion(i)->useTriggered(2,playedminion,false,when);
    player2->getRitual()->useAbility(2,playedminion,false,when);
  } else {
    for (int i = 1; i <= player2->getNumMinions(); ++i) {
      if (i == playedminion) continue;
      player2->getMinion(i)->useTriggered(2,playedminion,true,when);
    }
    player2->getRitual()->useAbility(1,playedminion,true,when);
    for (int i = 1; i <= player1->getNumMinions(); ++i) player1->getMinion(i)->useTriggered(1,playedminion,false,when);
    player1->getRitual()->useAbility(1,playedminion,false,when);
  }
}