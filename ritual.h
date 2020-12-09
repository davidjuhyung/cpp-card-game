#ifndef RITUAL_H
#define RITUAL_H
#include "card.h"

class Ritual : public Card {
	std::string description;
	int activationCost
	int charges;
  public:
  	void play(int player, int minion) override;
	virtual void useAbility(bool startOfPlay, bool minionplayed) = 0;
};



#endif
