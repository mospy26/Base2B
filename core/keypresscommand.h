#ifndef KEYPRESSCOMMAND_H
#define KEYPRESSCOMMAND_H

#include "command.h"

class KeyPressCommand : public Command
{
public:
    KeyPressCommand(WalkingStickman& stickman);

    void execute(QInputEvent* event) override;
};

#endif // KEYPRESSCOMMAND_H
