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
  void startTurn();
  void endTurn();

  // in all the below functions p is the target player, the param is handled by main
  void attack(int i, int p);
  void attack(int i, int p, char t);
  void play(int i, int p);
  void play(int i, int p, char t);
  void use(int i, int p);
  void use(int i, int p, char t);

  // reduce life by d
  void damage(int d);

  // increase magic by 1
  void incrementMagic();

  std::shared_ptr<AbstractMinion> getMinion(int i);

  std::shared_ptr<Ritual> getRiutal();

  void removeRitual();

  void replaceMinion(int i, std::shared_ptr<AbstractMinion> m);

  void setRitual(std::shared_ptr<Ritual> ritual);

  void addMinion(std::shared_ptr<AbstractMinion> m);

  int numMinions();

  // ith minion goes back to hand
  void moveToHand(int i);
  
  void resurrect();
};

#endif
