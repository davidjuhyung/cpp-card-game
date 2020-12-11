#include "spell.h"
#include "ritual.h"
#include "minion.h"

Spell::Spell(std::string name, Board* board) : Card{name,board} {
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
    Player* p = board->getPlayer(owner);
    Player* t = board->getPlayer(targetPlayer);
	int playerMagic = p->getMagic();
    if (cost > playerMagic) throw InputException{"Player doesn't have enough magic"};  
    if (name == "Banish"){
        //destroy target minion or ritual
        if (actOnRitual) {
            if (t->hasRitual() == false) throw InputException{"Target doesn't have ritual"};
            t->removeRitual();
        } else {
            int lastMinion = t->getNumMinions() - 1;
            if (minion < 0 || minion > lastMinion) throw InputException{"Target has no minion at position " + std::to_string(minion+1)};
            t->removeMinion(minion);
        }
    }
    else if (name == "Unsommon") {
        //return target minion to its owner's hand
        int lastMinion = t->getNumMinions() - 1;
        if (minion < 0 || minion > lastMinion) throw InputException{"Target has no minion at position " + std::to_string(minion+1)};
        t->moveToHand(minion);
    }
    else if (name == "Recharge") {
        //ritual gains 3 charges
        if (p->hasRitual() == false) throw InputException{"You don't have ritual"};
        p->getRitual()->recharge();
    }
    else if (name == "Disenchant") {
        //destroy the top enchantment on target minion
        int lastMinion = t->getNumMinions() - 1;
        if (minion < 0 || minion > lastMinion) throw InputException{"Target has no minion at position " + std::to_string(minion+1)};
        auto m = t->getMinion(minion)->getMinion(); 
        board->getPlayer(targetPlayer)->replaceMinion(minion, m);
        if (m->getDefence() <= 0) {
            board->APNAP(When::Death);
            t->removeMinion(minion,true);
        }
    }
    else if (name == "Raise Dead") {
        //resurrect the top minion in your graveyard and set its defence to 1
        if (p->isGraveyardEmpty()) throw InputException{"Graveyard is Empty"};
        p->resurrect();
        p->getMinion(board->getPlayer(owner)->getNumMinions()-1)->setDefence(1);
    }
    else if (name == "Blizzard"){
        //deal 2 damage to all minions
        for (int i = 0; i < p->getNumMinions(); i++ ){
            p->getMinion(i)->damage(2);
            if (p->getMinion(i)->getDefence() <= 0) {
                board->APNAP(When::Death);
                p->removeMinion(i,true);
            }
        }
        for (int i = 0; i < board->getPlayer(owner%2+1)->getNumMinions(); i++ ){
            board->getPlayer(owner%2+1)->getMinion(i)->damage(2);
            if (board->getPlayer(owner%2+1)->getMinion(i)->getDefence() <= 0) {
                board->APNAP(When::Death);
                board->getPlayer(owner%2+1)->removeMinion(i,true);
            }
        }
    }
    p->setMagic(playerMagic-cost);
}

card_template_t Spell::displayCard(bool forInspect) { 
    card_template_t vec = display_spell(name,cost,description);
    return vec;
}
