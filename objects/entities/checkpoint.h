#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "entitydecorator.h"
#include "walkingstickman.h"

class Checkpoint : public Entity {
public:
    /**
     * @brief Checkpoint Create a checkpoint flag with coordinate and velocity as provided
     * @param coordinate
     * @param velocity
     */
    Checkpoint(Coordinate coordinate, int velocity);

    void collisionLogic(Stickman& stickman) override;
};

#endif // CHECKPOINT_H
