#ifndef CARD_H
#define CARD_H

#include "ascii_graphics.h"
#include <memory>
#include "board.h"
#include "player.h"

class Card
{
  protected:
	 std::string name;
	 Board* board;
	 int cost;
  public:
  	Card(std::string name, Board* board) : name{name}, board{board} {}
  	std::string getName() { return name; }
		int getCost() const { return cost; }
		// all classes that will be derived from should have a virtual or protected destructor, 
    // otherwise deleting an instance via a pointer to a base class results in undefined behavior.
    virtual ~Card() {}
  	// This function is the play method for the card class. It
    // effects the board in some way depending on the type and specification
  	virtual void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) = 0;
    virtual card_template_t displayCard() const = 0;
};

#endif
