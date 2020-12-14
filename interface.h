#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <ncurses.h>
#include <unistd.h>

// our files
#include "player.h"
#include "board.h"
#include "inputException.h"

void readAction(std::string action, std::vector<std::string> params, Board &b, bool testingMode);

int gdisplay(bool testingMode, Board &b);

#endif
