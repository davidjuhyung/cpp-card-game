#include "delay.h"

Delay::Delay(std::string name = "Delay", Board* board) : Enchantment{name,board}, enchantmentName{"Delay"} {}

void Delay::play(int player, int minion = 0, bool actOnRitual = false) {
	auto m = std::make_shared<Delay>(name,board);
	m->minion = board->getPlayer(player)->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack();
	m->defence = m->minion->getDefence();
	m->gainAction = m->minion->gaining();
	m->name = m->minion->getName();
	board->getPlayer(player)->replaceMinion(minion,m);
}

void Delay::useAbility(int targetplayer, int target) { minion->useAbility(targetplayer,target); }

void Delay::useTriggered(int targetplayer, int target) { minion->useTriggered(targetplayer,target); }
