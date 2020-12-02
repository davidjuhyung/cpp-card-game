#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int main(int argc, char const *argv[]) {
  std::string deck1;
  std::string deck2;

  // read command line arguments
  for (int i = 1; i < argc; i++) {
    std::string cmd{argv[i]};
    if (cmd.at(0) == '-') {
      if (cmd == "-deck1" || cmd == "-deck2") {
        std::string fileName = argv[++i]; // Note: Assume when there is a deck1 command line argument, it is followed by a filename. 
        std::ifstream infile{fileName}; 
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
      }
      if (cmd == "-testing") {
        std::cout << "-testing entered" << std::endl;
      }
    }
  }
}
