#ifndef POWERUP_H
#define POWERUP_H

#include "coordinate.h"
#include "entity.h"
#include "walkingstickman.h"

class Powerup : public Entity {
public:
    /**
     * @brief Powerup Create a powerup with name, coordinate and velocity as given
     * @param name
     * @param coordinate
     * @param velocity
     */
    Powerup(std::string name, Coordinate coordinate, int velocity);
    virtual ~Powerup() override = default;

    virtual void collisionLogic(Stickman& player) override;

    /**
     * @brief upgradeStickman Defines how the stickman is upgraded if the current powerup is grabbed
     * @param player
     */
    virtual void upgradeStickman(WalkingStickman& player);
    void updateCoordinate() override;
};

#endif // POWERUP_H
