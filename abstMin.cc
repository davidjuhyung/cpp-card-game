#include "abstMin.h"

void AbstractMinion::attack(int player) {
	Player* p = board->getPlayer(player);
	if (actions == 0) return;
	p->damage(attack);
}

void AbstractMinion::attack(int player, int minion) {
	Player* p = board->getPlayer(player);
	AbstractMinion* m = p->getMinion(minion);
	if (actions == 0) return;
	m->damage(attack);
	defence -= m->getAttack();
}

void AbstractMinion::damage(int a) { defence -= a; }

int AbstractMinion::getAttack() { return attack; }

int AbstractMinion::getDefence() { return defence; }

int AbstractMinion::setAction() {
	if (gainAction) actions = 1;
}
