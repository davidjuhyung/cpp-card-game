#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <set>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>
#include "abstMin.h"
#include "giant.h"
#include "spell.h"
#include "ritual.h"
#include "enrage.h"
#include "delay.h"
#include "fatigue.h"
#include "silence.h"

std::vector<std::shared_ptr<Card>> initialize(std::istream &in);

#endif
