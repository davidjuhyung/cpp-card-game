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

void Ability::useAbility(int activePlayer, int targetPlayer, int minion) {
	if (actions == 0) throw InputException("Minion doesn't have any actions remaining");
	Player* p = board->getPlayer(activePlayer);
	Player* t = board->getPlayer(targetPlayer);
	int mana = p->getMana();
	if (mana < activationCost) throw InputException("Player doesn't have enough mana");
	if (name == "Novice Pyromancer") {
		int lastMinion = t->getNumMinions()-1;
		if (minion < 0) throw InputException{"Please specify a target to use this ability on"};
		if (minion > lastMinion) throw InputException{"Target has no minion at position " + std::to_string(minion+1)};
		auto m = t->getMinion(minion);
		m->damage(1);
		if (m->getDefence() <= 0) {
			board->APNAP(When::Death);
			t->removeMinion(minion,true);
		}
		actions--;
		p->setMana(mana-activationCost);
	} else if (name == "Apprentice Summoner") {
		int numMinions = p->getNumMinions();
		if (numMinions == Player::maxMinionSize) throw InputException{"Minion slots filled"};
		auto m = std::make_shared<Minion>("Air Elemental",board);
		auto a = std::make_shared<Ability>(name,board,m);
		p->addMinion(a);
		board->APNAP(When::Play,numMinions);
		actions--;
		p->setMana(mana-activationCost);
	} else if (name == "Master Summoner") {
		int numMinions = p->getNumMinions();
		if (numMinions == Player::maxMinionSize) throw InputException{"Minion slots filled"};
		for (int i = 0; i < Player::maxMinionSize - numMinions && i < 3; ++i) {
			auto m = std::make_shared<Minion>("Air Elemental",board);
			auto a = std::make_shared<Ability>(name,board,m);
			p->addMinion(a);
			board->APNAP(When::Play,numMinions+i);
		}
		actions--;
		p->setMana(mana-activationCost);
	}
}

void Ability::useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) {
	Player* p = board->getPlayer(owner);
	Player* enemy = board->getPlayer(owner%2+1);
	if (name == "Bomb") {
		if (when != When::Death) return;
		if (defence > 0) return;
		int numMinions = enemy->getNumMinions();
		for (int i = 0; i < numMinions; ++i) {
			enemy->getMinion(i)->damage(attack);
			if (enemy->getMinion(i)->getDefence() <= 0) {
				board->APNAP(When::Death);
				enemy->removeMinion(i,true);
			}
		}
	} else if (name == "Potion Seller") {
		if (when != When::End) return;
		int numMinions = p->getNumMinions();
		for (int i = 0; i < numMinions; ++i) {
			p->getMinion(i)->setDefence(p->getMinion(i)->getDefence()+1);
		}
		defence--;
	} else if (name == "Fire Elemental") {
		if (when != When::Play) return;
		if (isOwnerActive) return;
		if (playedMinion < 0 || playedMinion > enemy->getNumMinions()-1) return;
		enemy->getMinion(playedMinion)->damage(1);
		if (enemy->getMinion(playedMinion)->getDefence() <= 0) {
			board->APNAP(When::Death);
			enemy->removeMinion(playedMinion,true);
		}
	}
}

std::shared_ptr<AbstractMinion> Ability::getMinion(bool forDisplay) {
	if (minion == nullptr) throw InputException{"Unexpected! Ability not attached to a minion"};
	minion->setDefence(defence);
	minion->setAttack(attack);
	return minion;
}
