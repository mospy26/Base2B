#ifndef KEYPRESSCOMMAND_H
#define KEYPRESSCOMMAND_H

#include "command.h"

class KeyPressCommand : public Command
{
public:
    KeyPressCommand(Stage3Dialog& dialog, WalkingStickman& stickman);

    void execute(QInputEvent* event) override;
};

#endif // KEYPRESSCOMMAND_H
