#include "spell.h"

void Spell::play(int player, int minion, bool actOnRitual) {
    if (description == "Banish"){
        //destroy target minion or ritual *****
        getCost() -= 2;
        board->getPlayer(player)->removeMinion();
        board->getPlayer(player)->removeRitual();
    }
    else if (description == "Unsommon"){
        //return target minion to its owner's hand
        getCost()--;
        board->getPlayer(player)->moveToHand(minion);
    }
    else if (description == "Recharge"){
        //ritual gains 3 charges
        getCost()--;
        board->getPlayer(player)->getRitual()->getCharges() += 3;
    }
    else if (description == "Disenchant"){
        //destroy the top enchantment on target minion
        getCost()--;
        auto m = board->getPlayer(player)->getMinon(minion)->getMinion(); 
        board->getPlayer(player)->replaceMinion(minion, m)
    }
    else if (description == "Raise Dead"){
        //resurrect the top minion in your graveyard and set its defence to 1
        getCost()--;
        board->getPlayer(player)->resurect();
        int num = board->getPlayer(player)->getNumMinions();
        board->getPlayer(player)->getMinion(num)->setDefence(1);
    }
    else if (description == "Blizzard"){
        //deal 2 damage to all minion
        getCost()--;
        for (int i = 1; i <= board->getPlayer(player)->getNumMinions(); i++ ){
            board->getPlayer(player)->getMinion(1)->damage(2);
        }
        for (int i = 1; i <= board->getPlayer(player%2+1)->getNumMinions(); i++ ){
            board->getPlayer(player)->getMinion(2)->damage(2);
        }
    }
}
