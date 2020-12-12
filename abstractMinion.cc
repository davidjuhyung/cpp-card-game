#include "abstractMinion.h"
#include "minion.h"
#include "ability.h"

AbstractMinion::AbstractMinion(std::string name, Board* board) : Card{name,board} {
	actions = 1;
	if (name == "Air Elemental") {
		attack = 1;
		defence = 1;
		cost = 0;
	} else if (name == "Earth Elemental") {
		attack = 4;
		defence = 4;
		cost = 3;
	} else if (name == "Bomb") {
		attack = 1;
		defence = 2;
		cost = 2;
		abilityDescription = "Deals damage to all opponent minions equal to its attack value when it dies";
	} else if (name == "Fire Elemental") {
		attack = 2;
		defence = 2;
		cost = 2;
		abilityDescription = "Whenever an opponent's minion enters play deal 1 damage to it";
	} else if (name == "Potion Seller") {
		attack = 1;
		defence = 3;
		cost = 2;
		abilityDescription = "At the end of your turn, all your minions gain +0/+1";
	} else if (name == "Novice Pyromancer") {
		attack = 0;
		defence = 1;
		cost = 1;
		activationCost = 1;
		abilityDescription = "Deal 1 damage to target minion";
	} else if (name == "Apprentice Summoner") {
		attack = 1;
		defence = 1;
		cost = 1;
		activationCost = 1;
		abilityDescription = "Summon a 1/1 Air Elemental";
	} else {
		attack = 2;
		defence = 3;
		cost = 3;
		activationCost = 2;
		abilityDescription = "Summon up to 3 1/1 Air Elementals";
	}
}

void AbstractMinion::attackPlayer(int player) {
	if (actions == 0) throw InputException("Minion doesn't have any actions remaining");
	Player* p = board->getPlayer(player);
	p->damage(attack);
	if(p->getLife() <= 0) throw InputException{"Game over! Player " + std::to_string(player%2+1) + " wins! Congratulations!",true};
	actions--;
}

void AbstractMinion::attackMinion(int ownPosition, int player, int target) {
	int lastNum1 = board->getPlayer(player%2+1)->getNumMinions()-1;
	int lastNum2 = board->getPlayer(player)->getNumMinions()-1;
	if (0 > ownPosition || lastNum1 < ownPosition) {
		throw InputException{"You have no minion at position " + std::to_string(ownPosition+1)};
	} else if (lastNum2 < target) {
		throw InputException{"Enemy have no minion at position " + std::to_string(target+1)};
	} else if (0 > target) {
		throw InputException{"Please specify a target to attack"};
	}
	if (actions == 0) throw InputException("Minion doesn't have any actions remaining");
	Player* p = board->getPlayer(player);
	auto m = p->getMinion(target);
	m->damage(attack);
	defence -= m->getAttack();
	if (m->getDefence() <= 0) {
		board->APNAP(When::Death);
		auto removed = m->removeAllEnchantments();
		p->replaceMinion(target,removed);
		p->removeMinion(target,true);
	}
	if (defence <= 0) {
		board->APNAP(When::Death);
		auto removed = removeAllEnchantments();
		p->replaceMinion(ownPosition,removed);
		board->getPlayer(player%2+1)->removeMinion(ownPosition,true);
	}
	actions--;
}

void AbstractMinion::damage(int d) { defence -= d; }

int AbstractMinion::getDefence() const { return defence; }

int AbstractMinion::getAttack() const { return attack; }

void AbstractMinion::setDefence(int d) { defence = d; }

void AbstractMinion::setAttack(int a) { attack = a; }

int AbstractMinion::getAction() const {return actions; }

bool AbstractMinion::gaining() const { return gainAction; }

void AbstractMinion::setGaining(bool gain) { gainAction = gain; }

int AbstractMinion::getActivationCost() const { return activationCost; }

void AbstractMinion::setActivationCost(int c) { activationCost = c; }

void AbstractMinion::setAction(int owner, int ownPosition) { 
	if (gainAction) actions = 1;
	else {
		board->getPlayer(owner)->replaceMinion(ownPosition,getMinion());
	}
}

void AbstractMinion::setCurrentAction(int a) { actions = a; }
