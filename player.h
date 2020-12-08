#ifndef PLAYER_H
#define PLAYER_H

#include <string>
// [TODO] include card object

class Player
{
public: // will make it public now for testing in main
  std::string name;
public:
  Player(std::string name);
  ~Player();
  void startTurn();
  void endTurn();
  void attack(int i, Player *p);
  void attack(int i, int j, Player *p);
  void play(int i);
  void play(int i, int j, Player *p);
  void use(int i);
  void use(int i, int j, Player *p);
};

#endif