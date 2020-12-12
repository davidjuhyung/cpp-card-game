#include "minion.h"
#include "ability.h"

Minion::Minion(std::string name, Board* board) : AbstractMinion{name,board} {}

void Minion::play(int owner, int targetPlayer, int minion, bool actOnRitual) {
	Player* p = board->getPlayer(owner);
	int playerMagic = p->getMagic();
	if (cost > playerMagic) throw InputException{"Player doesn't have enough magic"};
	int numMinions = p->getNumMinions();
	if (numMinions >= Player::maxMinionSize) throw InputException{"Minion slots filled"};
    p->setMagic(playerMagic-cost);
	auto m = std::make_shared<Minion>(name,board);
	m->setAttack(attack);
	m->setDefence(defence);
	auto a = std::make_shared<Ability>(name,board,m);
	p->addMinion(a);
	board->APNAP(When::Play,numMinions);
}

void Minion::useAbility(int activePlayer, int targetPlayer, int minion) {}

void Minion::useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) {}

std::shared_ptr<AbstractMinion> Minion::getMinion(bool forDisplay) {
	auto m = std::make_shared<Minion>(name,board);
	m->setAttack(attack);
	m->setDefence(defence);
	if (forDisplay) return m;
	auto a = std::make_shared<Ability>(name,board,m);
	return a;
}

card_template_t Minion::displayCard(bool forInspect) {
	card_template_t vec;
	if (name == "Air Elemental" || name == "Earth Elemental") {
		vec = display_minion_no_ability(name,cost,attack,defence);
	} else if (name == "Bomb" || name == "Fire Elemental" || name == "Potion Seller") {
		vec = display_minion_triggered_ability(name,cost,attack,defence,abilityDescription);
	} else {
		vec = display_minion_activated_ability(name,cost,attack,defence,activationCost,abilityDescription);
	}
    return vec;
}

std::vector<card_template_t> Minion::inspectMinion() {
	std::vector<card_template_t> vec = {displayCard()};
	return vec;
}
