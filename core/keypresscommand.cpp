#include "keypresscommand.h"

KeyPressCommand::KeyPressCommand(WalkingStickman& stickman) : Command(stickman) {

}

void KeyPressCommand::execute(QInputEvent* event) {
    QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);

    if(keyEvent->key() == Qt::Key_Right && !keyEvent->isAutoRepeat()) {
        stickman->setVelocity(8);
        stickman->setMovingIndicators(true, stickman->isMovingLeft());
    } else if(keyEvent->key() == Qt::Key_Left && !keyEvent->isAutoRepeat()) {
        stickman->setVelocity(-8);
        stickman->setMovingIndicators(stickman->isMovingRight(), true);
    }

    if(keyEvent->key() == Qt::Key_Space && !keyEvent->isAutoRepeat() && stickman->canJump()) {
        stickman->jump();
    }
}
