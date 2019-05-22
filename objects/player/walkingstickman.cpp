#include "walkingstickman.h"

WalkingStickman::WalkingStickman(int floor, int jumpImpulse, int maxJumpCount, int gravity)
    : JumpingStickman(floor, jumpImpulse, maxJumpCount, gravity)
{
    initialCoordinates = JumpingStickman::getCoordinate();
}

void WalkingStickman::update(std::vector<std::unique_ptr<Entity>>& obstacles) {
    //walk();
    Coordinate& coordinate = getCoordinate();
    int newY = coordinate.getYCoordinate() + jumpVelocity;
    coordinate.setXCoordinate(coordinate.getXCoordinate() + velocity);
    colliding = false;

    // Check for collisions
    for (auto &other : obstacles) {
        Collision::CollisonResult col = Collision::moveCast(*this, *other, 0, jumpVelocity);

        if(col.overlapped || col.left || col.right || col.up || col.down) {
            // restart
            // stickman crashed
            // blink : extension
            colliding = true;
            blinking = true;
            blinker = 3;
        }
    }

    if(blinker == 0) {
        blinking = false;
    }

    // Check if we're below the floor
    if (newY <= floor) {
        newY = floor;
        grounded = true;
        jumpVelocity = 0;
        jumpCount = 0;
    }

    coordinate.setYCoordinate(newY);
    jumpVelocity += gravity;
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
    if(time%20 > 10) {
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
