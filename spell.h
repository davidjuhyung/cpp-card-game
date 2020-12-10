#ifndef SPELL_H
#define SPELL_H

#include "player.h"
#include "card.h"
#include "abstractMinion.h"

class Spell : public Card {
	std::string description;
	public:
	Spell(std::string name, Board* board);
	void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) override;
};

#endif
