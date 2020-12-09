#ifndef MINION_H
#define MINION_H

#include "abstMin.h"

class Minion : public AbstractMinion
{
  public:

  	Minion(std::string name, Board* board);

  	void useAbility(int targetplayer, int target = 0) override;

  	void useTriggered(int targetplayer, int target = 0) override;
};

#endif
