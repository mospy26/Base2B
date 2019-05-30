#include "normalpowerup.h"

NormalPowerup::NormalPowerup(Coordinate coordinate, int velocity) : Powerup("normal", coordinate, velocity) {

}

void NormalPowerup::collisionLogic(Stickman &stickman) {
    Powerup::collisionLogic(stickman);
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    if(walkingStickman->collidedWithPowerup()) {
        upgradeStickman(*walkingStickman);
    }
}

void NormalPowerup::upgradeStickman(WalkingStickman &stickman) {
    stickman.setSize("normal");
    stickman.provideAbility(Ability::NoEffect);
}
