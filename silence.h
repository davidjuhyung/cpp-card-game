#ifndef _SILENCE_H_
#define _SILENCE_H_
#include "enchantment.h"

class Silence : public Enchantment {
  public:
	Silence(std::string name = "Silence", Board* board);
	void useAbility(int activePlayer, int minion) override;
};

#endif
