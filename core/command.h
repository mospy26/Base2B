#ifndef COMMAND_H
#define COMMAND_H

#include "stage3dialog.h"
#include "walkingstickman.h"

class Command
{
public:
    Command(Stage3Dialog& dialog, WalkingStickman& stickman)
        : dialog(&dialog), stickman(&stickman) {}

    virtual ~Command() {}

    virtual void execute(QInputEvent* event) = 0;

protected:
    Stage3Dialog* dialog;
    WalkingStickman* stickman;
};

#endif // COMMAND_H
