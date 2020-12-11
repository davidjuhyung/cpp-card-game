#ifndef SPELL_H
#define SPELL_H

#include "card.h"
// needs a bord class declaration and the include in .cc
// needs a player include in .cc
class Spell : public Card 
{
	private:
		std::string description;
	public:	
		Spell(std::string name, Board* board);	
		void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) override;
		card_template_t displayCard() const override;
};

#endif
