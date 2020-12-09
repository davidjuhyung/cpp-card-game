#ifndef BOARD_H
#define BOARD_H

#include "player.h"

enum class When {Start = 0, End, Play, Death};

class Board
{
private:
  int active = 1;
  std::shared_ptr<Player> player1 = nullptr;
  std::shared_ptr<Player> player2 = nullptr;
public:
  void setPlayer(int player, std::shared_ptr<Player> player);
  void endturn();
  void attack(int i);
  void attack(int i, int j);
  void play(int i);
  void play(int i, int p, char t);
  void use(int i);
  void use(int i, int p, int t);
  Player* getPlayer(int p);
  void inspect(int i);
  void display();
  void showHand();

  void APNAP(int playedminion = 0, When when = When::Start) {
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
};


#endif