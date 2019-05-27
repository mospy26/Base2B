#include "keyreleasedcommand.h"

KeyReleasedCommand::KeyReleasedCommand(Stage3Dialog& dialog, WalkingStickman& stickman)
    : Command(dialog, stickman)
{

}

void KeyReleasedCommand::execute(QInputEvent *event) {
    QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);

    if(keyEvent->key() == Qt::Key_Right && !keyEvent->isAutoRepeat()) {
        stickman->setVelocity(0);
    }
    else if(keyEvent->key() == Qt::Key_Left && !keyEvent->isAutoRepeat()) {
        stickman->setVelocity(0);
    }

    int stickmanVelocity = stickman->getVelocity();
    stickman->setMovingIndicators(stickmanVelocity == 0 ? false: true, stickmanVelocity == 0 ? false : true);

}
