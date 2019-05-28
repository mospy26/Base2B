#include "largepowerup.h"

LargePowerup::LargePowerup(Coordinate coordinate, int velocity)
    :   Powerup("large", coordinate, velocity)
{

}

void LargePowerup::collisionLogic(Stickman &stickman) {
    Powerup::collisionLogic(stickman);
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    if(walkingStickman->collidedWithPowerup()) {
        upgradeStickman(stickman);
    }
}

void LargePowerup::upgradeStickman(Stickman &stickman) {
    stickman.setSize("large");
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    walkingStickman->provideAbility(Ability::HigherJumping);
}
