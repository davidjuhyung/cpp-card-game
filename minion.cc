#include "minion.h"
#include "ability.h"

Minion::Minion(std::string name, Board* board) : AbstractMinion{name,board} {}

void Minion::useAbility(int activeplayer, int target) {}

void Minion::useTriggered(int owner, int playedminion, bool isOwnerActive, When when) {}

std::shared_ptr<AbstractMinion> getMinion() const {
	auto m = std::make_shared<Minion>(name,board);
	m->setAttack(attack);
	m->setDefence(defence);
	auto a = std::make_shared<Ability>(name,board,m);
	return a;
}
