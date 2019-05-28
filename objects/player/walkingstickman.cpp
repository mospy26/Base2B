#include "walkingstickman.h"

WalkingStickman::WalkingStickman(int floor, int jumpImpulse, int maxJumpCount, int gravity)
    : JumpingStickman(floor, jumpImpulse, maxJumpCount, gravity), reachedFlag(false), collidedPowerup(false)
{

}

void WalkingStickman::update(std::vector<std::unique_ptr<Entity>>& obstacles) {

    Coordinate &ac = getCoordinate();
    int newY = ac.getYCoordinate() + jumpVelocity;
    colliding = false;

    ac.setXCoordinate(ac.getXCoordinate() + velocity);

//    if(blinker <= 0) {
//        blinking = false;
//    }

    for (auto &other : obstacles) {
        Collision::CollisonResult col = Collision::moveCast(*this, *other, 0, jumpVelocity);

        if (col.overlapped && lives > 0) {
            colliding = true;
        }
    }

    // Check if we're below the floor
    if (newY <= floor && lives > 0) {
        newY = floor;
        grounded = true;
        jumpVelocity = 0;
        jumpCount = 0;
    }

    ac.setYCoordinate(newY);
    jumpVelocity += gravity;
}

void WalkingStickman::handleInput(QKeyEvent& event) {

    //Call the handle input method from JumpingStickman that records the jumping key
    if(lives > 0) {
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

void WalkingStickman::setLives(int lives) {
    this->lives = lives;
}

int WalkingStickman::getLives() const {
    return lives;
}

void WalkingStickman::died() {
    jumpImpulse = 23;
    jump();
    velocity = 0;
}

void WalkingStickman::setReachedFlag(bool reached) {
    reachedFlag = reached;
}

bool WalkingStickman::isReachedFlag() const {
    return reachedFlag;
}

void WalkingStickman::setMovingIndicators(bool right, bool left) {
    movingLeft = left;
    movingRight = right;
}

void WalkingStickman::setCollidedWithPowerup(bool collided) {
    collidedPowerup = collided;
}

bool WalkingStickman::collidedWithPowerup() const {
    return collidedPowerup;
}
