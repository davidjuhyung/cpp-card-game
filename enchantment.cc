#include "enchantment.h"

Enchantment::Enchantment(std::string name, Board* board) : AbstractMinion{name,board} {}

card_template_t Enchantment::displayCard() const {
	card_template_t vec;
	if (enchantmentName == "Enrage") {
		vec = display_enchantment_attack_defence(EnchantmentName,cost,enchantmentDescription,"*2","-2");
	} else if (EnchantmentName == "Giant Strength") {
		vec = display_enchantment_attack_defence(EnchantmentName,cost,enchantmentDescription,"+2","+2");
	} else {
		vec = display_enchantment(EnchantmentName,cost,enchantmentDescription);
	}
    return vec;
}

std::vector<card_template_t> Enchantment::inspectMinion() {
	std::vector<card_template_t> vec = minion->inspectMinion();
	if (enchantmentName != "Ability") vec.push_back(displayCard());
	return vec;
}
