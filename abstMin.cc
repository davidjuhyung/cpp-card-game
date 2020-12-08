#include "abstMin.h"
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

void AbstractMinion::attack(int player) {
	Player* p = board->getPlayer(player);
	if (actions == 0) return;
	p->damage(attack);
}

void AbstractMinion::attack(int player, int minion) {
	Player* p = board->getPlayer(player);
	AbstractMinion* m = p->getMinion(minion);
	if (actions == 0) return;
	m->defence -= attack;
	defence -= m->attack;
}

void AbstractMinion::play(int player, int minion = 0, bool actOnRitual = false) {
	std::shared_ptr<AbstractMinion> m = std::make_shared<Minion>(name,board);
	m->attack = attack;
	m->defence = defence;
	std::shared_ptr<AbstractMinion> a = std::make_shared<Ability>(name,board,m);
	board->getPlayer(player)->addMinion(a);
}

int AbstractMinion::getDefence() const { return defence; }

int AbstractMinion::getAttack() const { return attack; }

int AbstractMinion::getAction() const {return actions; }

bool AbstractMinion::gaining() const { return gainAction; }

int AbstractMinion::setAction() {
	if (gainAction) actions = 1;
}
