#include "ability.h"

Ability::Ability(std::string name, Board* board, std::shared_ptr<AbstractMinion> minion) : Enchantment{name,board},
 enchantmentName{"Ability"}, minion{minion}, attack{minion->getAttack()}, defence{minion->getDefence()},
 actions{minion->getAction()}, name{minion->getName()} {
	if (name == "Novice Pyromancer" || name == "Apprentice Summoner") activationCost = 1;
	else if (name == "Master Summoner") activationCost = 2;
	else activationCost = 0;
}

void Ability::play(int player, int minion = 0, bool actOnRitual = false) {}

void Ability::useAbility(int activeplayer, int target) {
	if (actions == 0) return;
	Player* p = board->getPlayer(activeplayer);
	int m = p->getMagic();
	if (m < activationCost) return;
	if (name == "Novice Pyromancer") {
		board->getPlayer(activeplayer%2+1)->getMinion(target)->damage(1);
		actions--;
		p->setMagic(m-activationCost);
	} else if (name == "Apprentice Summoner") {
		int num = p->getNumMinions();
		if (num == 5) return;
		auto m = std::make_shared<Minion>("Air Elemental",board);
		auto a = std::make_shared<Ability>(name,board,m);
		p->addMinion(a);
		actions--;
		p->setMagic(m-activationCost);
	} else if (name == "Master Summoner") {
		int num = p->getNumMinions();
		if (num == 5) return;
		for (int i = 1; i <= 5 - num && i <= 3; ++i) {
			auto m = std::make_shared<Minion>("Air Elemental",board);
			auto a = std::make_shared<Ability>(name,board,m);
			p->addMinion(a);
		}
		actions--;
		p->setMagic(m-activationCost);
	}
}

void Ability::useTriggered(int owner, int playedminion, int minionowner, bool isOwnerActive, When when) {
	Player* p = board->getPlayer(owner);
	Player* enemy = board->getPlayer(owner%2+1);
	if (name == "Bomb") {
		if (defence > 0) return;
		int num = enemy->getNumMinions();
		for (int i = 1; i <= num; ++i) {
			enemy->getMinion(i)->damage(attack);
		}
	} else if (name == "PotionSeller") {
		int num = p->getNumMinions();
		for (int i = 1; i <=  num; ++i) {
			p->getMinion(i)->incrementAttack();
		}
	} else if (name == "Fire Elemental") {
		if (when != When::Play) return;

	}
}
