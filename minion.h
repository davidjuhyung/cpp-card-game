#ifndef MINION_H
#define MINION_H

#include "abstractMinion.h"

class Minion : public AbstractMinion
{
  public:

  	Minion(std::string name, Board* board);

  	void useAbility(int activeplayer, int target = 0, bool turn) override;

  	void useTriggered(int owner, int playedminion, bool isOwnerActive, When when) override;
};

#endif
