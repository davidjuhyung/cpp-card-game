#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <ncurses.h>
#include <unistd.h>

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

void refreshBoard(std::stringstream &snap, int active, int highlight = -1) {
  int lineNum = 1;
  std::string line;
  while (getline(snap,line)) {
    if (lineNum == 1 || lineNum == 56 || (active == 1 && lineNum > 23) || (active == 2 && lineNum <= 33)) {
      mvaddstr(lineNum, 0, line.c_str());
      lineNum++;
      continue;
    }
    if (highlight == 6 || highlight == 7) {
      if ((active == 1 && lineNum > 12) || (active == 2 && lineNum <= 44)) {
        mvaddstr(lineNum, 0, line.c_str());
        lineNum++;
        continue;
      }
    }
    for (int i = 0; i < 5; ++i) {
      mvaddstr(lineNum, 0, line.substr(0,1).c_str());
      if (i == highlight && lineNum >= 13 && lineNum <= 44) attron(A_REVERSE);
      else if (highlight == 6 && active == 1 && i == 4) attron(A_REVERSE);
      else if (highlight == 6 && active == 2 && i == 0) attron(A_REVERSE);
      else if (highlight == 7 && i == 2) attron(A_REVERSE);
      else if (highlight == 7 && i == 2) attron(A_REVERSE);
      mvaddstr(lineNum, i*33+1, line.substr(i*33+1,33).c_str());
      attroff(A_REVERSE);
      mvaddstr(lineNum, 166, line.substr(165,1).c_str());
    }
    lineNum++;
  }
  refresh();
  std::stringstream().swap(snap);
}

void refreshHand(std::stringstream &snap, int highlight = -1) {
  int lineNum = 58;
  std::string e{"                                 "};
  int empty;
  std::string line;
  while (getline(snap,line)) {
    empty = line.length()/33-1;
    for (int i = 0; i < 5; ++i) {
      if (i == highlight) attron(A_REVERSE);
      if (i <= empty) mvaddstr(lineNum, i*33, line.substr(i*33,33).c_str());
      else mvaddstr(lineNum, i*33, e.c_str());
      attroff(A_REVERSE);
    }
    lineNum++;
  }
  refresh();
  std::stringstream().swap(snap);
}

