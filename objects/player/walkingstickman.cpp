#include "walkingstickman.h"

WalkingStickman::WalkingStickman(int floor, int jumpImpulse, int maxJumpCount, int gravity)
    : JumpingStickman(floor, jumpImpulse, maxJumpCount, gravity), reachedFlag(false), collidedPowerup(false) {

}

void WalkingStickman::update(std::vector<std::unique_ptr<Entity>>& obstacles) {

    Coordinate &ac = getCoordinate();
    int newY = ac.getYCoordinate() + jumpVelocity;
    colliding = false;

    ac.setXCoordinate(ac.getXCoordinate() + velocity);

    jumpImpulse = ability == Ability::HigherJumping ? 18 : 15;
    for (auto &other : obstacles) {
        if(other == nullptr) continue;
        Collision::CollisonResult col = Collision::moveCast(*this, *other, 0, jumpVelocity);

        if (col.overlapped && lives > 0) {
            if(ability != Ability::BreakObstacles) {
                colliding = true;
            } else if(ability == Ability::BreakObstacles && other->getName() != "flag") {
                other = nullptr;
            } else if(ability == Ability::BreakObstacles && other->getName() == "flag" && obstacles.size() == 1) { //the only obstacle is a flag
                colliding = true;
            }
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

void WalkingStickman::putBack() {
    setCoordinate(initialCoordinates);
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
    jumpImpulse = 22;
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

void WalkingStickman::provideAbility(enum Ability ability) {
    this->ability = ability;
}
