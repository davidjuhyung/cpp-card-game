#include "enchantment.h"

Enchantment::Enchantment(std::string name, Board* board) : AbstractMinion{name,board} {}

card_template_t Enchantment::displayCard() {
	card_template_t vec;
	if (minion != nullptr) {
		vec = getMinion(true)->displayCard();
		return vec;
	}
	if (enchantmentName == "Enrage") {
		vec = display_enchantment_attack_defence(enchantmentName,cost,enchantmentDescription,"*2","-2");
	} else if (enchantmentName == "Giant Strength") {
		vec = display_enchantment_attack_defence(enchantmentName,cost,enchantmentDescription,"+2","+2");
	} else if (enchantmentName == "Ability") {
		vec = minion->displayCard();
	} else {
		vec = display_enchantment(enchantmentName,cost,enchantmentDescription);
	}
    return vec;
}

std::vector<card_template_t> Enchantment::inspectMinion() {
	std::vector<card_template_t> vec = getMinion(true)->inspectMinion();
	if (enchantmentName != "Ability") vec.push_back(displayCard());
	return vec;
}
