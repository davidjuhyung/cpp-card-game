#include "silence.h"

Silence::Silence(std::string name = "Silence", Board* board) : Enchantment{name, board}, enchantmentName{"Silence"} {}
}

void Silence::play(int player, int minion) {
    //enchanted minion cannot use ability
	auto m = std::make_shared<Silence>(name,board);
	m->minion = board->getPlayer(player)->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack();
	m->defence = m->minion->getDefence();
	m->gainAction = m->minion->gaining();
	m->name = m->minion->getName();
	m->activationCost = m->minion->getActivationCost();
	board->getPlayer(player)->replaceMinion(minion,m);
}

void Silence::useAbility(int activeplayer, int target) {}

void Silence::useTriggered(int activeplayer, int target) {}
