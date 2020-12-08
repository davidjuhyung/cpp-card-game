#include "spell.h"

void Spell::play(int player, int minion) {
    if (description == "Banish"){
        cost -= 2;
        //Minion temp{} 
        //auto m = std::make_shared<Minion>(temp);
        graveyard.push_back(minion);
        //destroy target minion or ritual
    }
    else if (description == "Unsommon"){
        cost --;
        board->getPlayer(player)->moveToHand(minion);
        //return target minion to its owner's hand
    }
    else if (description == "Recharge"){
        cost --;
        board->getPlayer(player)->getRitual().charges += 3;
        //ritual gains 3 charges
    }
    else if (description == "Disenchant"){
        cost--;

        //destroy the top enchantment on target minion
    }
    else if (description == "RaiseDead"){
        cost--;
        board->getPlayer(player)->resurect();
        top_minion.defence = 1;
        //resurrect the top minion in your graveyard and set its defence to 1
    }
    else if (description == "Blizzard"){
        cost--;
        play_one_mininion = getMinion(1);
        play_two_mininion = getMinion(2);
        play_one_num = numMinions(1);
        play_two_num = numMinions(2);
        for (int i; i < play_one_num; i++) {
            
        }
        //deal 2 damage to all minion
    }
}
