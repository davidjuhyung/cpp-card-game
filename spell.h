#ifndef _SPELL_H_
#define _SPELL_H_
#include "card.h"

class Spell : public Card {
	std::string description;
	public:
	void play(int player, int minion = 0, bool actOnRitual = false) override;
};

#endif
