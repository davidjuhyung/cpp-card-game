#ifndef SPELL_H
#define SPELL_H

#include "card.h"

class Spell : public Card {
	std::string description;
	public:
	void play(int player, int minion = 0, bool actOnRitual = false) override;
};

#endif
