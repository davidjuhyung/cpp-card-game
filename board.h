#ifndef BOARD_H
#define BOARD_H

class Board
{
private:
  /* data */
public:
  Board(/* args */);
  ~Board();
  void endturn();
  void attack(int i);
  void attack(int i, int j);
  void play(int i);
  void play(int i, int p, int t);
  void use(int i);
  void use(int i, int p, int t);
  void inspect(int i);
  void display();
  void showHand();
};


#endif