#ifndef POWERUP_H
#define POWERUP_H

#include "coordinate.h"
#include "entity.h"
#include "walkingstickman.h"

class Powerup : public Entity
{
public:
    Powerup(std::string name, Coordinate coordinate, int velocity);
    virtual ~Powerup() override = default;

    virtual void collisionLogic(Stickman& player) override;
    virtual void updateCoordinate() override;
    virtual void upgradeStickman(Stickman& player);
};

#endif // POWERUP_H
