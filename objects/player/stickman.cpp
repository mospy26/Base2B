#include "stickman.h"

Stickman::~Stickman() {

}

void Stickman::setCoordinate(Coordinate coordinate) {
    this->coordinate = coordinate;
}

void Stickman::setSize(std::string size) {
    this->size = size;
}

// Resize stickman based on size attribute
void Stickman::setSprite(std::string path) {
    QPixmap newSprite(QString::fromStdString(path));
    if (size.compare("tiny") == 0) {
        sprite = newSprite.scaledToHeight(24);
    } else if(size.compare("normal") == 0) {
        sprite = newSprite.scaledToHeight(48);
    } else if(size.compare("large") == 0) {
        sprite = newSprite.scaledToHeight(72);
    } else {
        sprite = newSprite.scaledToHeight(96);
    }
}

// Draw and update stickman position
void Stickman::render(Renderer &renderer, unsigned int time) {
    renderer.draw(coordinate.getQtRenderingXCoordinate(), coordinate.getQtRenderingYCoordinate() - sprite.height(), sprite);
    std::string spritePath = ":sprites/sprite";
    this->setSprite(spritePath.append(std::to_string((time/5)%2)).append(".png"));
}

void Stickman::handleInput(QKeyEvent &event) {

}

void Stickman::update(std::vector<std::unique_ptr<Entity>> &obstacles) {

}

bool Stickman::isColliding() {
    return colliding;
}

int Stickman::width() {
    return sprite.width();
}

int Stickman::height() {
    return sprite.height();
}

Coordinate &Stickman::getCoordinate() {
    return coordinate;
}
