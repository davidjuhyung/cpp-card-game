#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>

// our files
#include "player.h"
#include "deck.h"
#include "board.h"
#include "inputException.h"

const int PLAYER1_SEED = 20824741;
const int PLAYER2_SEED = 20824742;

void readAction(std::string action, std::vector<std::string> params, Board &b, bool testingMode) 
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
    throw InputException("Terminating the program...", true);
  } 
  else if (action == "attack") 
  {
    try {
      if (params.size() == 1) {
        b.attack(std::stoi(params[0]));
      } else if (params.size() == 2) {
        b.attack(std::stoi(params[0]), std::stoi(params[1]));
      } else {
        throw InputException("Invalid number of paramaters");
      }
    } catch (InputException err) {
      throw;
    } catch (...) {
      throw InputException("The parameter is not a valid number");
    }
  } 
  else if (action == "play") 
  {
    try {
      if (params.size() == 1) {
        b.play(std::stoi(params[0]), testingMode);
      } else if (params.size() == 3) {
        b.play(std::stoi(params[0]), std::stoi(params[1]), params[2][0], testingMode);
      } else {
        throw InputException("Invalid number of paramaters");
      }
    } catch (InputException err) {
      throw;
    } catch (...) {
      throw InputException("The parameter is not a valid number");
    }
  } 
  else if (action == "use") 
  {
    try {
      if (params.size() == 1) {
        b.use(std::stoi(params[0]), testingMode);
      } else if (params.size() == 3) {
        b.use(std::stoi(params[0]), std::stoi(params[1]), params[2][0], testingMode);
      } else {
        throw InputException("Invalid number of paramaters");
      }
    } catch (InputException err) {
      throw;
    } catch (...) {
      throw InputException("The parameter is not a valid number");
    }
  } 
  else if (action == "inspect") 
  {
    try {
      if (params.size() == 1) {
        b.inspect(std::stoi(params[0]));
      } else {
        throw InputException("Invalid number of paramaters");
      }
    } catch (InputException err) {
      throw;
    } catch (...) {
      throw InputException("The parameter is not a valid number");
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
  else if (action == "deck") 
  {
    b.displayPlayerDeck();
  }
  else if (action == "draw" && testingMode) 
  {
    b.draw();
  }
  else if (action == "discard" && testingMode) 
  {
    try { 
      if (params.size() == 1) {
        b.discard(std::stoi(params[0]));
      } else {
        throw InputException("Invalid number of paramaters");
      }
    } catch (InputException err) {
      throw;
    } catch (...) {
      throw InputException("The parameter is not a valid number");
    }
  }
  else 
  {
    throw InputException("Invalid command, type help for information");
  }
}

int main(int argc, const char *argv[]) 
{
  bool testingMode = false;
  Board b;
  std::istream *actionInput = &std::cin;
  std::string deck1File = "", deck2File = ""; 

  // read action line arguments
  for (int i = 1; i < argc; i++) {
    std::string cmd{argv[i]};
    if (cmd.at(0) == '-') {
      if (cmd == "-deck1" || cmd == "-deck2" || cmd == "-init") {
        std::string fileName = argv[++i]; // This is assumed to be true by the pdf
        if (cmd == "-deck1") {
          deck1File = fileName;
        } else if (cmd == "-deck2"){
          deck2File = fileName;
        } else if (cmd == "-init") {
          actionInput = new std::ifstream{fileName}; // must be deleted after
        }
      }
      if (cmd == "-testing") {
        testingMode = true;
      }
    }
  }
    
  std::ifstream defaultDeck1{"./codeForStudents/default.deck"};
  std::ifstream defaultDeck2{"./codeForStudents/default.deck"};
  std::ifstream d1{deck1File};
  std::ifstream d2{deck2File};
  auto deck1 = deck1File.empty() ? initialize(defaultDeck1, &b, PLAYER1_SEED, testingMode) : initialize(d1, &b, PLAYER1_SEED, testingMode);
  auto deck2 = deck2File.empty() ? initialize(defaultDeck2, &b, PLAYER2_SEED, testingMode) : initialize(d2, &b, PLAYER2_SEED, testingMode);

  // game setup
  const int NUMBER_OF_PLAYERS = 2;
  std::string names[NUMBER_OF_PLAYERS] = {"", ""};
  for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    if (actionInput == &std::cin) {
      std::cout << "Enter the name of player " << i+1 << ": ";
    }
    std::getline(*actionInput, names[i]);
    if (names[i].empty()) names[i] = "anon. player";
    if (actionInput->eof() && actionInput != &std::cin) {
      delete actionInput;
      actionInput = &std::cin;
    } 
  }

  auto p1 = std::make_unique<Player>(1, names[0], deck1);
  auto p2 = std::make_unique<Player>(2, names[1], deck2);
  b.setPlayer(std::move(p1));
  b.setPlayer(std::move(p2));
  b.startTurn();


  std::string action;
  while (std::getline(*actionInput, action) || action.empty() || !actionInput->eof()) { // to support both ctrl+D and quit command
    try { 
      if (actionInput->eof() && actionInput != &std::cin) {
        delete actionInput;
        actionInput = &std::cin;
      } else if (actionInput->eof()) throw InputException("Terminating the program...", true);
      if (action.empty()) continue;
      std::istringstream stream{action};
      std::vector<std::string> params;
      std::string action;
      stream >> action;
      std::string s;
      while(stream >> s) {
        params.push_back(s);
      }
      readAction(action, params, b, testingMode);
    } catch (InputException err) {
      std::cout << err.getReason() << std::endl;
      if (err.getQuit()) break;
    } 
  }
}
 