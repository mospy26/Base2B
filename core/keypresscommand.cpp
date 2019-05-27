#include "keypresscommand.h"

KeyPressCommand::KeyPressCommand(Stage3Dialog& dialog, WalkingStickman& stickman)
    : Command(dialog, stickman)
{

}

void KeyPressCommand::execute(QInputEvent* event) {
    QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);

    if(keyEvent->key() == Qt::Key_Right && !keyEvent->isAutoRepeat()) {
        stickman->setVelocity(8);
    }
    else if(keyEvent->key() == Qt::Key_Left && !keyEvent->isAutoRepeat()) {
        stickman->setVelocity(-8);
    }
    if(keyEvent->key() == Qt::Key_Space && !keyEvent->isAutoRepeat()) {
        stickman->jump();
    }
}
