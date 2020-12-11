#include "enrage.h"

Enrage::Enrage(std::string name, Board* board) : Enchantment{name,board} {
	enchantmentName = "Enrage";
	enchantmentDescription = "";
	cost = 2;
}

void Enrage::play(int owner, int targetPlayer, int minion, bool actOnRitual) {
	Player* p = board->getPlayer(owner);
	Player* t = board->getPlayer(targetPlayer);
    int magic = p->getMagic();
	if (cost > magic) throw InputException{"Player doesn't have enough magic"};
	int lastMinion = t->getNumMinions()-1;
	if (minion < 0 || minion > lastMinion) throw InputException{"Target doesn't have minion at " + std::to_string(minion+1)};
	auto m = std::make_shared<Enrage>(name,board);
	m->minion = t->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack()*2;
	m->defence = m->minion->getDefence()-2;
	m->gainAction = m->minion->gaining();
	m->name = m->minion->getName();
	m->activationCost = m->minion->getActivationCost();
	t->replaceMinion(minion,m);
	p->setMagic(magic-cost);
	if (m->defence <= 0) {
		board->APNAP(When::Death);
		t->removeMinion(minion,true);
	}
}

void Enrage::useAbility(int activePlayer, int target) { minion->useAbility(activePlayer,target); }

void Enrage::useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) { minion->useTriggered(owner,playedMinion,isOwnerActive,when); }

std::shared_ptr<AbstractMinion> Enrage::getMinion(bool forDisplay) {
	if (minion == nullptr) throw InputException{"Unexpected! Enchantment not attached to a minion"};
	if (forDisplay) {
		minion->setDefence(defence);
		minion->setAttack(attack);
	} else {
		minion->setDefence(defence+2);
		minion->setAttack(attack/2);
	}
	return minion;
}
