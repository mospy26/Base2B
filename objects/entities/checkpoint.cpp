#include "checkpoint.h"

Checkpoint::Checkpoint(std::string name, Coordinate coordinate, int velocity)
    : Entity(name, coordinate, velocity)
{

}

void Checkpoint::collisionLogic(Stickman &stickman) {
    WalkingStickman* walking = dynamic_cast<WalkingStickman*>(&stickman);
    if(walking->isColliding()) {
        walking->setReachedFlag(true);
    }
    Entity::collisionLogic(stickman);
}
