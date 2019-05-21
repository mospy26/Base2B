#include <QBitmap>
#include "colouredentity.h"

ColouredEntity::ColouredEntity(std::unique_ptr<Entity> entity, QColor colour) : EntityDecorator(std::move(entity)), colour(colour) {
}

void ColouredEntity::render(Renderer &renderer, unsigned int time) {
    // This isn't efficient, but it'd take too much refactoring of the original code to make it better
    QPixmap &pm = EntityDecorator::getSprite();
    QPixmap temp(pm);
    pm.fill(colour);
    pm.setMask(temp.createMaskFromColor(Qt::transparent));
    EntityDecorator::render(renderer, time);
}

std::unique_ptr<Entity> ColouredEntity::clone() {
    auto e = std::make_unique<ColouredEntity>(EntityDecorator::clone(), colour);
    return std::move(e);
}
