#include "enrage.h"

Enrage::Enrage(std::string name = "Enrage", Board* board) : Enchantment{name,board}, enchantmentName{"Enrage"} {}

void Enrage::play(int player, int minion = 0, bool actOnRitual = false) {
	auto m = std::make_shared<Enrage>(name,board);
	m->minion = board->getPlayer(player)->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack() + 2;
	m->defence = m->minion->getDefence() - 2;
	m->gainAction = m->minion->gaining();
	m->name = m->minion->getName();
	m->activationCost = m->minion->getActivationCost();
	board->getPlayer(player)->replaceMinion(minion,m);
}

void Enrage::useAbility(int targetplayer, int target) { minion->useAbility(targetplayer,target); }

void Enrage::useTriggered(int targetplayer, int target) { minion->useTriggered(targetplayer,target); }
