#ifndef MINION_H
#define MINION_H

#include "abstMin.h"

class Minion public : AbstractMinion {
  public:
  	Minion(std::string name, Board* board);
  	void useAbility(int activeplayer) override;
  	void useTriggered(int activeplayer) override;
};

#endif
