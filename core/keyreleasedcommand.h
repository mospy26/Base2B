#ifndef KEYRELEASEDCOMMAND_H
#define KEYRELEASEDCOMMAND_H

#include "command.h"

class KeyReleasedCommand : public Command
{
public:
    KeyReleasedCommand(WalkingStickman& stickman);

    void execute(QInputEvent* event) override;
};

#endif // KEYRELEASEDCOMMAND_H
