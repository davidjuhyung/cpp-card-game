#ifndef BOARD_H
#define BOARD_H

#include "player.h"

class Board
{
private:
  int active;
  std::shared_ptr<Player> player1;
  std::shared_ptr<Player> player2;
public:
  Board(std::shared_ptr<Player>,std::shared_ptr<Player>);
  ~Board(); // I don't think you'll need to implement a dtor
  void endturn();
  void attack(int i);
  void attack(int i, int j);
  void play(int i);
  void play(int i, int p, int t);
  void use(int i);
  void use(int i, int p, int t);
  Player* getPlayer(bool active = true); // if false is passed, return inactive player
  void inspect(int i);
  void display();
  void showHand();
};


#endif