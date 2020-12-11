#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// our files
#include "player.h"
#include "deck.h"
#include "board.h"

void readAction(std::string action) {
  if (action == "help"){
    std::cout << "Commands: help -- Display this message." << std::endl;
  } else if (action == "end") {

  } else if (action == "quit") {
  
  } else if (action == "draw") {

  } else if (action == "discard") {

  } else if (action == "attack") {

  } else if (action == "play") {
  
  } else if (action == "use") {

  } else if (action == "describe") {
    
  } else if (action == "hand") {

  } else if (action == "board") {
  
  } else {
    std::cerr << "Invalid action." << std::endl;
  }
}

int main(int argc, const char *argv[]) {
  bool testingMode = false;
  std::ifstream defaultDeck{"./codeForStudents/default.deck"};
  std::istream *actionInput = &std::cin;
  //Board b;
  std::string name1 = "", name2 = "";
  // auto deck1 = initialize(defaultDeck, &b);
  // auto deck2 = deck1;

  // read action line arguments
  // for (int i = 1; i < argc; i++) {
  //   std::string cmd{argv[i]};
  //   if (cmd.at(0) == '-') {
  //     std::string fileName = argv[++i]; 
  //     std::ifstream infile{fileName}; 
  //     if (cmd == "-deck1" || cmd == "-deck2") {
  //       auto deck = initialize(infile, &b);
  //       if (cmd == "-deck1") {
  //         deck1 = deck;
  //       } else {
  //         deck2 = deck;
  //       }
  //     }
  //     if (cmd == "-init") {
  //       actionInput = new std::ifstream{fileName}; // must be deleted after
  //     }
  //     if (cmd == "-testing") {
  //       testingMode = true;
  //     }
  //   }
  // }

  std::getline(*actionInput, name1);
  std::getline(*actionInput, name2);
  // auto p1 = std::make_shared<Player>(1, name1, deck1);
  // auto p2 = std::make_shared<Player>(2, name2, deck2);
  // b.setPlayer(p1);
  // b.setPlayer(p2);

  std::string action;
  while (std::getline(*actionInput, action)) {
    readAction(action);
  }
  // if (actionInput != &std::cin) {
  //   std::cout << "File is read" << std::endl;
  //   delete actionInput;
  //   actionInput = &std::cin;
  // }
  while (std::getline(*actionInput, action)) {
    readAction(action);
  }
}