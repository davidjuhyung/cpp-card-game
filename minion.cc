#include "minion.h"
#include "ability.h"

Minion::Minion(std::string name, Board* board) : AbstractMinion{name,board} {}

void Minion::useAbility(int activePlayer, int target) {}

void Minion::useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) {}

std::shared_ptr<AbstractMinion> Minion::getMinion(bool forDisplay = false) {
	auto m = std::make_shared<Minion>(name,board);
	m->setAttack(attack);
	m->setDefence(defence);
	if (forDisplay) return m;
	auto a = std::make_shared<Ability>(name,board,m);
	return a;
}

card_template_t Minion::displayCard() const {
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
