#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "entitydecorator.h"
#include "walkingstickman.h"

class Checkpoint : public EntityDecorator
{
public:
    Checkpoint(std::unique_ptr<Entity> flag);

    void collisionLogic(Stickman& stickman) override;
};

#endif // CHECKPOINT_H
