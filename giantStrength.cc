#include "giantStrength.h"

GiantStrength::GiantStrength(std::string name, Board* board) : Enchantment{name,board} {
	enchantmentName = "Giant Strength";
	enchantmentDescription = "";
	cost = 1;
}

void GiantStrength::play(int owner, int targetPlayer, int minion, bool actOnRitual) {
	if (cost > board->getPlayer(owner)->getMagic()) return;
	board->getPlayer(owner)->setMagic(board->getPlayer(owner)->getMagic()-cost);
	auto m = std::make_shared<GiantStrength>(name,board);
	m->minion = board->getPlayer(targetPlayer)->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack()+2;
	m->defence = m->minion->getDefence()+2;
	m->gainAction = m->minion->gaining();
	m->name = m->minion->getName();
	m->activationCost = m->minion->getActivationCost();
	board->getPlayer(targetPlayer)->replaceMinion(minion,m);
}

void GiantStrength::useAbility(int activePlayer, int target) { minion->useAbility(activePlayer,target); }

void GiantStrength::useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) { minion->useTriggered(owner,playedMinion,isOwnerActive,when); }

std::shared_ptr<AbstractMinion> GiantStrength::getMinion() {
	minion->setDefence(minion->getDefence()-2);
	minion->setAttack(minion->getAttack()-2);
	return minion;
}
