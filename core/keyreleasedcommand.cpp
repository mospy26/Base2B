#include "keyreleasedcommand.h"

KeyReleasedCommand::KeyReleasedCommand(WalkingStickman& stickman)
    : Command(stickman)
{

}

void KeyReleasedCommand::execute(QInputEvent *event) {
    QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);

    if(keyEvent->key() == Qt::Key_Right && !keyEvent->isAutoRepeat()) {
        stickman->setMovingIndicators(false, stickman->isMovingLeft());
        stickman->setVelocity(0);
    }
    else if(keyEvent->key() == Qt::Key_Left && !keyEvent->isAutoRepeat()) {
        stickman->setMovingIndicators(stickman->isMovingRight(), false);
        stickman->setVelocity(0);
    }
}
