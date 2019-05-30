#include "giantpowerup.h"

GiantPowerup::GiantPowerup(Coordinate coordinate, int velocity): Powerup("giant", coordinate, velocity) {

}

void GiantPowerup::collisionLogic(Stickman& stickman) {
    Powerup::collisionLogic(stickman);
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    if(walkingStickman->collidedWithPowerup()) {
        upgradeStickman(*walkingStickman);
    }
}

void GiantPowerup::upgradeStickman(WalkingStickman &stickman) {
    stickman.setSize("giant");
    stickman.provideAbility(Ability::BreakObstacles);
}
