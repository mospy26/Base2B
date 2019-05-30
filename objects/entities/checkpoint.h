#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "entitydecorator.h"
#include "walkingstickman.h"

class Checkpoint : public Entity
{
public:
    Checkpoint(Coordinate coordinate, int velocity);

    void collisionLogic(Stickman& stickman) override;
};

#endif // CHECKPOINT_H
