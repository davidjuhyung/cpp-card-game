#include "giant.h"

GiantStrength::GiantStrength(std::string name = "Giant Strength", Board* board) : Enchantment{name,board}, enchantmentName{"Giant Strength"}, cost{1} {}

void GiantStrength::play(int player, int minion = 0, bool actOnRitual = false) {
	auto m = std::make_shared<GiantStrength>(name,board);
	m->minion = board->getPlayer(player)->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack()+2;
	m->defence = m->minion->getDefence()+2;
	m->gainAction = m->minion->gaining();
	m->name = m->minion->getName();
	m->activationCost = m->minion->getActivationCost();
	board->getPlayer(player)->replaceMinion(minion,m);
}

void GiantStrength::useAbility(int activeplayer, int target) { minion->useAbility(activeplayer,target); }

void GiantStrength::useTriggered(int owner, int playedminion, bool isOwnerActive, When when) { minion->useTriggered(owner,playedminion,isOwnerActive,when); }
