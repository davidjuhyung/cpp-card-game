#include "deck.h"

std::vector<std::shared_ptr<Card>> initialize(std::istream &in,Board* b) {
	std::set<std::string> minions = {"Air Elemental","Apprentice Summoner","Bomb","Earth Elemental","Fire Elemental","Master Summoner","Novice Pyromancer","Potion Seller"};
	std::set<std::string> enchantments = {"Delay","Enrage","Giant Strength","Magic Fatigue","Silence"};
	std::set<std::string> spells = {"Banish","Blizzard","Disenchant","Raise Dead","Recharge","Unsommon"};
	std::set<std::string> rituals = {"Aura of Power","Dark Ritual","Standstill"};
	std::vector<std::shared_ptr<Card>> deck;
	std::string name;
	while (getline(in,name)) {
		if (minions.find(name)!=minions.end()) {
			auto card = std::make_shared<AbstractMinion>(name,b);
			deck.push_back(card);
		} else if (enchantments.find(name)!=enchantments.end()) {
			if (name=="Delay") auto card = std::make_shared<Delay>(name,b);
			if (name=="Enrage") auto card = std::make_shared<Enrage>(name,b);
			if (name=="Giant Strength") auto card = std::make_shared<GiantStrength>(name,b);
			if (name=="Magic Fatigue") auto card = std::make_shared<MagicFatigue>(name,b);
			if (name=="Silence") auto card = std::make_shared<Silence>(name,b);
			deck.push_back(card);
		} else if (spells.find(name)!=spells.end()) {
			auto card = std::make_shared<Spell>(name,b);
			deck.push_back(card);
		} else if (rituals.find(name)!=rituals.end()) {
			auto card = std::make_shared<Ritual>(name,b);
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
