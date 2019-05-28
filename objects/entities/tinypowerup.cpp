#include "tinypowerup.h"

TinyPowerup::TinyPowerup(Coordinate coordinate, int velocity)
    : Powerup("tiny", coordinate, velocity)
{

}

void TinyPowerup::collisionLogic(Stickman& stickman) {
    Powerup::collisionLogic(stickman);
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    if(walkingStickman->collidedWithPowerup()) {
        upgradeStickman(stickman);
    }
}

void TinyPowerup::upgradeStickman(Stickman &stickman) {
    stickman.setSize("tiny");
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    walkingStickman->provideAbility(Ability::NoEffect);
}
