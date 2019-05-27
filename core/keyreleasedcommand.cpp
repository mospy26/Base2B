#include "keyreleasedcommand.h"

KeyReleasedCommand::KeyReleasedCommand(WalkingStickman& stickman)
    : Command(stickman)
{

}

void KeyReleasedCommand::execute(QInputEvent *event) {
    QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);

    stickman->setVelocity(0);

    if(keyEvent->key() == Qt::Key_Right && !keyEvent->isAutoRepeat()) {
        stickman->setMovingIndicators(false, stickman->isMovingLeft());
    }
    else if(keyEvent->key() == Qt::Key_Left && !keyEvent->isAutoRepeat()) {
        stickman->setMovingIndicators(stickman->isMovingRight(), false);
    }
}
