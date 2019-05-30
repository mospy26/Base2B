#include "lifepowerup.h"

LifePowerup::LifePowerup(Coordinate coordinate, int velocity) : Powerup("life", coordinate, velocity) {

}

void LifePowerup::collisionLogic(Stickman &stickman) {
    Powerup::collisionLogic(stickman);
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    if(walkingStickman->collidedWithPowerup()) {
        upgradeStickman(*walkingStickman);
    }
}

void LifePowerup::upgradeStickman(WalkingStickman &stickman) {
    stickman.setLives(stickman.getLives() + 1);
}
