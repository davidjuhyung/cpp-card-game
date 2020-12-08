#ifndef BOARD_H
#define BOARD_H

#include "player.h"

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
  void play(int i, int p, int t);
  void use(int i);
  void use(int i, int p, int t);
  Player* getPlayer(int p);
  void inspect(int i);
  void display();
  void showHand();
};


#endif