#include "spell.h"

void Spell::play(int player, int minion) {
    if (description == "Banish"){
        //destroy target minion or ritual
        cost -= 2;
        board->getPlayer(player).graveyard.push_back(minion);
    }
    else if (description == "Unsommon"){
        //return target minion to its owner's hand
        cost --;
        board->getPlayer(player)->moveToHand(minion);
    }
    else if (description == "Recharge"){
        //ritual gains 3 charges
        cost --;
        board->getPlayer(player)->getRitual().charges += 3;
    }
    else if (description == "Disenchant"){
        //destroy the top enchantment on target minion
        cost--;
    }
    else if (description == "Raise Dead"){
        //resurrect the top minion in your graveyard and set its defence to 1
        cost--;
        board->getPlayer(player)->resurect();
        top_minion.defence = 1;
    }
    else if (description == "Blizzard"){
        //deal 2 damage to all minion
        cost--;
        /*play_one_mininion = getMinion(1);
        play_two_mininion = getMinion(2);
        play_one_num = numMinions(1);
        play_two_num = numMinions(2);
        for (int i; i < play_one_num; i++) {}*/
        board->getPlayer(player)->getMinion(1)->damage(2);
        board->getPlayer(player)->getMinion(2)->damage(2);
    }
}
