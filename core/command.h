#ifndef COMMAND_H
#define COMMAND_H

#include "walkingstickman.h"

class Command
{
public:
    Command(WalkingStickman& stickman)
        : stickman(&stickman) {}

    virtual ~Command() {}

    virtual void execute(QInputEvent* event) = 0;

protected:
    WalkingStickman* stickman;
};

#endif // COMMAND_H
