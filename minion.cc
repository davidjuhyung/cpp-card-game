#include "minion.h"

Minion::Minion(std::string name, Board* board) : AbstractMinion{name,board} {}

void Minion::useAbility(int targetplayer, int target) {}

void Minion::useTriggered(int targetplayer, int target) {}
