#include "board.h"
#include "card.h"
#include "player.h"
#include "minion.h"
#include "ritual.h"
#include <iostream>


// getPlayer and setPlayer will use a loop in the future, but for now this is sufficient.
Player* Board::getPlayer(int p)
{
  if (player1->getPlayerNum() == p) {
    return player1.get();
  }
  return player2.get();
}

void Board::setPlayer(std::shared_ptr<Player> player)
{
  if (player->getPlayerNum() == 1) player1 = player;
  if (player->getPlayerNum() == 2) player2 = player;
}

void Board::startTurn()
{
  auto activePlayer = getPlayer(active);
  activePlayer->startTurn();
  APNAP(When::Start);
}

void Board::endturn()
{
  APNAP(When::End);
  active = active % 2 + 1;
}

void Board::attack(int i)
{
  getPlayer(active)->attack(i, active%2+1);
}

void Board::attack(int i, int t)
{
  getPlayer(active)->attack(i, active%2+1, t);
}

void Board::play(int i)
{
  getPlayer(active)->play(active, i);
}

void Board::play(int i, int p, char t)
{
  getPlayer(active)->play(active, i, p, t);
}

void Board::use(int i)
{
  getPlayer(active)->use(i, active);
}

void Board::use(int i, int p, char t)
{
  getPlayer(active)->use(i, p, t);
}


void Board::inspect(int i)
{
  std::vector<card_template_t> m = getPlayer(active)->inspectMinion(i);
  int numEnchantments = m.size() - 1;
  if (numEnchantments < 0) return;
  card_template_t card = m.at(0);
  int cardSize = card.size();
  for (auto line : card) std::cout << line << std::endl;
  int numLines = numEnchantments / 5;
  if (numEnchantments%5 != 0) numLines++;
  for (int i = 0; i < numLines; ++i) {
    for (int j = 0; j < cardSize; ++j) {
      for (int k = 1; k <= 5; ++k) {
        if (k+i*5 > numEnchantments) break;
        std::cout << m.at(k+i*5).at(j);
      }
      std::cout << std::endl;
    }
  }
}

void Board::display()
{
  const int width = CARD_TEMPLATE_EMPTY.at(0).length();
  const int height = CARD_TEMPLATE_EMPTY.size();
  std::cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
  for (int i = 0; i < 5*width; ++i) std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  std::cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;

  card_template_t ritual1 = getPlayer(1)->showRitual();
  card_template_t ritual2 = getPlayer(2)->showRitual();
  card_template_t grave1 = getPlayer(1)->showTopGraveyard();
  card_template_t grave2 = getPlayer(2)->showTopGraveyard();
  card_template_t p1 = getPlayer(1)->display();
  card_template_t p2 = getPlayer(2)->display();
  std::vector<card_template_t> minions1 = getPlayer(1)->displayMinions();
  int numMinions1 = minions1.size();
  std::vector<card_template_t> minions2 = getPlayer(2)->displayMinions();
  int numMinions2 = minions2.size();

  for (int i = 0; i < height; ++i) {
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    for (int j = 0; j < 5; ++j) {
      if (j == 0) std::cout << grave1.at(i);
      else if (j == 2) std::cout << p1.at(i);
      else if (j == 4) std::cout << ritual1.at(i);
      else for (int empty = 0; empty < width; empty++) std::cout << " ";
    }
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    std::cout << std::endl;
  }
  for (int i = 0; i < height; ++i) {
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    for (int j = 0; j < 5; ++j) {
      if (j+1 > numMinions1) std::cout << CARD_TEMPLATE_BORDER.at(i);
      else std::cout << minions1.at(j).at(i);
    }
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    std::cout << std::endl;
  }

  for (auto line : CENTRE_GRAPHIC) std::cout << line << std::endl;;

  for (int i = 0; i < height; ++i) {
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    for (int j = 0; j < 5; ++j) {
      if (j+1 > numMinions2) std::cout << CARD_TEMPLATE_BORDER.at(i);
      else std::cout << minions2.at(j).at(i);
    }
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    std::cout << std::endl;
  }
  for (int i = 0; i < height; ++i) {
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    for (int j = 0; j < 5; ++j) {
      if (j == 0) std::cout << grave2.at(i);
      else if (j == 2) std::cout << p2.at(i);
      else if (j == 4) std::cout << ritual2.at(i);
      else for (int empty = 0; empty < width; empty++) std::cout << " ";
    }
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    std::cout << std::endl;
  }
  std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
  for (int i = 0; i < 5*width; ++i) std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;
}

//   std::vector<std::shared_ptr<Card>> hand;
void Board::showHand()
{
  std::vector<card_template_t> m = getPlayer(active)->displayHand();
  int num = m.size();
  if (num == 0) return; // This is not possible so remove this line if you want
  card_template_t card = m.at(0);
  int cardSize = card.size();
  for (int j = 0; j < cardSize; ++j) {
    for (int k = 0; k < num; ++k) {
      std::cout << m.at(k).at(j);
    }
    std::cout << std::endl;
  }
}

void Board::APNAP(When when, int playedMinion) 
{
  if (active == 1) {
    for (int i = 0; i < player1->getNumMinions(); ++i) {
      if (i == playedMinion) continue;
      player1->getMinion(i)->useTriggered(1,playedMinion,true,when);
    }
    player1->getRitual()->useAbility(1,playedMinion,true,when);
    if (when == When::Start || when == When::End) return;
    for (int i = 0; i < player2->getNumMinions(); ++i) player2->getMinion(i)->useTriggered(2,playedMinion,false,when);
    player2->getRitual()->useAbility(2,playedMinion,false,when);
  } else {
    for (int i = 0; i < player2->getNumMinions(); ++i) {
      if (i == playedMinion) continue;
      player2->getMinion(i)->useTriggered(2,playedMinion,true,when);
    }
    player2->getRitual()->useAbility(1,playedMinion,true,when);
    if (when == When::Start || when == When::End) return;
    for (int i = 0; i < player1->getNumMinions(); ++i) player1->getMinion(i)->useTriggered(1,playedMinion,false,when);
    player1->getRitual()->useAbility(1,playedMinion,false,when);
  }
}

/////// testing mode only ////////
void Board::draw() {
  getPlayer(active)->draw();
}

void Board::discard(int i) {
  getPlayer(active)->discard(i);
}
