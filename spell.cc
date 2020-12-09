#include "spell.h"

void Spell::play(int player, int minion) {
    if (description == "Banish"){
        //destroy target minion or ritual
        getCost()-= 2;
        board->getPlayer(player).graveyard.push_back(minion);
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
    }
    else if (description == "Raise Dead"){
        //resurrect the top minion in your graveyard and set its defence to 1
        getCost()--;
        board->getPlayer(player)->resurect();
        top_minion->getDefence() += 1;
    }
    else if (description == "Blizzard"){
        //deal 2 damage to all minion
        getCost()--;
        /*play_one_mininion = getMinion(1);
        play_two_mininion = getMinion(2);
        play_one_num = numMinions(1);
        play_two_num = numMinions(2);
        for (int i; i < play_one_num; i++) {}*/
        board->getPlayer(player)->getMinion(1)->damage(2);
        board->getPlayer(player)->getMinion(2)->damage(2);
    }
}
