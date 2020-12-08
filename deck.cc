#include "deck.h"

std::vector<std::shared_prt<Card>> initialize(std::istream &in,Board* b) {
	std::set<std::string> minions = {"Air Elemental","Apprentice Summoner","Bomb","Earth Elemental","Fire Elemental","Master Summoner","Novice Pyromancer","Potion Seller"};
	std::set<std::string> enchantments = {"Delay","Enrage","Giant Strength","Magic Statue","Silence"};
	std::set<std::string> spells = {"Banish","Blizzard","Disenchant","Raise Dead","Recharge","Unsommon"};
	std::set<std::string> rituals = {"Aura of Power","Dark Ritual","Standstill"};
	std::vector<Card> deck;
	std::string name;
	while (getline(in,name)) {
		if (minions.find(name)!=minions.end()) {
			std::shared_ptr<Card> card = std::make_shared<AbstractMinion>(name,b);
			deck.push_back(card);
		} else if (enchantments.find(name)!=enchantments.end()) {
			std::shared_ptr<Card> card = std::make_shared<Enchantment>(name,b);
			deck.push_back(card);
		} else if (spells.find(name)!=spells.end()) {
			std::shared_ptr<Card> card = std::make_shared<Spell>(name,b);
			deck.push_back(card);
		} else if (rituals.find(name)!=rituals.end()) {
			std::shared_ptr<Card> card = std::make_shared<Ritual>(name,b);
			deck.push_back(card);
		}
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine rng{seed};
	for ( int i = 0; i < 1000; i++ ) {
		//std::shuffle( v.begin(), v.end(), std::default_random_engine(seed) );
		std::shuffle( deck.begin(), deck.end(), rng );	
	}
	return deck;
}
