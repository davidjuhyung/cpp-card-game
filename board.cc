#include "board.h"
#include "card.h"
#include "player.h"
#include "minion.h"
#include "ritual.h"

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
  APNAP(When::Start);
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
  getPlayer(active)->play(active, i, p, t);
}

void Board::use(int i)
{
  getPlayer(active)->use(i, active);
}

void Board::use(int i, int p, char t)
{
  getPlayer(active)->use(i, p, t);
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

}

void Board::APNAP(When when, int playedMinion) 
{
  if (active == 1) {
    for (int i = 0; i < player1->getNumMinions(); ++i) {
      if (i == playedMinion) continue;
      player1->getMinion(i)->useTriggered(1,playedMinion,true,when);
    }
    player1->getRitual()->useAbility(1,playedMinion,true,when);
    for (int i = 0; i < player2->getNumMinions(); ++i) player2->getMinion(i)->useTriggered(2,playedMinion,false,when);
    player2->getRitual()->useAbility(2,playedMinion,false,when);
  } else {
    for (int i = 0; i < player2->getNumMinions(); ++i) {
      if (i == playedMinion) continue;
      player2->getMinion(i)->useTriggered(2,playedMinion,true,when);
    }
    player2->getRitual()->useAbility(1,playedMinion,true,when);
    for (int i = 0; i < player1->getNumMinions(); ++i) player1->getMinion(i)->useTriggered(1,playedMinion,false,when);
    player1->getRitual()->useAbility(1,playedMinion,false,when);
  }
}
