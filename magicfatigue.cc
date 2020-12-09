#include "magicfatigue.h"

MagicFatigue::MagicFatigue(std::string name = "Magic Fatigue", Board* board) : Enchantment{name, board} {}

void MagicFatigue::play(int player, int minion){
    //enchanted minion's activated ability costs 2 more
    auto m = std::make_share<MagicFatigue>(name,board);
    m->minion = board->getPlayer(player)->getMinion(minion);
	m->actions = m->minion->getAction();
	m->attack = m->minion->getAttack();
	m->defence = m->minion->getDefence();
	m->gainAction = m->minion->gaining();
	m->name = m->minion->getName();
	m->activationCost = m->minion->getActivationCost() + 2;
    board->getPlayer(player)->replaceMinion(minion,m);
}
void MagicFatigue::useAbility(int activeplayer, int target) { minion->useAbility(activeplayer,target); }
void MagicFatigue::useTriggered(int activeplayer, int target) { minion->useTriggered(activeplayer,target); }
