#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "codeForStudents/ascii_graphics.h"

class Card;
class AbstractMinion;
class Ritual;

class Player
{
public:
  static const int maxHandSize = 5;
  static const int maxMinionSize = 5;
private:
  int playerNum;
  std::string name;
  int life;
  int magic;
  std::vector<std::shared_ptr<Card>> deck;
  std::vector<std::shared_ptr<Card>> hand;
  std::vector<std::shared_ptr<AbstractMinion>> minions;
  std::vector<std::shared_ptr<AbstractMinion>> graveyard;
  std::shared_ptr<Ritual> ritual = nullptr;

public:
  Player(int playerNum, std::string name, std::vector<std::shared_ptr<Card>> deck);
  // i = ith minion
  // o = opposing player
  // a = active player
  // t = target minion or ritual
  // p = target player
  void startTurn();
  void attack(int i, int o);
  void attack(int i, int o, int t);
  void play(int a, int i);
  void play(int a, int i, int p, char t);
  void use(int i, int p);
  void use(int i, int p, char t);
  card_template_t display();
  std::vector<card_template_t> displayMinions();
  std::vector<card_template_t> inspectMinion(int i);
  std::vector<card_template_t> displayHand();
  // if graveyard is empty return empty card template
  card_template_t showTopGraveyard();
  // if no ritual is present, return empty card template
  card_template_t showRitual();

  int getPlayerNum();
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

  bool hasRitual();
  std::shared_ptr<Ritual> getRitual();
  void setRitual(std::shared_ptr<Ritual> ritual);
  void removeRitual();

  std::shared_ptr<AbstractMinion> getMinion(int i);
  int getNumMinions();
  void addMinion(std::shared_ptr<AbstractMinion> m);
  void replaceMinion(int i, std::shared_ptr<AbstractMinion> m);
  void removeMinion(int i, bool moveToGrave = false);

  // testing mode
  void draw();
  void discard(int i);
};

#endif
