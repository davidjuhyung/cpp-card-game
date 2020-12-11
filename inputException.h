#ifndef INPUT_EXCEPTION_H
#define INPUT_EXCEPTION_H

#include <string>

class InputException {
  private:
    std::string reason;
    bool quit;
  public:
    InputException(std::string reason, bool quit = false): reason{reason}, quit{quit} {}
    std::string getReason() const { return reason; }
    bool getQuit() const { return quit; }
};

#endif