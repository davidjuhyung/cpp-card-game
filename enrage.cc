#include "enrage.h"

Enrage::Enrage(std::string name, Board* board) : Enchantment{name,board} {
	enchantmentName = "Enrage";
	cost = 2;
}

void Enrage::play(int owner, int targetPlayer, int minion, bool actOnRitual) {
	if (cost > board->getPlayer(owner)->getMagic()) return;
	board->getPlayer(owner)->setMagic(board->getPlayer(owner)->getMagic()-cost);
	auto m = std::make_shared<Enrage>(name,board);
	m->minion = board->getPlayer(targetPlayer)->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack() + 2;
	m->defence = m->minion->getDefence() - 2;
	m->gainAction = m->minion->gaining();
	m->name = m->minion->getName();
	m->activationCost = m->minion->getActivationCost();
	board->getPlayer(targetPlayer)->replaceMinion(minion,m);
	if (m->defence <= 0) {
		board->APNAP(When::Death);
		board->getPlayer(targetPlayer)->removeMinion(minion,true);
	}
}

void Enrage::useAbility(int activePlayer, int target) { minion->useAbility(activePlayer,target); }

void Enrage::useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) { minion->useTriggered(owner,playedMinion,isOwnerActive,when); }
