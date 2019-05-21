#ifndef ENTITYDECORATOR_H
#define ENTITYDECORATOR_H

#include "entity.h"

class EntityDecorator : public Entity {
public:
    EntityDecorator(std::unique_ptr<Entity> entity);
    virtual ~EntityDecorator() = 0;

    void updateCoordinate();
    void collisionLogic(Stickman &player);

    Coordinate &getCoordinate();
    QPixmap &getSprite();
    int width();
    int height();
    void render(Renderer &renderer, unsigned int time);
    void setSize(int width, int height);
    void setVelocity(int v);
    int getVelocity();
    std::unique_ptr<Entity> clone();

private:
    std::unique_ptr<Entity> entity;
};

#endif // ENTITYDECORATOR_H
