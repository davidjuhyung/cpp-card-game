#include "minion.h"

Minion::Minion(std::string name, Board* board) : AbstractMinion{name,board} {}

void Minion::useAbility(int activeplayer, int target) {}

void Minion::useTriggered(int activeplayer, int target) {}
