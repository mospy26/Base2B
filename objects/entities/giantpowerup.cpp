#include "giantpowerup.h"

GiantPowerup::GiantPowerup(std::string name, Coordinate coordinate, int velocity)
    : Powerup(name, coordinate, velocity)
{

}

void GiantPowerup::collisionLogic(Stickman& stickman) {
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickman);
    if(stickman.isColliding()) {
        qDebug() << 2;
        upgradeStickman(*walkingStickman);
        walkingStickman->setCollidedWithPowerup(true);
    }
}

void GiantPowerup::upgradeStickman(Stickman &stickman) {
    stickman.setSize("giant");
}

void GiantPowerup::updateCoordinate() {
    getCoordinate().setYCoordinate(getCoordinate().getYCoordinate() - 1);
    getCoordinate().setXCoordinate(getCoordinate().getXCoordinate() - getVelocity());
}
