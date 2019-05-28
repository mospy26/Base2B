#include "normalpowerup.h"

NormalPowerup::NormalPowerup(Coordinate coordinate, int velocity)
    : Powerup("normal", coordinate, velocity)
{

}

void NormalPowerup::collisionLogic(Stickman &stickman) {
    Powerup::collisionLogic(stickman);
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    if(walkingStickman->collidedWithPowerup()) {
        upgradeStickman(stickman);
    }
}

void NormalPowerup::upgradeStickman(Stickman &stickman) {
    stickman.setSize("normal");
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    walkingStickman->provideAbility(Ability::NoEffect);
}
