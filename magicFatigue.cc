#include "magicFatigue.h"

MagicFatigue::MagicFatigue(std::string name, Board* board) : Enchantment{name, board} {
	enchantmentName = "Magic Fatigue";
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
void MagicFatigue::useAbility(int activeplayer, int target) { minion->useAbility(activeplayer,target); }
void MagicFatigue::useTriggered(int owner, int playedminion, bool isOwnerActive, When when) { minion->useTriggered(owner,playedminion,isOwnerActive,when); }
