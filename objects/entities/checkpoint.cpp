#include "checkpoint.h"

Checkpoint::Checkpoint(Coordinate coordinate, int velocity)
    : Entity("flag", coordinate, velocity)
{

}

void Checkpoint::collisionLogic(Stickman &stickman) {
    WalkingStickman* walking = dynamic_cast<WalkingStickman*>(&stickman);
    if(walking->isColliding()) {
        walking->setReachedFlag(true);
    }
    Entity::collisionLogic(stickman);
}
