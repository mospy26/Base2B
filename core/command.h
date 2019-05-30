#ifndef COMMAND_H
#define COMMAND_H

#include "walkingstickman.h"

class Command {
public:
    /**
     * @brief Command Sets the stickman as a stickman
     * @param stickman
     */
    Command(WalkingStickman& stickman)
        : stickman(&stickman) {}

    virtual ~Command() {}

    /**
     * @brief execute Defines what it means to handle a received command
     * @param event
     */
    virtual void execute(QInputEvent* event) = 0;

protected:
    WalkingStickman* stickman;
};

#endif // COMMAND_H
