#ifndef _RITUAL_H_
#define _RITUAL_H_
#include "card.h"

class Ritual : public Card {
	std::string description;
	int activationCost
	int charges;
	int numOfRitualCards;
  public:
  	void play(int player, int minion) override;
	virtual void useAbility(bool startOfPlay, bool minionplayed) = 0;
};



#endif
