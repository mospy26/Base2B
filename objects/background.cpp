#include "background.h"
#include <QDebug>

void Background::setCoordinate(Coordinate coordinate) {
    this->coordinate = coordinate;
}

int Background::getVelocity() {
    return velocity;
}

void Background::setVelocity(int velocity) {
    this->velocity = velocity;
}

void Background::setSprite(std::string path) {
    QPixmap newSprite(QString::fromStdString(path));
    sprite = newSprite;
}

// Draws background at current coordinate with copy appended to end of first
// Then updates background location
void Background::render(Renderer &renderer, unsigned int /*time*/) {
    int x = coordinate.getQtRenderingXCoordinate();
    renderer.draw(x % 1200, coordinate.getQtRenderingYCoordinate() - sprite.height(), sprite);
    renderer.draw(x % 1200 + 1200, coordinate.getQtRenderingYCoordinate() - sprite.height(), sprite);
}

void Background::update() {
    coordinate.setXCoordinate(coordinate.getQtRenderingXCoordinate() - velocity);
}
