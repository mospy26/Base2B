#include "checkpoint.h"

Checkpoint::Checkpoint(std::unique_ptr<Entity> flag)
    : EntityDecorator(std::move(flag))
{

}

void Checkpoint::collisionLogic(Stickman &stickman) {
    WalkingStickman* walking = dynamic_cast<WalkingStickman*>(&stickman);
    if(stickman.isColliding()) {
        walking->setReachedFlag(true);
    }
    EntityDecorator::collisionLogic(stickman);
}
