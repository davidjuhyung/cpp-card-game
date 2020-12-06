#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "minion.h"
#include "ritual.h"

class Player
{
private:
  std::string name;
  std::vector<std::shared_ptr<Card>> deck;
  std::vector<std::shared_ptr<Card>> hand;
  std::vector<std::shared_ptr<AbstractMinion>> minions;
  std::vector<std::shared_ptr<AbstractMinion>> graveyard;
  std::shared_ptr<Ritual> ritual;
public:
  Player(std::string name);
  ~Player(); // I don't think you'll need to implement a dtor
  void startTurn();
  void endTurn();
  void attack(int i, Player *p);
  void attack(int i, int j, Player *p);
  void play(int i);
  void play(int i, int j, Player *p);
  void use(int i);
  void use(int i, int j, Player *p);
  Minion* getMinion(int i);
  Ritual* getRiutal();
  void setRitual(std::shared_ptr<Ritual> ritual);
  void moveToHand(int i); // ith minion goes back to hand
  void resurrect();
};

#endif
