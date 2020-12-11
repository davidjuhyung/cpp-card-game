#include "magicFatigue.h"

MagicFatigue::MagicFatigue(std::string name, Board* board) : Enchantment{name, board} {
	enchantmentName = "Magic Fatigue";
	enchantmentDescription = "Enchanted minion's activated ability costs 2 more";
	cost = 0;
}

void MagicFatigue::play(int owner, int targetPlayer, int minion, bool actOnRitual){
	//enchanted minion's activated ability costs 2 more
	if (cost > board->getPlayer(owner)->getMagic()) return;
	board->getPlayer(owner)->setMagic(board->getPlayer(owner)->getMagic()-cost);
	auto m = std::make_shared<MagicFatigue>(name,board);
	m->minion = board->getPlayer(targetPlayer)->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack();
	m->defence = m->minion->getDefence();
	m->gainAction = m->minion->gaining();
	m->name = m->minion->getName();
	m->activationCost = m->minion->getActivationCost() + 2;
    board->getPlayer(targetPlayer)->replaceMinion(minion,m);
}
void MagicFatigue::useAbility(int activePlayer, int target) { minion->useAbility(activePlayer,target); }
void MagicFatigue::useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) { minion->useTriggered(owner,playedMinion,isOwnerActive,when); }

std::shared_ptr<AbstractMinion> MagicFatigue::getMinion() {
	return minion;
}
