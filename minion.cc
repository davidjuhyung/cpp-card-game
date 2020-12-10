#include "minion.h"
#include "ability.h"

Minion::Minion(std::string name, Board* board) : AbstractMinion{name,board} {}

void Minion::useAbility(int activePlayer, int target) {}

void Minion::useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) {}

std::shared_ptr<AbstractMinion> Minion::getMinion() const {
	auto m = std::make_shared<Minion>(name,board);
	m->setAttack(attack);
	m->setDefence(defence);
	auto a = std::make_shared<Ability>(name,board,m);
	return a;
}
