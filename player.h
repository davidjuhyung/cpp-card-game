#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
// our libraries
#include "card.h"
#include "abstractMinion.h"
#include "ritual.h"

class Player
{
public:
  static const int maxHandSize = 5;
  static const int maxMinionSize = 5;
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
  void attack(int i, int p);
  void attack(int i, int p, char t);
  void play(int i, int p);
  void play(int a, int i, int p, char t);
  void use(int i, int p);
  void use(int i, int p, char t);

  std::string getName();
  std::vector<std::shared_ptr<Card>> getHand();  
  std::vector<std::shared_ptr<AbstractMinion>> getMinions();
  std::vector<std::shared_ptr<AbstractMinion>> getGraveyard();

  void moveToHand(int i);
  void resurrect();
  
  int getLife();
  void damage(int d);

  int getMagic();
  void setMagic(int m);

  std::shared_ptr<Ritual> getRitual();
  void setRitual(std::shared_ptr<Ritual> ritual);
  void removeRitual();

  std::shared_ptr<AbstractMinion> getMinion(int i);
  int getNumMinions();
  void addMinion(std::shared_ptr<AbstractMinion> m);
  void replaceMinion(int i, std::shared_ptr<AbstractMinion> m);
  void removeMinion(int i);
};

#endif
