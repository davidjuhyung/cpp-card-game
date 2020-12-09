#ifndef SPELL_H
#define SPELL_H

#include "player.h"
#include "card.h"
#include "abstractMinion.h"

class Spell : public Card {
	std::string description;
	public:
	void play(int player, int minion = 0, bool actOnRitual = false) override;
};

#endif
