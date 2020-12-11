#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>

// our files
#include "player.h"
#include "deck.h"
#include "board.h"

void readAction(std::string action, std::vector<std::string> params, Board &b) 
{
  if (action == "help")
  {
    std::cout << "help -- Display this message." << std::endl;
    std::cout << "end -- End the current player’s turn." << std::endl;
    std::cout << "quit -- End the game." << std::endl;
    std::cout << "attack minion other-minion -- Orders minion to attack other-minion." << std::endl;
    std::cout << "attack minion -- Orders minion to attack the opponent." << std::endl;
    std::cout << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << std::endl;
    std::cout << "use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player. inspect minion -- View a minion’s card and all enchantments on that minion." << std::endl;
    std::cout << "hand -- Describe all cards in your hand." << std::endl;
    std::cout << "board -- Describe all cards on the board." << std::endl;
  } 
  else if (action == "end")
  {
    b.endturn();
  }
  else if (action == "quit") 
  {
    throw "quit has been entered";
  } 
  else if (action == "draw") 
  {
    b.draw();
  }
  else if (action == "discard") 
  {
    if (params.size() == 1) {
      b.discard(std::stoi(params[0]));
    }
  } 
  else if (action == "attack") 
  {
    if (params.size() == 1) {
      b.attack(std::stoi(params[0]));
    } else if (params.size() == 2) {
      b.attack(std::stoi(params[0]), std::stoi(params[1]));
    }
  } 
  else if (action == "play") 
  {
    if (params.size() == 1) {
      b.play(std::stoi(params[0]));
    } else if (params.size() == 3) {
      b.play(std::stoi(params[0]), std::stoi(params[1]), params[2][0]);
    }
  } 
  else if (action == "use") 
  {
    if (params.size() == 1) {
      b.use(std::stoi(params[0]));
    } else if (params.size() == 3) {
      b.use(std::stoi(params[0]), std::stoi(params[1]), params[2][0]);
    }
  } 
  else if (action == "inspect") 
  {
    if (params.size() == 1) {
      b.inspect(std::stoi(params[0]));
    } 
  } 
  else if (action == "hand") 
  {
    b.showHand();
  } 
  else if (action == "board") 
  {
    b.display();
  } 
  else 
  {
    std::cerr << "Invalid action." << std::endl;
  }
}

int main(int argc, const char *argv[]) 
{
  bool testingMode = false;
  std::ifstream defaultDeck{"./codeForStudents/default.deck"};
  std::istream *actionInput = &std::cin;
  Board b;
  std::string name1 = "", name2 = "";
  auto deck1 = initialize(defaultDeck, &b);
  auto deck2 = deck1;

  // read action line arguments
  for (int i = 1; i < argc; i++) {
    std::string cmd{argv[i]};
    if (cmd.at(0) == '-') {
      std::string fileName = argv[++i]; 
      std::ifstream infile{fileName}; 
      if (cmd == "-deck1" || cmd == "-deck2") {
        auto deck = initialize(infile, &b);
        if (cmd == "-deck1") {
          deck1 = deck;
        } else {
          deck2 = deck;
        }
      }
      if (cmd == "-init") {
        actionInput = new std::ifstream{fileName}; // must be deleted after
      }
      if (cmd == "-testing") {
        testingMode = true;
      }
    }
  }

  // draw 5 cards
  
  std::getline(*actionInput, name1);
  std::getline(*actionInput, name2);
  auto p1 = std::make_shared<Player>(1, name1, deck1);
  auto p2 = std::make_shared<Player>(2, name2, deck2);
  b.setPlayer(p1);
  b.setPlayer(p2);

  std::string action;
  while (std::getline(*actionInput, action)) {
    std::istringstream stream{action};
    std::vector<std::string> params;
    stream >> action;
    std::string s;
    while(stream >> s) {
      params.push_back(s);
    }
    readAction(action, params, b);  
  }
  if (actionInput != &std::cin) {
    delete actionInput;
    actionInput = &std::cin;
  }
  while (std::getline(*actionInput, action)) {
    try {
      std::istringstream stream{action};
      std::vector<std::string> params;
      stream >> action;
      std::string s;
      while(stream >> s) {
        params.push_back(s);
      }
      readAction(action, params, b);  
    } catch (const char* msg) {
      break;
    }
  }
}