#include "giant.h"

GiantStrength::GiantStrength(std::string name = "Giant Strength", Board* board) : Enchantment{name,board}, enchantmentName{"Giant Strength"} {}

void GiantStrength::play(int player, int minion) {
	auto m = std::make_shared<GiantStrength>(name,board);
	m->minion = board->getPlayer(player)->getMinion(minion);
	m->actions = this->minion->getAction();
	m->attack = this->minion->getAttack()+2;
	m->defence = this->minion->getDefence()+2;
	m->gainAction = this->minion->gaining();
	m->name = this->minion->getName();
	board->getPlayer(minion,m);
}

void GiantStrength::useAbility(int activeplayer, int target) { minion->useAbility(activeplayer,target); }

void GiantStrength::useTriggered(int activeplayer, int target) { minion->useTriggered(activeplayer,target); }
