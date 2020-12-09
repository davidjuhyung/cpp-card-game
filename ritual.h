#ifndef RITUAL_H
#define RITUAL_H

#include "card.h"

class Ritual : public Card {
	std::string description;
	int activationCost;
	int charges;
  public:
  	void play(int player, int minion = 0, bool actOnRitual = false) override; //when it is played on the board
	void useAbility(int player, int playedMinion = 0, bool actOnRitual = false, When when = When::Start); //when it is used/triggered
	int getCharges(); //return charges
};

#endif
