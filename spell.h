#ifndef SPELL_H
#define SPELL_H
#include "card.h"

class Spell : public Card {
	std::string description;
	public:
	void play(int player, int minion) override;
};

#endif
