#ifndef SECTION_H
#define SECTION_H

#include "Command.h"

class Section {

public:
    virtual void inputCommand(Command) = 0;
//    virtual void init() = 0;

};

#endif // SECTION_H
