#include "ritual.h"

void play(int player, int minion = 0, bool actOnRitual = false) 
{
    //Every time the ritual's triggered ability activates, it expends a 
    //number of charges equal to its activation cost to do the effect.  
    //If it does not have enough charges left to activate, the ability's 
    //effect simply does not occur. A player may only have one ritual on 
    //the board at any one time.  If they play a second ritual while one is
    //already active, the old ritual is removed from the game and destroyed
}

void useAbility(int player, int playedminion = 0, bool actOnRitual = false, When when = When::Start)
{
    if (description == "DarkRitual"){
        //At the start of your turn, gain 1 magic
        cost -= activationCost;
        board->getPlayer(player)->incrementMagic();
    }
    else if (description == "AuraOfPower"){
        //whenever a minion enter a play under your control, it gains +1/+1
        cost -= activationCost;
        board->getPlayer(player)->getMinion(minion)->getAttack()++;
        board->getPlayer(player)->getMinion(minion)->getDefence()++;
    }
    else if (description == "Standstill"){
        //whenever a minion enter a play, destroy it
        cost -= activationCost;
        for (int i = 1; i <= player->getNumMinions(); i++){
            board->getPlayer(player)->removeMinion();
        }
    }
}

int Ritual::getCharges() const { return charges; }
