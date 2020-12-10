#include "board.h"
#include "cardType.h"

std::shared_ptr<Player> Board::getPlayer(int p)
{
  if (p == 1) 
  {
    return player1;
  }
  return player2;
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
  
}

void Board::attack(int i, int j)
{

}

void Board::play(int i)
{

}

void Board::play(int i, int p, int t)
{

}

void Board::use(int i)
{

}

void Board::use(int i, int p, int t)
{

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
    
    }
    else if (n->type == CardType::enchantment)
    {

    }
    else if (n->type == CardType::ritual)
    {

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