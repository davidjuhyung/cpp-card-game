#ifndef MINION_H
#define MINION_H

#include "abstractMinion.h"
class Minion : public AbstractMinion
{
  public:
  	Minion(std::string name, Board* board);
  	void useAbility(int activePlayer, int target = -1) override;
  	void useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) override;
  	std::shared_ptr<AbstractMinion> getMinion() const override;
};

#endif
