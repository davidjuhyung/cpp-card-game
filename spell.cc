#include "spell.h"

void Spell::play(nt player, int minion) {
    if (description == "Banish"){
        cost -= 2;
        //Minion temp{} //what values??;
        //auto m = std::make_shared<Minion>(temp);
        graveyard.push_back(minion);
        //destroy target minion or ritual
    }
    else if (description == "Unsommon"){
        cost --;
        //return target minion to its owner's hand
    }
    else if (description == "Recharge"){
        cost --;
        getRitual().charges += 3;
        //ritual gains 3 charges
    }
    else if (description == "Disenchant"){
        cost--;

        //destroy the top enchantment on target minion
    }
    else if (description == "RaiseDead"){
        cost--;
        top_minion = graveyard.back().c;
        top_minion.defence = 1;
        //resurrect the top minion in your graveyard and set its defence to 1
    }
    else if (description == "Blizzard"){
        cost--;
        play_one_mininion = getMinion(1);
        play_two_mininion = getMinion(2);
        
        //deal 2 damage to all minion
    }
    else if (description == "Summoner"){
        
    }
}
