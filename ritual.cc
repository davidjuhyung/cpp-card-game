#include "ritual.h"

void play(int player, int minion) override 
{
    
}

virtual void useAbility(int player, int minion) = 0
{
    if (description == "DarkRitual"){
        //At the start of your turn, gain 1 magic
        board->getPlayer(player)->incrementMagic();
    }
    else if (description == "AuraOfPower"){
        //whenever a minion enter a play under your control, it gains +1/+1
        attack++;
        defense++;
    }
    else if (description == "Standstill"){
        //whenever a minion enter a play, destroy it
        graveyard.push_back(minion);
    }
    /*else if (description == "BombRitual"){
        //Deals damage to all the opponent minions equal to its attack value when it dies
    }
    else if (description == "PotionSellerRitual"){
    }*/
}
