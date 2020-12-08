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
  int life;
  int magic;
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
  void attack(int i, int p);
  void attack(int i, int p, char t);
  void play(int i);
  void play(int i, int p, char t);
  void use(int i);
  void use(int i, int p, char t);
  void damage(int d); // reduce life by d
  void incrementMagic(); // increase magic by 1
  std::shared_ptr<AbstractMinion> getMinion(int i);
  std::shared_ptr<Ritual> getRiutal();
  void removeRitual();
  void replaceMinion(int i, std::shared_ptr<AbstractMinion> m);
  void setRitual(std::shared_ptr<Ritual> ritual);
  void addMinion(std::shared_ptr<AbstractMinion> m);
  int numMinions();
  void moveToHand(int i); // ith minion goes back to hand
  void resurrect();
};

#endif
