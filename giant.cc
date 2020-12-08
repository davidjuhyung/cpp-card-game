#include "giant.h"

GiantStrength::GiantStrength(std::string name = "Giant Strength", Board* board) : Enchantment{name,board} {}

void GiantStrength::play(int player, int minion) {
	this->minion = board->getPlayer(player)->getMinion(minion);
	actions = this->minion->getAction();
	attack = this->minion->getAttack();
	defence = this->minion->getDefence();
	gainAction = this->minion->gaining();
	name = this->minion->getName();
}

void GiantStrength::useAbility(int activeplayer) {
	
}
