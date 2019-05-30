#include "jumpingstickman.h"
#include "collision.h"

JumpingStickman::JumpingStickman(int floor, int jumpImpulse, int maxJumpCount, int gravity)
    : floor(floor), jumpImpulse(jumpImpulse), jumpVelocity(0), gravity(gravity), jumpCount(0), maxJumpCount(maxJumpCount)  {

}

JumpingStickman::~JumpingStickman() {

}

void JumpingStickman::jump() {
    jumpVelocity = jumpImpulse;
    grounded = false;
    jumpCount++;
}

bool JumpingStickman::canJump() {
    return jumpCount < maxJumpCount;
}

void JumpingStickman::handleInput(QKeyEvent &event) {
    if (event.key() == Qt::Key_Space && !event.isAutoRepeat() && canJump()) {
        jump();
    }
}

int JumpingStickman::getJumpVelocity() {
    return jumpVelocity;
}

void JumpingStickman::update(std::vector<std::unique_ptr<Entity>> &obstacles) {
    Coordinate &ac = getCoordinate();
    int newY = ac.getYCoordinate() + jumpVelocity;
    colliding = false;

    // Check for collisions
    for (auto &other : obstacles) {
        Collision::CollisonResult col = Collision::moveCast(*this, *other, 0, jumpVelocity);

        if (col.overlapped) {
            int by = other->getCoordinate().getYCoordinate();
            if (col.down && jumpVelocity < 0) {
                // Hitting obstacle from above
                jumpVelocity = 0;
                grounded = true;
                jumpCount = 0;
                newY = by + other->height() + 1;
            } else if (col.up) {
                // Hitting obstacle from below
                jumpVelocity = 0;
                newY = by - height() - 1;
            } else {
                // Hidding obstacle from the side
                colliding = true;
            }
        }
    }

    // Check if we're below the floor
    if (newY <= floor) {
        newY = floor;
        grounded = true;
        jumpVelocity = 0;
        jumpCount = 0;
    }

    ac.setYCoordinate(newY);
    jumpVelocity += gravity;
}
