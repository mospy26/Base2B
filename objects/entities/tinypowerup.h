#ifndef TINYPOWERUP_H
#define TINYPOWERUP_H

#include "powerup.h"

class TinyPowerup : public Powerup
{
public:
    TinyPowerup(Coordinate coordinate, int velocity);

    void collisionLogic(Stickman& stickman) override;
    void upgradeStickman(Stickman& stickman) override;
};

#endif // TINYPOWERUP_H