void refreshInspect(std::stringstream &snap, bool clear = false) {
  int lineNum = 40;
  std::string line;
  std::string e = "                                                                                                                                                                                                                               ";
  if (clear) {
    for (int i = 0; i < 50; ++i) {
      mvaddstr(lineNum,170,e.c_str());
      lineNum++;
    }
    refresh();
    std::stringstream().swap(snap);
  }
  while (getline(snap,line)) {
    mvaddstr(lineNum,170,line.c_str());
    lineNum++;
  }
  refresh();
  std::stringstream().swap(snap);
}

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

  if (g == true) {
    initscr();
    cbreak();
    noecho();
    curs_set(false);

    std::stringstream pic;
    b.display(pic);
    refreshBoard(pic,1);

    mvaddstr(57,1,"Your Hand:");

    std::stringstream h;
    b.showHand(h);
    refreshHand(h);

    std::stringstream ins;

    refresh();
    keypad(stdscr,true);
    std::string choices[6] = {"Play","Attack","Use","Inspect","End","Quit"};
    int c;
    int highlight = 0;
    while (true) {
      for (int i = 0; i < 6; ++i) {
        if (i == highlight) attron(A_REVERSE);
        mvaddstr(i+72,1,choices[i].c_str());
        attroff(A_REVERSE);
      }
      c = getch();
      if (c == KEY_UP) highlight--;
      else if (c == KEY_DOWN) highlight++;
      if (highlight < 0) highlight = 0;
      if (highlight > 5) highlight = 5;
      if (c == 10) {
        if (highlight == 0) {
          c = 0;
          highlight = 0;
          while (c != 10) {
            b.showHand(h);
            refreshHand(h,highlight);
            c = getch();
            if (c == KEY_LEFT) highlight--;
            else if (c == KEY_RIGHT) highlight++;
            if (highlight < 0) highlight = 0;
            if (highlight > 4) highlight = 4;
          }
          c = 0;
          int cardNum = highlight;
          highlight = 10;
          while (c != 10) {
            if (highlight == 10) {
              attron(A_REVERSE);
              mvaddstr(77,1,"No Target");
              attroff(A_REVERSE);
              b.display(pic);
              refreshBoard(pic,b.active);
            } else {
              b.display(pic);
              mvaddstr(77,1,"No Target");
              if (highlight == 11) refreshBoard(pic,1,6);
              else if (highlight == 12) refreshBoard(pic,2,6);
              else refreshBoard(pic,highlight/5+1,highlight%5);
            }
            c = getch();
            if (c == KEY_LEFT) highlight--;
            else if (c == KEY_RIGHT) highlight++;
            if (highlight < 0) highlight = 0;
            if (highlight > 10) highlight = 10;
            if (c == KEY_DOWN) highlight = 11;
            if (c == KEY_UP) highlight = 12;
          }
          try {
            if (highlight == 10) b.play(cardNum+1,testingMode);
            else if (highlight == 11) b.play(cardNum+1,1,'r',testingMode);
            else if (highlight == 12) b.play(cardNum+1,2,'r',testingMode);
            else b.play(cardNum+1,highlight/5+1,highlight%5+1,testingMode);
          } catch (InputException err) {
            mvaddstr(79,1,err.getReason().c_str());
            getch();
            mvaddstr(79,1,"                                                                                   ");
            if (err.getQuit()) break;
          } catch (...) {
            mvaddstr(79,1,"Try another Target");
            getch();
            mvaddstr(79,1,"                                                                                    ");
          }
        } else if (highlight == 2) {
          c = 0;
          highlight = 0;
          while (c != 10) {
            b.display(pic);
            refreshBoard(pic,b.active,highlight);
            c = getch();
            if (c == KEY_LEFT) highlight--;
            else if (c == KEY_RIGHT) highlight++;
            if (highlight < 0) highlight = 0;
            if (highlight > 4) highlight = 4;
          }
          c = 0;
          int minionNum = highlight;
          highlight = 10;
          while (c != 10) {
            if (highlight == 10) {
              attron(A_REVERSE);
              mvaddstr(77,1,"No Target");
              attroff(A_REVERSE);
              b.display(pic);
              refreshBoard(pic,b.active);
            } else {
              mvaddstr(77,1,"No Target");
              b.display(pic);
              if (highlight == 11) refreshBoard(pic,1,6);
              else if (highlight == 12) refreshBoard(pic,2,6);
              else refreshBoard(pic,highlight/5+1,highlight);
            }
            c = getch();
            if (c == KEY_LEFT) highlight--;
            else if (c == KEY_RIGHT) highlight++;
            if (highlight < 0) highlight = 0;
            if (highlight > 10) highlight = 10;
            if (c == KEY_DOWN) highlight = 11;
            if (c == KEY_UP) highlight = 12;
          }
          try {
            if (highlight == 10) b.use(minionNum);
            else if (highlight == 11) b.use(minionNum+1,1,'r',testingMode);
            else if (highlight == 12) b.use(minionNum+1,2,'r',testingMode);
            else b.use(minionNum+1,highlight/5+1,highlight%5+1,testingMode);
          } catch (InputException err) {
            mvaddstr(79,1,err.getReason().c_str());
            getch();
            mvaddstr(79,1,"                                                                                   ");
            if (err.getQuit()) break;
          } catch (...) {
            mvaddstr(79,1,"Try another Target");
            getch();
            mvaddstr(79,1,"                                                                                    ");
          }
        } else if (highlight == 1) {
          highlight = 0;
          c = 0;
          while (c != 10) {
            b.display(pic);
            refreshBoard(pic,b.active,highlight);
            c = getch();
            if (c == KEY_LEFT) highlight--;
            else if (c == KEY_RIGHT) highlight++;
            if (highlight < 0) highlight = 0;
            if (highlight > 4) highlight = 4;
          }
          c = 0;
          int minionNum = highlight;
          highlight = 5;
          while (c != 10) {
            b.display(pic);
            if (highlight == 5) refreshBoard(pic,b.active%2+1,7);
            else refreshBoard(pic,b.active%2+1,highlight);
            c = getch();
            if (c == KEY_LEFT) highlight--;
            else if (c == KEY_RIGHT) highlight++;
            if (highlight < 0) highlight = 0;
            if (highlight > 5) highlight = 5;
            if (c == KEY_UP || c == KEY_DOWN) highlight = 5;
          }
          try {
            if (highlight == 5) b.attack(minionNum+1);
            else b.attack(minionNum+1,highlight%5+1);
          } catch (InputException err) {
            mvaddstr(79,1,err.getReason().c_str());
            getch();
            mvaddstr(79,1,"                                                                                   ");
            if (err.getQuit()) break;
          } catch (...) {
            mvaddstr(79,1,"Try another Target");
            getch();
            mvaddstr(79,1,"                                                                                    ");
          }
        } else if (highlight == 3) {
          highlight = 0;
          c = 0;
          while (c != 10) {
            b.display(pic);
            refreshBoard(pic,b.active,highlight);
            c = getch();
            if (c == KEY_LEFT) highlight--;
            else if (c == KEY_RIGHT) highlight++;
            if (highlight < 0) highlight = 0;
            if (highlight > 4) highlight = 4;
          }
          try {
            b.inspect(highlight+1,ins);
            refreshInspect(ins);
            getch();
            refreshInspect(ins,true);
          } catch (InputException err) {
            mvaddstr(79,1,err.getReason().c_str());
            getch();
            mvaddstr(79,1,"                                                                                    ");
            if (err.getQuit()) break;
          } catch (...) {
            mvaddstr(79,1,"Try another Target");
            getch();
            mvaddstr(79,1,"                                                                                    ");
          }
        } else if (highlight == 4) {
          b.endturn();
          c = 0;
          highlight = 0;
        } else if (highlight == 5) {
          highlight = 0;
          c = 0;
          break;
        }
        b.display(pic);
        refreshBoard(pic,b.active);
        b.showHand(h);
        refreshHand(h);
        mvaddstr(77,4,"        ");
      }
    }

    getch();
    endwin();
    return 0;
  }
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
 