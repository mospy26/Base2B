#include "lifepowerup.h"

LifePowerup::LifePowerup(Coordinate coordinate, int velocity)
    : Powerup("life",coordinate, velocity)
{

}

void LifePowerup::collisionLogic(Stickman &stickman) {
    Powerup::collisionLogic(stickman);
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    if(walkingStickman->collidedWithPowerup()) {
        upgradeStickman(stickman);
    }
}

void LifePowerup::upgradeStickman(Stickman &stickman) {
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    walkingStickman->setLives(walkingStickman->getLives() + 1);
}
