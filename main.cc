#include <fstream>
#include "deck.h"
#include "interface.h"

const int PLAYER1_SEED = 20824741;
const int PLAYER2_SEED = 20824742;

int main(int argc, const char *argv[]) 
{
  bool testingMode = false;
  bool g = false;
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
        } else if (cmd == "-deck2") {
          deck2File = fileName;
        } else if (cmd == "-init") {
          actionInput = new std::ifstream{fileName}; // must be deleted after
        }
      }
      if (cmd == "-testing") {
        testingMode = true;
      }
      if (cmd == "-graphics") {
        g = true;
      }
    }
  }
    
  std::ifstream defaultDeck1{"default.deck"};
  std::ifstream defaultDeck2{"default.deck"};
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

  if (g == true) return gdisplay(testingMode,b);

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
