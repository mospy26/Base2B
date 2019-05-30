#ifndef COLOUREDENTITY_H
#define COLOUREDENTITY_H

#include "entitydecorator.h"

class ColouredEntity : public EntityDecorator {
public:
    /**
     * @brief ColouredEntity An decorator for colouring an Entity's sprite
     * @param entity The entity to decorate
     * @param colour The new colour of the entity's sprite
     */
    ColouredEntity(std::unique_ptr<Entity> entity, QColor colour);
    void render(Renderer &renderer, unsigned int time);
    std::unique_ptr<Entity> clone();

private:
    QColor colour;
};

#endif // COLOUREDENTITY_H
