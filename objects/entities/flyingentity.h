#ifndef FLYINGENTITY_H
#define FLYINGENTITY_H

#include <memory>
#include "entitydecorator.h"
#include "stickman.h"

class FlyingEntity : public EntityDecorator {
public:
    /**
     * @brief FlyingEntity A decorator for adding vertical movement to an Entity
     * @param entity The entity to decorate
     * @param flyRate The rate at which the entity will move vertically
     */
    FlyingEntity(std::unique_ptr<Entity> entity, int flyRate);

    void collisionLogic(Stickman &player);
    std::unique_ptr<Entity> clone();

private:
    int flyRate;
};

#endif // FLYINGENTITY_H
