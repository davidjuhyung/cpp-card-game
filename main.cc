#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// our files
#include "player.h"

int main(int argc, char const *argv[]) {
  std::string name1;
  std::string name2;
  std::string deck1;
  std::string deck2;

  // read command line arguments
  for (int i = 1; i < argc; i++) {
    std::string cmd{argv[i]};
    if (cmd.at(0) == '-') {
      std::string fileName = argv[++i]; 
      std::ifstream infile{fileName}; 
      if (cmd == "-deck1" || cmd == "-deck2") {
        if (cmd == "-deck1") {
          // [TODO] assign the deck to player 1
          deck1 = fileName;
          std::cout << "Player 1's deck is composed of: " << std::endl;
        } else {
          // [TODO] assign the deck to player 2
          deck2 = fileName;
          std::cout << "Player 2's deck is composed of: " << std::endl;
        }
        // Echo back the cards in the deck
        std::string cardName;
        while (infile >> cardName) {
          std::cout << cardName << std::endl;
        }
      }
      if (cmd == "-init") {
        std::cout << "-init entered" << std::endl;
        infile >> name1;
        infile >> name2;
        // [TODO] read play()
      }
      if (cmd == "-testing") {
        std::cout << "-testing entered" << std::endl;
      }
    }
  }

  // create Players
  Player p1{name1};
  Player p2{name2};

  std::cout << "Player 1's name: " << p1.name << std::endl;
  std::cout << "Player 2's name: " << p2.name << std::endl;
}
