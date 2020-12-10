#ifndef SILENCE_H
#define SILENCE_H

#include "player.h"
#include "abstractMinion.h"
#include "enchantment.h"

class Silence : public Enchantment {
  public:
	Silence(std::string name = "Silence", Board* board);
	void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) override;
  	void useAbility(int activeplayer, int target = -1) override;
  	void useTriggered(int owner, int playedminion, bool isOwnerActive, When when) override;
};

#endif