#ifndef _SPELL_H_
#define _SPELL_H_
#include "card.h"

class Spell : public Card {
	std::string description;
	public:
	void play(Board *board, int player, int minion) override;
};


#endif