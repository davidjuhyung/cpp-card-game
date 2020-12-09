#ifndef PLAYER_H
#define PLAYER_H

#include <string>
// our libraries
#include "card.h"
#include "abstractMinion.h"

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
  Player(std::string name, std::vector<std::shared_ptr<Card>> deck);
  void startTurn();
  void endTurn();
  void attack(int i, int p);
  void attack(int i, int p, char t);
  void play(int i, int p);
  void play(int i, int p, char t);
  void use(int i, int p);
  void use(int i, int p, char t);

  void getName();

  void moveToHand(int i);  // ith minion goes back to hand
  void resurrect();
  
  void getLife();
  void damage(int d); // decrease life by d

  int getMagic();
  void setMagic(int m)

  std::shared_ptr<Ritual> getRiutal();
  void setRitual(std::shared_ptr<Ritual> ritual);
  void removeRitual();

  std::shared_ptr<AbstractMinion> getMinion(int i);
  int getNumMinions();
  void addMinion(std::shared_ptr<AbstractMinion> m);
  void replaceMinion(int i, std::shared_ptr<AbstractMinion> m);
  void removeMinion(int i);
};

#endif