#include "ritual.h"

void play(int player, int minion) override 
{
    if (numOfRituals == 1){
        
    }
    //Every time the ritual's triggered ability activates, it expends a 
    //number of charges equal to its activation cost to do the effect.  
    //If it does not have enough charges left to activate, the ability's 
    //effect simply does not occur. A player may only have one ritual on 
    //the board at any one time.  If they play a second ritual while one is
    //already active, the old ritual is removed from the game and destroyed
}

virtual void useAbility(int player, int minion) = 0
{
    if (description == "DarkRitual"){
        //At the start of your turn, gain 1 magic
        cost -= activationCost;
        board->getPlayer(player)->incrementMagic();
    }
    else if (description == "AuraOfPower"){
        //whenever a minion enter a play under your control, it gains +1/+1
        cost -= activationCost;
        board->getPlayer(player)->getMinion(minion).attack++;
        board->getPlayer(player)->getMinion(minion).defence++;
    }
    else if (description == "Standstill"){
        //whenever a minion enter a play, destroy it
        cost -= activationCost;
        board->getPlayer(player).graveyard.push_back(minion);
    }
    /*else if (description == "BombRitual"){
        //Deals damage to all the opponent minions equal to its attack value when it dies
    }
    else if (description == "PotionSellerRitual"){
    }*/
}
