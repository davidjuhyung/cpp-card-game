#ifndef BOARD_H
#define BOARD_H

#include "player.h"

enum class When {Start = 0, End, Play, Death};

class Board
{
private:
  int active = 1;
  std::shared_ptr<Player> player1 = nullptr; // unique_ptr ? since it's exclusively owned by board only. Do we ever share this pointer?
  std::shared_ptr<Player> player2 = nullptr;
public:
  std::shared_ptr<Player> getPlayer(int p);
  void setPlayer(int p, std::shared_ptr<Player> player);
  void startTurn();
  void endturn();
  void attack(int i);
  void attack(int i, int j);
  void play(int i);
  void play(int i, int p, char t);
  void use(int i);
  void use(int i, int p, int t);
  void inspect(int i);
  void display();
  void showHand();
  void APNAP(int playedminion = 0, When when = When::Start);
};


#endif