#include "largepowerup.h"

LargePowerup::LargePowerup(Coordinate coordinate, int velocity)
    :   Powerup("large", coordinate, velocity)
{

}

void LargePowerup::collisionLogic(Stickman &stickman) {
    Powerup::collisionLogic(stickman);
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    if(walkingStickman->collidedWithPowerup()) {
        upgradeStickman(*walkingStickman);
    }
}

void LargePowerup::upgradeStickman(WalkingStickman &stickman) {
    stickman.setSize("large");
    stickman.provideAbility(Ability::HigherJumping);
}
