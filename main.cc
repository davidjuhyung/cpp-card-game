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
  std::istream actionInput;
  Board b;
  std::string name1 = "", name2 = "";
  std::vector<std::shared_ptr<Card>> deck1 = nullptr, deck2 = nullptr;

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
        infile >> name1;
        infile >> name2;
        actionInput = infile;
      }
      if (cmd == "-testing") {
        testingMode = true;
      }
    }
  }
  // read action inputs


}