#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// our files
#include "player.h"
#include "deck.h"
#include "board.h"

int main(int argc, char const *argv[]) {
  bool testingMode = false;
  bool init = false;
  std::ifstream defaultDeck{"default.deck"};
  std::istream actionInput;
  Board b;
  std::string name1 = "", name2 = "";
  auto deck1 = initialize(defaultDeck, &b);
  auto deck2 = deck1;

  // read command line arguments
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
        init = true;
        actionInput = infile;
      }
      if (cmd == "-testing") {
        testingMode = true;
      }
    }
  }
  if (!init) actionInput = std::cin;

  std::string command;

  actionInput >> name1;
  actionInput >> name2;
  auto p1 = std::make_shared<Player>(name1,deck1);
  auto p2 = std::make_shared<Player>(name2,deck2);
  b.setPlayer(1,p1);
  b.setPlayer(2,p2);
  

  while (actionInput >> command && init) {
    if (command == "help"){
      std::cout << "Commands: help -- Display this message." << std::endl;

    }
    if (command == "end") {

    }
    if (command == "quit") {
      break;
    }
    if (command == "draw") {

    }
    if (command == "discard") {

    }
    if (command == "attack") {
      attack();
    }
    if (command == "play") {
      int i;
    }
    if (command == "use") {

    }
    if (command == "describe") {
      
    }
    if (command == "hand") {

    }
    if (command == "board") {
      
    }
    else{
      std::cerr << "Invalid command."<< std::endl;
    }
  }
}
