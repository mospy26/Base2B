#include "giantpowerup.h"

GiantPowerup::GiantPowerup(std::string name, Coordinate coordinate, int velocity)
    : Powerup(name, coordinate, velocity)
{

}

void GiantPowerup::collisionLogic(Stickman& stickman) {
    if(stickman.isColliding()) {
        upgradeStickman(stickman);
    }
}

void GiantPowerup::upgradeStickman(Stickman &stickman) {
    stickman.setSize("giant");
}

void GiantPowerup::updateCoordinate() {
    getCoordinate().setYCoordinate(getCoordinate().getYCoordinate() - 1);
    getCoordinate().setXCoordinate(getCoordinate().getXCoordinate() - getVelocity());
}
