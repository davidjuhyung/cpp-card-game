#include "spell.h"

Spell(std::string name, Board* board) : Card{name,board} {
	if (name == "Banish") {
		cost = 2;
		description = "Destroy target minion or ritual";
	} else if (name == "Unsommon") {
		cost = 1;
		description = "Return target minion to its owner's hand";
	} else if (name == "Recharge") {
		cost = 1;
		description = "Your ritual gains 3 charges";
	} else if (name == "Disenchant") {
		cost = 1;
		description = "Destroy the top enchantment on target minion";
	} else if (name == "Raise Dead") {
		cost = 1;
		description = "Resurrect the top minion in your graveyard and set its defence to 1";
	} else {
		cost = 3;
		description = "Deal 2 damage to all minions";
	}
}

void Spell::play(int owner, int targetPlayer, int minion, bool actOnRitual) {
	if (cost > board->getPlayer(owner)->getMagic()) return;
    board->getPlayer(owner)->setMagic(board->getPlayer(owner)->getMagic()-cost);
    if (name == "Banish"){
        //destroy target minion or ritual
        if (actOnRitual) board->getPlayer(targetplayer)->removeRitual();
        else board->getPlayer(targetplayer)->removeMinion(minion);
    }
    else if (name == "Unsommon"){
        //return target minion to its owner's hand
        board->getPlayer(targetplayer)->moveToHand(minion);
    }
    else if (name == "Recharge"){
        //ritual gains 3 charges
        board->getPlayer(owner)->getRitual()->recharge();
    }
    else if (name == "Disenchant"){
        //destroy the top enchantment on target minion
        auto m = board->getPlayer(targetplayer)->getMinon(minion)->getMinion(); 
        board->getPlayer(targetPlayer)->replaceMinion(minion, m)
    }
    else if (name == "Raise Dead"){
        //resurrect the top minion in your graveyard and set its defence to 1
        board->getPlayer(owner)->resurect();
        board->getPlayer(owner)->getMinion(board->getPlayer(owner)->getNumMinion()-1)->setDefence(1);
    }
    else if (name == "Blizzard"){
        //deal 2 damage to all minions
        for (int i = 0; i < board->getPlayer(owner)->getNumMinions(); i++ ){
            board->getPlayer(owner)->getMinion(i)->damage(2);
        }
        for (int i = 0; i < board->getPlayer(owner%2+1)->getNumMinions(); i++ ){
            board->getPlayer(owner)->getMinion(i)->damage(2);
        }
    }
}
