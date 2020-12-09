#include "player.h"

Player::Player(std::string name)
  : name{name}
  , life{20}
  , magic{3}
  , deck{deck}
  , hand{hand}
  , minions{minions}
  , graveyard{graveyard}
  , ritual{graveyard}
  {};

Player::~Player() {};


