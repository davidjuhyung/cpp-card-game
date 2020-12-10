#include "delay.h"

Delay::Delay(std::string name, Board* board) : Enchantment{name,board} {
	enchantmentName = "Delay";
	cost = 1;
}

void Delay::play(int owner, int targetPlayer, int minion, bool actOnRitual) {
	//enchanted minion doesn't gain an action on their next turn. automatically destroyed after 1 turn
	if (cost > board->getPlayer(owner)->getMagic()) return;
	board->getPlayer(owner)->setMagic(board->getPlayer(owner)->getMagic()-cost);
	auto m = std::make_shared<Delay>(name,board);
	m->minion = board->getPlayer(targetPlayer)->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack();
	m->defence = m->minion->getDefence();
	m->gainAction = false;
	m->name = m->minion->getName();
	m->activationCost = m->minion->getActivationCost();
	board->getPlayer(targetPlayer)->replaceMinion(minion,m);
}

void Delay::useAbility(int activeplayer, int target) { minion->useAbility(activeplayer,target); }

void Delay::useTriggered(int owner, int playedminion, bool isOwnerActive, When when) { minion->useTriggered(owner,playedminion,isOwnerActive,when); }
