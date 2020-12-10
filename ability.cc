#include "ability.h"
#include "minion.h"

Ability::Ability(std::string name, Board* board, std::shared_ptr<AbstractMinion> minion) : Enchantment{name,board} {
	enchantmentName = "Ability";
	this->minion = minion;
	attack = minion->getAttack();
	defence = minion->getDefence();
	actions = minion->getAction();
	name = minion->getName();
	enchantmentDescription = "Not actually an enchantment";
}

void Ability::play(int owner, int targetPlayer, int minion, bool actOnRitual) {}

void Ability::useAbility(int activePlayer, int target) {
	if (actions == 0) return;
	Player* p = board->getPlayer(activePlayer);
	int magic = p->getMagic();
	if (magic < activationCost) return;
	if (name == "Novice Pyromancer") {
		board->getPlayer(activePlayer%2+1)->getMinion(target)->damage(1);
		if (board->getPlayer(activePlayer%2+1)->getMinion(target)->getDefence() <= 0) {
			board->APNAP(When::Death);
			board->getPlayer(activePlayer%2+1)->removeMinion(target,true);
		}
		actions--;
		p->setMagic(magic-activationCost);
	} else if (name == "Apprentice Summoner") {
		int num = p->getNumMinions();
		if (num == Player::maxMinionSize) return;
		auto m = std::make_shared<Minion>("Air Elemental",board);
		auto a = std::make_shared<Ability>(name,board,m);
		p->addMinion(a);
		board->APNAP(When::Play,num);
		actions--;
		p->setMagic(magic-activationCost);
	} else if (name == "Master Summoner") {
		int num = p->getNumMinions();
		if (num == Player::maxMinionSize) return;
		for (int i = 0; i < Player::maxMinionSize - num && i < 3; ++i) {
			auto m = std::make_shared<Minion>("Air Elemental",board);
			auto a = std::make_shared<Ability>(name,board,m);
			p->addMinion(a);
			board->APNAP(When::Play,num+i);
		}
		actions--;
		p->setMagic(magic-activationCost);
	}
}

void Ability::useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) {
	Player* p = board->getPlayer(owner);
	Player* enemy = board->getPlayer(owner%2+1);
	if (name == "Bomb") {
		if (when != When::Death) return;
		if (defence > 0) return;
		int num = enemy->getNumMinions();
		for (int i = 0; i < num; ++i) {
			enemy->getMinion(i)->damage(attack);
			if (enemy->getMinion(i)->getDefence() <= 0) {
				board->APNAP(When::Death);
				enemy->removeMinion(i,true);
			}
		}
	} else if (name == "PotionSeller") {
		if (when != When::End) return;
		int num = p->getNumMinions();
		for (int i = 0; i <  num; ++i) {
			p->getMinion(i)->setAttack(p->getMinion(i)->getAttack()+1);
		}
	} else if (name == "Fire Elemental") {
		if (when != When::Play) return;
		if (isOwnerActive) return;
		enemy->getMinion(playedMinion)->damage(1);
		if (enemy->getMinion(playedMinion)->getDefence() <= 0) {
			board->APNAP(When::Death);
			enemy->removeMinion(playedMinion,true);
		}
	}
}

std::shared_ptr<AbstractMinion> Ability::getMinion() {
	return minion;
}
