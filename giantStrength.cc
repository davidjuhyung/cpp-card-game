#include "giantStrength.h"

GiantStrength::GiantStrength(std::string name, Board* board) : Enchantment{name,board} {
	enchantmentName = "Giant Strength";
	enchantmentDescription = "";
	cost = 1;
}

void GiantStrength::play(int owner, int targetPlayer, int minion, bool actOnRitual) {
	Player* p = board->getPlayer(owner);
	Player* t = board->getPlayer(targetPlayer);
    int mana = p->getMana();
	if (cost > mana) throw InputException{"Player doesn't have enough mana"};
	int lastMinion = t->getNumMinions()-1;
	if (minion < 0) throw InputException{"Please specify a target to play this card"};
	if (minion > lastMinion) throw InputException{"Target doesn't have minion at " + std::to_string(minion+1)};
	auto m = std::make_shared<GiantStrength>(name,board);
	m->minion = t->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack()+2;
	m->defence = m->minion->getDefence()+2;
	m->gainAction = m->minion->gaining();
	m->name = m->minion->getName();
	m->activationCost = m->minion->getActivationCost();
	t->replaceMinion(minion,m);
	p->setMana(mana-cost);
}

void GiantStrength::useAbility(int activePlayer, int targetPlayer, int minion) { this->minion->useAbility(activePlayer,targetPlayer,minion); }

void GiantStrength::useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) { minion->useTriggered(owner,playedMinion,isOwnerActive,when); }

std::shared_ptr<AbstractMinion> GiantStrength::getMinion(bool forDisplay) {
	if (minion == nullptr) throw InputException{"Unexpected! Enchantment not attached to a minion"};
	if (forDisplay) {
		minion->setDefence(defence);
		minion->setAttack(attack);
	} else {
		minion->setDefence(defence-2);
		minion->setAttack(attack-2);
	}
	minion->setCurrentAction(actions);
	minion->setActivationCost(activationCost);
	minion->setGaining(gainAction);
	return minion;
}
