#include "tinypowerup.h"

TinyPowerup::TinyPowerup(Coordinate coordinate, int velocity) : Powerup("tiny", coordinate, velocity) {

}

void TinyPowerup::collisionLogic(Stickman& stickman) {
    Powerup::collisionLogic(stickman);
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    if(walkingStickman->collidedWithPowerup()) {
        upgradeStickman(*walkingStickman);
    }
}

void TinyPowerup::upgradeStickman(WalkingStickman& stickman) {
    stickman.setSize("tiny");
    stickman.provideAbility(Ability::NoEffect);
}
