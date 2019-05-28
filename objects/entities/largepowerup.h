#ifndef LARGEPOWERUP_H
#define LARGEPOWERUP_H

#include "powerup.h"

class LargePowerup : public Powerup
{
public:
    LargePowerup(Coordinate coordinate, int velocity);

    void collisionLogic(Stickman& stickman) override;
    void upgradeStickman(Stickman& stickman) override;
};

#endif // LARGEPOWERUP_H
