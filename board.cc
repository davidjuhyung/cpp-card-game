#include "board.h"
#include "card.h"
#include "player.h"
#include "minion.h"
#include "ritual.h"


// getPlayer and setPlayer will use a loop in the future, but for now this is sufficient.
Player* Board::getPlayer(int p)
{
  if (player1->getPlayerNum() == p) {
    return player1.get();
  }
  return player2.get();
}

void Board::setPlayer(std::shared_ptr<Player> player)
{
  if (player->getPlayerNum() == 1) player1 = player;
  if (player->getPlayerNum() == 2) player2 = player;
}

void Board::startTurn()
{
  auto activePlayer = getPlayer(active);
  activePlayer->startTurn();
  APNAP(When::Start);
}

void Board::endturn()
{
  APNAP(When::End);
}

void Board::attack(int i)
{
  getPlayer(active)->attack(i, active%2+1);
}

void Board::attack(int i, int t)
{
  getPlayer(active)->attack(i, active%2+1, t);
}

void Board::play(int i)
{
  getPlayer(active)->play(active, i);
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
    if (when == When::Start || when == When::End) return;
    for (int i = 0; i < player2->getNumMinions(); ++i) player2->getMinion(i)->useTriggered(2,playedMinion,false,when);
    player2->getRitual()->useAbility(2,playedMinion,false,when);
  } else {
    for (int i = 0; i < player2->getNumMinions(); ++i) {
      if (i == playedMinion) continue;
      player2->getMinion(i)->useTriggered(2,playedMinion,true,when);
    }
    player2->getRitual()->useAbility(1,playedMinion,true,when);
    if (when == When::Start || when == When::End) return;
    for (int i = 0; i < player1->getNumMinions(); ++i) player1->getMinion(i)->useTriggered(1,playedMinion,false,when);
    player1->getRitual()->useAbility(1,playedMinion,false,when);
  }
}

/////// testing mode only ////////
void Board::draw() {
  getPlayer(active)->draw();
}

void Board::discard(int i) {
  getPlayer(active)->discard(i);
}
