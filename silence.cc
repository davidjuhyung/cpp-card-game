#include "silence.h"

Silence::Silence(std::string name, Board* board) : Enchantment{name, board} {
	enchantmentName = "Silence";
	enchantmentDescription = "Enchanted minion cannot use abilities";
	cost = 1;
}

void Silence::play(int owner, int targetPlayer, int minion, bool actOnRitual) {
	//enchanted minion cannot use ability
	Player* p = board->getPlayer(owner);
	Player* t = board->getPlayer(targetPlayer);
    int magic = p->getMagic();
	if (cost > magic) throw InputException{"Player doesn't have enough magic"};
	int lastMinion = t->getNumMinions()-1;
	if (minion < 0 || minion > lastMinion) throw InputException{"Target doesn't have minion at " + std::to_string(minion+1)};
	auto m = std::make_shared<Silence>(name,board);
	m->minion = t->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack();
	m->defence = m->minion->getDefence();
	m->gainAction = m->minion->gaining();
	m->name = m->minion->getName();
	m->activationCost = m->minion->getActivationCost();
	t->replaceMinion(minion,m);
	p->setMagic(magic-cost);
}

void Silence::useAbility(int activePlayer, int target) {}

void Silence::useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) {}

std::shared_ptr<AbstractMinion> Silence::getMinion(bool forDisplay) {
	if (minion == nullptr) throw InputException{"Unexpected! Enchantment not attached to a minion"};
	minion->setDefence(defence);
	minion->setAttack(attack);
	return minion;
}
