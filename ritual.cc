#include "ritual.h"

void play(int player, int minion = 0, bool actOnRitual = false) 
{
    board->getPlayer(player)->getMagic() -= cost;
}

void useAbility(int player, int playedMinion = 0, bool actOnRitual = false, When when = When::Start)
{
    if (charges == 0) { return; }
    if (description == "DarkRitual"){
        //At the start of your turn, gain 1 magic
        charges -= activationCost;
        board->getPlayer(player)->incrementMagic();
    }
    else if (description == "AuraOfPower"){
        //whenever a minion enter a play under your control, it gains +1/+1
        charges -= activationCost;
        board->getPlayer(player)->getMinion(minion)->getAttack()++;
        board->getPlayer(player)->getMinion(minion)->getDefence()++;
    }
    else if (description == "Standstill"){
        //whenever a minion enter a play, destroy it
        charges -= activationCost;
        for (int i = 1; i <= player->getNumMinions(); i++){
            board->getPlayer(player)->removeMinion();
        }
    }
}

int Ritual::getCharges() const { return charges; }
