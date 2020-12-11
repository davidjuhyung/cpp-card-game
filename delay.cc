#include "delay.h"

Delay::Delay(std::string name, Board* board) : Enchantment{name,board} {
	enchantmentName = "Delay";
	enchantmentDescription = "Enchanted minion does not gain an action on their next turn. This enchantement is automatically destroyed after 1 turn";
	cost = 1;
}

void Delay::play(int owner, int targetPlayer, int minion, bool actOnRitual) {
	//enchanted minion doesn't gain an action on their next turn. automatically destroyed after 1 turn
	Player* p = board->getPlayer(owner);
	Player* t = board->getPlayer(targetPlayer);
    int magic = p->getMagic();
	if (cost > magic) throw InputException{"Player doesn't have enough magic"};
	int lastMinion = t->getNumMinions()-1;
	if (minion < 0 || minion > lastMinion) throw InputException{"Target doesn't have minion at " + std::to_string(minion+1)};
	auto m = std::make_shared<GiantStrength>(name,board);
	m->minion = t->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack();
	m->defence = m->minion->getDefence();
	m->gainAction = false;
	m->name = m->minion->getName();
	m->activationCost = m->minion->getActivationCost();
	t->replaceMinion(minion,m);
	p->setMagic(magic-cost);
}

void Delay::useAbility(int activePlayer, int target) { minion->useAbility(activePlayer,target); }

void Delay::useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) { minion->useTriggered(owner,playedMinion,isOwnerActive,when); }

std::shared_ptr<AbstractMinion> Delay::getMinion(bool forDisplay) {
	if (minion == nullptr) throw InputException{"Unexpected! Enchantment not attached to a minion"};
	minion->setDefence(defence);
	minion->setAttack(attack);
	return minion;
}
