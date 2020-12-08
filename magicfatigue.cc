#include "magicfatigue.h"

MagicFatigue::MagicFatigue(std::string name = "Magic Fatigue", Board* board) : Enchantment{name, board} {}

void MagicFatigue::useAbility(int activePlayer) {
    //enchanted minion's activated ability costs 2 more
    board->getPlayer(activePlayer);
    minion 
}
