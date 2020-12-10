#include "ritual.h"

Ritual::Ritual(std::string name, Board* board) : Card{name,board} {
	if (name == "Dark Ritual") {
		cost = 0;
		description = "At the start of your turn, gain 1 magic";
	} else if (name == "Aura Of Power") {
		cost = 1;
		description = "Whenever a minion enter a play under your control, it gains +1/+1";
	} else {
		cost = 3;
		description = "Whenever a minion enter a play, destroy it";
	}
}

void Ritual::play(int owner, int targetPlayer, int minion, bool actOnRitual) 
{
	if (cost > board->getPlayer(owner)->getMagic()) return;
    board->getPlayer(owner)->setMagic(board->getPlayer(owner)->getMagic()-cost);
    auto r = std::make_shared<Ritual>(name,board);
    board->getPlayer(owner)->setRitual(r);
}

void Ritual::useAbility(int owner, int playedMinion, bool isOwnerActive, When when)
{
    if (charges < activationCost) { return; }
    if (name == "Dark Ritual"){
        //At the start of your turn, gain 1 magic
        if (!isOwnerActive || when!=When::Start) return;
        charges -= activationCost;
        board->getPlayer(owner)->setMagic(board->getPlayer(owner)->getMagic()+1);
    }
    else if (name == "Aura Of Power") {
        //whenever a minion enter a play under your control, it gains +1/+1
        if (!isOwnerActive || when!=When::Play) return;
        charges -= activationCost;
        board->getPlayer(owner)->getMinion(playedMinion)->setAttack(board->getPlayer(owner)->getMinion(playedMinion)->getAttack()+1);
        board->getPlayer(owner)->getMinion(playedMinion)->setDefence(board->getPlayer(owner)->getMinion(playedMinion)->getDefence()+1);
    }
    else if (name == "Standstill") {
        //whenever a minion enter a play, destroy it
        if (when!=When::Play) return;
        int p = isOwnerActive ? owner : owner%2+1;
        charges -= activationCost;
        board->getPlayer(p)->removeMinion(playedMinion);
    }
}

int Ritual::getCharges() const { return charges; }

void Ritual::recharge() { charges += 3; }
