#ifndef BOARD_H
#define BOARD_H

#include <memory>
class Player;

enum class When {Start = 0, End, Play, Death};

class Board
{
private:
  int active = 1;
  std::shared_ptr<Player> player1 = nullptr;
  std::shared_ptr<Player> player2 = nullptr;
public:
  Player* getPlayer(int p);
  void setPlayer(std::shared_ptr<Player> player);
  void startTurn();
  void endturn();
  void attack(int i);
  void attack(int i, int t);
  void play(int i);
  void play(int i, int p, char t);
  void use(int i);
  void use(int i, int p, char t);
  void inspect(int i);
  void display();
  void showHand();
  void APNAP(When when = When::Start, int playedMinion = -1);
  // testing mode only
  void draw();
  void discard(int i);
};

#endif
