#include "giantpowerup.h"

GiantPowerup::GiantPowerup(Coordinate coordinate, int velocity)
    : Powerup("giant", coordinate, velocity)
{

}

void GiantPowerup::collisionLogic(Stickman& stickman) {
    Powerup::collisionLogic(stickman);
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    if(walkingStickman->collidedWithPowerup()) {
        upgradeStickman(stickman);
    }
}

void GiantPowerup::upgradeStickman(Stickman &stickman) {
    stickman.setSize("giant");
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    walkingStickman->provideAbility(Ability::BreakObstacles);
}
