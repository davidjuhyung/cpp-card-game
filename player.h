#ifndef PLAYER_H
#define PLAYER_H

#include <string>
// [TODO] include card object

class Player
{
private:
  std::string name;
public:
  player();
  ~player();
  startTurn();
  endTurn();
  attack(int i, Player *p);
  attack(int i, int j, Player *p);
  play(int i);
  play(int i, int j, Player *p);
  use(int i);
  use(int i, int i, Player *p);
};

#endif