#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <set>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>
#include "abstractMinion.h"
#include "giant.h"
#include "spell.h"
#include "ritual.h"
#include "enrage.h"
#include "delay.h"
#include "fatigue.h"
#include "silence.h"
#include "board.h"

// Pass an input stream in from which the deck is read, and the board pointer b on which this game is taking place
std::vector<std::shared_ptr<Card>> initialize(std::istream &in,Board* b);

#endif
