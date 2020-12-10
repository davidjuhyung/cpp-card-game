#include "silence.h"

Silence::Silence(std::string name, Board* board) : Enchantment{name, board} {
	enchantmentName = "Silence";
	cost = 1;
}

void Silence::play(int owner, int targetPlayer, int minion, bool actOnRitual) {
    //enchanted minion cannot use ability
    if (cost > board->getPlayer(owner)->getMagic()) return;
    board->getPlayer(owner)->setMagic(board->getPlayer(owner)->getMagic()-cost);
	auto m = std::make_shared<Silence>(name,board);
	m->minion = board->getPlayer(targetPlayer)->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack();
	m->defence = m->minion->getDefence();
	m->gainAction = m->minion->gaining();
	m->name = m->minion->getName();
	m->activationCost = m->minion->getActivationCost();
	board->getPlayer(targetPlayer)->replaceMinion(minion,m);
}

void Silence::useAbility(int activeplayer, int target) {}

void Silence::useTriggered(int owner, int playedminion, bool isOwnerActive, When when) {}
