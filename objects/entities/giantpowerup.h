#ifndef GIANTPOWERUP_H
#define GIANTPOWERUP_H

#include "powerup.h"

class GiantPowerup : public Powerup
{
public:
    GiantPowerup(std::string name, Coordinate coordinate, int velocity);

    void collisionLogic(Stickman& stickman) override;
    void updateCoordinate() override;
    void upgradeStickman(Stickman& stickman) override;
};

#endif // GIANTPOWERUP_H
