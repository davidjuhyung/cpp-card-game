#ifndef RITUAL_H
#define RITUAL_H

#include "card.h"
#include "codeForStudents/ascii_graphics.h"
// needs a board class declaration + include for .cc
// needs a player include for .cc
class Ritual : public Card 
{
	private:
		std::string description;
		int activationCost;
		int charges;

  public:
  	Ritual(std::string name, Board* board);
  	void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) override;
  	// if isOwnerActive is false, then the playedMinion is owned by the enemy
	void useAbility(int owner, int playedMinion, bool isOwnerActive, When when);
	int getCharges() const;
	void recharge();
	card_template_t displayCard() const override;
};

#endif
