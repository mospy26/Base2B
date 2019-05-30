#ifndef LIFEPOWERUP_H
#define LIFEPOWERUP_H

#include "powerup.h"

class LifePowerup : public Powerup {
public:
    LifePowerup(Coordinate coordinate, int velocity);

    void collisionLogic(Stickman& stickman) override;
    void upgradeStickman(WalkingStickman& stickman) override;
};

#endif // LIFEPOWERUP_H
