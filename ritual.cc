#include "ritual.h"
#include "minion.h"

Ritual::Ritual(std::string name, Board* board) : Card{name,board} {
	if (name == "Dark Ritual") {
		cost = 0;
		description = "At the start of your turn, gain 1 magic";
	} else if (name == "Aura Of Power") {
		cost = 1;
		description = "Whenever a minion enter a play under your control, it gains +1/+1";
	} else {
		cost = 3;
		description = "Whenever a minion enter a play, destroy it";
	}
}

void Ritual::play(int owner, int targetPlayer, int minion, bool actOnRitual) 
{
    Player* p = board->getPlayer(owner);
    int magic = p->getMagic();
	if (cost > magic) throw InputException{"Player doesn't have enough magic"};
    p->setMagic(magic-cost);
    auto r = std::make_shared<Ritual>(name,board);
    p->setRitual(r);
}

void Ritual::useAbility(int owner, int playedMinion, bool isOwnerActive, When when)
{
    Player* p = board->getPlayer(owner);
    if (charges < activationCost) throw InputException{"Ritual doesn't have enough charges"};
    if (name == "Dark Ritual") {
        //At the start of your turn, gain 1 magic
        if (!isOwnerActive || when!=When::Start) return;
        charges -= activationCost;
        p->setMagic(p->getMagic()+1);
    }
    else if (name == "Aura Of Power") {
        //whenever a minion enter a play under your control, it gains +1/+1
        if (!isOwnerActive || when!=When::Play) return;
        charges -= activationCost;
        // playedMinion is never out of bound but i'll still check
        if (playedMinion < 0 || playedMinion > p->getNumMinions()-1) throw InputException{"Played Minion is out of bounds"};
        p->getMinion(playedMinion)->setAttack(p->getMinion(playedMinion)->getAttack()+1);
        p->getMinion(playedMinion)->setDefence(p->getMinion(playedMinion)->getDefence()+1);
    }
    else if (name == "Standstill") {
        //whenever a minion enter a play, destroy it
        if (when!=When::Play) return;
        int pNum = isOwnerActive ? owner : owner%2+1;
        charges -= activationCost;
        if (playedMinion < 0 || playedMinion > board->getPlayer(pNum)->getNumMinions()-1) throw InputException{"Played Minion is out of bounds"};
        board->getPlayer(pNum)->removeMinion(playedMinion);
    }
}

int Ritual::getCharges() const { return charges; }

void Ritual::recharge() { charges += 3; }

card_template_t Ritual::displayCard(bool forInspect) {
    card_template_t vec = display_ritual(name,cost,activationCost,description,charges);
    return vec;
}
