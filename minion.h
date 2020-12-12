#ifndef MINION_H
#define MINION_H

#include "abstractMinion.h"

class Minion : public AbstractMinion
{
  public:
  	Minion(std::string name, Board* board);
  	void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) override;
  	void useAbility(int activePlayer, int target = -1) override;
  	void useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) override;
  	std::shared_ptr<AbstractMinion> getMinion(bool forDisplay = false) override;
  	card_template_t displayCard(bool forInspect = false) override;
  	std::vector<card_template_t> inspectMinion() override;
};

#endif
