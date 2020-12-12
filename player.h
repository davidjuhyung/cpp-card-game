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
  int mana;
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
  void play(int i, bool testing = false);
  void play(int i, int p, char t, bool testing = false);
  void use(int i, bool testing = false);
  void use(int i, int p, char t, bool testing = false);
  // testing mode
  void draw();
  void discard(int i);
  std::vector<card_template_t> displayDeck();

  int getPlayerNum();

  void moveToHand(int i);
  void resurrect();
  
  int getLife();
  void damage(int d);

  int getMana();
  void setMana(int m);

  bool hasRitual();
  std::shared_ptr<Ritual> getRitual();
  void setRitual(std::shared_ptr<Ritual> ritual);
  void removeRitual();

  std::shared_ptr<AbstractMinion> getMinion(int i);
  int getNumMinions();
  void addMinion(std::shared_ptr<AbstractMinion> m);
  void replaceMinion(int i, std::shared_ptr<AbstractMinion> m);
  void removeMinion(int i, bool moveToGrave = false);

  bool isGraveyardEmpty();

  // display
  card_template_t display();
  std::vector<card_template_t> displayMinions();
  std::vector<card_template_t> inspectMinion(int i);
  std::vector<card_template_t> displayHand();
  // if graveyard is empty return empty card template
  card_template_t showTopGraveyard();
  // if no ritual is present, return empty card template
  card_template_t showRitual();
};

#endif
