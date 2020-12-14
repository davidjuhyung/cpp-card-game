#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <iostream>

class Player;

enum class When {Start = 0, End, Play, Death};

class Board
{
private:
  std::unique_ptr<Player> player1 = nullptr;
  std::unique_ptr<Player> player2 = nullptr;
public:
  int active = 1;
  Player* getPlayer(int p);
  void setPlayer(std::unique_ptr<Player> player);
  void startTurn();
  void endturn();
  void attack(int i);
  void attack(int i, int t);
  void play(int i, bool testing = false);
  void play(int i, int p, char t, bool testing = false);
  void use(int i, bool testing = false);
  void use(int i, int p, char t, bool testing = false);
  void inspect(int i, std::ostream &out = std::cout);
  void display(std::ostream &out = std::cout);
  void showHand(std::ostream &out = std::cout);
  void APNAP(When when = When::Start, int playedMinion = -1);
  // testing mode only
  void draw();
  void discard(int i);
  void displayPlayerDeck();
};

#endif
