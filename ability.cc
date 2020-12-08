#include "ability.h"

Ability::Ability(std::string name, Board* board, std::shared_ptr<AbstractMinion> minion) : Enchantment{name,board},
 enchantmentName{"Ability"}, minion{minion}, attack{minion->getAttack()}, defence{minion->getDefence()},
 actions{minion->getAction()}, name{minion->getName()} {
	if (name == "Novice Pyromancer" || name == "Apprentice Summoner") activationCost = 1;
	else if (name == "Master Summoner") activationCost = 2;
	else activationCost = 0;
}

void Ability::play(int player, int minion) {}

void Ability::useAbility(int activeplayer, int target) {
	
}
