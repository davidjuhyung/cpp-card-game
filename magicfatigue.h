#ifndef _MAGICFATIGUE_H_
#define _MAGICFATIGUE_H_
#include "enchantment.h"

#include 
class MagicFatigue : public Enchantment {
	
  public:
	MagicFatigue(Minion* minion);
	void useAbility(bool activated = true) override;
};

#endif
