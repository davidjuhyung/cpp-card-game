#ifndef _SILENCE_H_
#define _SILENCE_H_
#include "enchantment.h"

class Silence : public Enchantment {
  public:
	Silence(Minion* minion);
	void useAbility(bool activated = true) override;
};

#endif
