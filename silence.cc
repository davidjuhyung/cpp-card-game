#include "silence.h"

Silence::Silence(std::string name = "Silence", Board* board) : Enchantment{name, board} {}

}

void Silence::useAbility(int activePlayer, int minion) {
    board->getPlayer(activePlayer)->getMinion(minion); 
    
    //encahnted minion cannot use ability
}
