#ifndef NORMALPOWERUP_H
#define NORMALPOWERUP_H

#include "powerup.h"

class NormalPowerup : public Powerup
{
public:
    NormalPowerup(Coordinate coordinate, int velocity);

    void collisionLogic(Stickman& stickman) override;
    void upgradeStickman(WalkingStickman& stickman) override;
};

#endif // NORMALPOWERUP_H
