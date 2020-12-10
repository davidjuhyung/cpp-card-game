#ifndef DECK_H
#define DECK_H

#include <istream>
#include <vector>
#include <memory>

class Card;
class AbstractMinion;
class GiantStrength;
class Spell;
class Enrage;
class Delay;
class MagicFatigue;
class Silence;
class Board;
class Player;
class Ritual;
class Enchantment;

// Pass an input stream in from which the deck is read, and the board pointer b on which this game is taking place
std::vector<std::shared_ptr<Card>> initialize(std::istream &in, Board* b);

#endif
