#include "powerup.h"

Powerup::Powerup(std::string name, Coordinate coordinate, int velocity)
    : Entity(name, coordinate, velocity)
{

}

void Powerup::collisionLogic(Stickman& player) {
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&player);
    Collision::CollisonResult col = Collision::moveCast(*walkingStickman, *this, 0, walkingStickman->getJumpVelocity());

    if (col.overlapped && walkingStickman->getLives() > 0) {
        walkingStickman->setCollidedWithPowerup(true);
    }
}

void Powerup::updateCoordinate() {
    getCoordinate().setYCoordinate(getCoordinate().getYCoordinate() - 1);
    getCoordinate().setXCoordinate(getCoordinate().getXCoordinate() - getVelocity());
}

void Powerup::upgradeStickman(WalkingStickman& player) {

}
