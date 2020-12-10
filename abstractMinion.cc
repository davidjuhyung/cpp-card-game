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
	} else if (name == "Fire Elemental") {
		attack = 2;
		defence = 2;
		cost = 2;
	} else if (name == "Potion Seller") {
		attack = 1;
		defence = 3;
		cost = 2;
	} else if (name == "Novice Pyromancer") {
		attack = 0;
		defence = 1;
		cost = 1;
	} else if (name == "Apprentice Summoner") {
		attack = 1;
		defence = 1;
		cost = 1;
	} else {
		attack = 2;
		defence = 3;
		cost = 3;
	}
}

void AbstractMinion::attackPlayer(int player) {
	if (actions == 0) return;
	Player* p = board->getPlayer(player);
	if (actions == 0) return;
	p->damage(attack);
	actions--;
}

void AbstractMinion::attackMinion(int ownPosition, int player, int target) {
	if (actions == 0) return;
	Player* p = board->getPlayer(player);
	auto m = p->getMinion(target);
	if (actions == 0) return;
	m->damage(attack);
	if (m->getDefence() <= 0) {
		board->APNAP(When::Death);
		p->removeMinion(target,true);
	}
	defence -= m->getAttack();
	if (defence <= 0) {
		board->APNAP(When::Death);
		board->getPlayer(player%2+1)->removeMinion(ownPosition,true);
	}
	actions--;
}

void AbstractMinion::damage(int d) { defence -= d; }

void AbstractMinion::play(int owner, int targetPlayer, int minion, bool actOnRitual) {
	if (cost > board->getPlayer(owner)->getMagic()) return;
    board->getPlayer(owner)->setMagic(board->getPlayer(owner)->getMagic()-cost);
	auto m = std::make_shared<Minion>(name,board);
	m->setAttack(attack);
	m->setDefence(defence);
	auto a = std::make_shared<Ability>(name,board,m);
	board->getPlayer(owner)->addMinion(a);
	board->APNAP(When::Play,board->getPlayer(owner)->getNumMinions()-1);
}

int AbstractMinion::getDefence() const { return defence; }

int AbstractMinion::getAttack() const { return attack; }

void AbstractMinion::setDefence(int d) { defence = d; }

void AbstractMinion::setAttack(int a) { attack = a; }

int AbstractMinion::getAction() const {return actions; }

bool AbstractMinion::gaining() const { return gainAction; }

int AbstractMinion::getActivationCost() const { return activationCost; }

void AbstractMinion::setAction() { if (gainAction) actions = 1; }
