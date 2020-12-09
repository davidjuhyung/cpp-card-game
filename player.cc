#include "player.h"

Player::Player(std::string name, std::vector<std::shared_ptr<Card>> deck)
  : name{name}
  , life{20}
  , magic{3}
  , deck{deck}
  , hand{nullptr}
  , minions{nullptr}
  , graveyard{nullptr}
  , ritual{nullptr}
  {};


