#include "giant.h"

GiantStrength::GiantStrength(std::string name = "Giant Strength", Board* board) : Enchantment{name,board}, enchantmentName{"Giant Strength"} {}

void GiantStrength::play(int player, int minion) {
	auto m = std::make_shared<GiantStrength>(name,board);
	m->minion = board->getPlayer(player)->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack()+2;
	m->defence = m->minion->getDefence()+2;
	m->gainAction = m->minion->gaining();
	m->name = m->minion->getName();
	board->getPlayer(minion,m);
}

void GiantStrength::useAbility(int activeplayer, int target) { minion->useAbility(activeplayer,target); }

void GiantStrength::useTriggered(int activeplayer, int target) { minion->useTriggered(activeplayer,target); }
