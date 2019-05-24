#include "checkpoint.h"

Checkpoint::Checkpoint(std::unique_ptr<Entity> flag)
    : EntityDecorator(std::move(flag))
{

}

void Checkpoint::collisionLogic(Stickman &stickman) {
    if(stickman.isColliding()) {

    }
    EntityDecorator::collisionLogic(stickman);
}
