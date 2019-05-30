#include "flyingentity.h"
#include "collision.h"

FlyingEntity::FlyingEntity(std::unique_ptr<Entity> entity, int flyRate) : EntityDecorator(std::move(entity)), flyRate(flyRate) {
}

std::unique_ptr<Entity> FlyingEntity::clone() {
    auto e = std::make_unique<FlyingEntity>(EntityDecorator::clone(), flyRate);
    return std::move(e);
}

void FlyingEntity::collisionLogic(Stickman &player) {
    // Only fly if not colliding with the player
    if (!player.isColliding()) {
        Coordinate &coord = EntityDecorator::getCoordinate();
        int newY = coord.getYCoordinate() + flyRate;

        // Make sure we don't move through the player
        Collision::CollisonResult res = Collision::moveCast(*this, player, 0, flyRate);
        if (res.overlapped) {
            if (res.down && flyRate < 0) {
                newY = player.getCoordinate().getYCoordinate() + player.height() + 1;
            } else if (res.up) {
                newY = player.getCoordinate().getYCoordinate() - height() - 1;
            }
        }
        coord.setYCoordinate(newY);
    }

    EntityDecorator::collisionLogic(player);
}
