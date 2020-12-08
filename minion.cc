#include "minion.h"

Minion::Minion(std::string name, Board* board) : AbstractMinion{name,board} {}

void Minion::useAbility(int activeplayer) {}

void Minion::useTriggered(int activeplayer) {}
