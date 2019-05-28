#ifndef GIANTPOWERUP_H
#define GIANTPOWERUP_H

#include "powerup.h"

class GiantPowerup : public Powerup
{
public:
    GiantPowerup(Coordinate coordinate, int velocity);

    void collisionLogic(Stickman& stickman) override;
    void upgradeStickman(Stickman& stickman) override;
};

#endif // GIANTPOWERUP_H
