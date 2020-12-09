#ifndef SILENCE_H
#define SILENCE_H
#include "enchantment.h"

class Silence : public Enchantment {
  public:
	Silence(std::string name = "Silence", Board* board);
	void play(int player, int minion) override;
  	void useAbility(int activeplayer, int target) override;
  	void useTriggered(int activeplayer, int target) override;
};

#endif
