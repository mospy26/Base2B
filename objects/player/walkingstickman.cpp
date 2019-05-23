#include "walkingstickman.h"

WalkingStickman::WalkingStickman(int floor, int jumpImpulse, int maxJumpCount, int gravity)
    : JumpingStickman(floor, jumpImpulse, maxJumpCount, gravity)
{

}

void WalkingStickman::update(std::vector<std::unique_ptr<Entity>>& obstacles) {

    JumpingStickman::update(obstacles);
    Coordinate& coordinate = getCoordinate();
    int newY = coordinate.getYCoordinate() + jumpVelocity;
    coordinate.setXCoordinate(coordinate.getXCoordinate() + velocity);

    if(blinker <= 0) {
        blinking = false;
    }

    for (auto &other : obstacles) {
        Collision::CollisonResult col = Collision::moveCast(*this, *other, 0, jumpVelocity);

        if (col.overlapped) {
            putBack();
            // restart
            // stickman crashed
            // blink : extension
            colliding = true;
            if(!blinking) blinker = 3;
            blinking = true;
        }
    }
}

void WalkingStickman::handleInput(QKeyEvent& event) {

    //Call the handle input method from JumpingStickman that records the jumping key
    JumpingStickman::handleInput(event);

    if(event.key() == Qt::Key_Left && !event.isAutoRepeat()) {
        velocity = -8;
        movingLeft = true;
    }
    if(event.key() == Qt::Key_Right && !event.isAutoRepeat()) {
        velocity = 8;
        movingRight = true;
    }

}

void WalkingStickman::putBack() {
    setCoordinate(initialCoordinates);
}

void WalkingStickman::blink(int time) {
    if(time%30 > 10) {
        blinker -= 1;
        sprite.fill(Qt::transparent);
    }
    else {
        std::string spritePath = ":sprites/sprite";
        setSprite(spritePath.append(std::to_string((time/5)%2)).append(".png"));
    }
}

bool WalkingStickman::getBlinking() const {
    return blinking;
}

void WalkingStickman::setBlinker(int blinkerValue) {
    blinker = blinkerValue;
}

int WalkingStickman::getBlinker() const {
    return blinker;
}

void WalkingStickman::handleReleasedInput(QKeyEvent& event) {
    if(event.key() == Qt::Key_Right && !event.isAutoRepeat()) {
        movingRight = false;
        velocity = 0;
    }
    if(event.key() == Qt::Key_Left && !event.isAutoRepeat()) {
        movingLeft = false;
        velocity = 0;
    }
}

int WalkingStickman::getVelocity() const {
    return velocity;
}

void WalkingStickman::setVelocity(int v) {
    velocity = v;
}

bool WalkingStickman::isMovingRight() const {
    return movingRight;
}

bool WalkingStickman::isMovingLeft() const {
    return movingLeft;
}

void WalkingStickman::setInitialCoordinates(Coordinate& coordinate) {
    initialCoordinates = coordinate;
}
