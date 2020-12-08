#include "ritual.h"

void play(int player, int minion) override 
{
    
}

virtual void useAbility(bool startOfPlay, bool minionplayed) = 0
{
    if (description == "DarkRitual"){
        //At the start of your turn, gain 1 magic
        magic++;
    }
    else if (description == "AuraOfPower"){
        //whenever a minion enter a play under your control, it gains +1/+1

    }
    else if (description == "Standstill"){
        //whenever a minion enter a play, destroy it
        
    }
    else if (description == "BombRitual"){
    }
    else if (description == "PotionSellerRitual"){
    }
}
