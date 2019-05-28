#include <QBitmap>
#include "entity.h"
#include <QDebug>

Entity::Entity(std::string name, Coordinate coordinate, int velocity):
    name(name),
    coordinate(coordinate),
    velocity(velocity),
    widthOverride(-1),
    heightOverride(-1) {
    updateSprite(0);
}

std::unique_ptr<Entity> Entity::clone() {
    auto e = std::make_unique<Entity>(name, coordinate, velocity);
    e->setSize(widthOverride, heightOverride);
    return e;
}

Coordinate &Entity::getCoordinate() {
    return coordinate;
}

void Entity::setVelocity(int v) {
    velocity = v;
}

int Entity::getVelocity() {
    return velocity;
}

int Entity::width() {
    return widthOverride >= 0 ? widthOverride : sprite.width();
}

int Entity::height() {
    return heightOverride >= 0 ? heightOverride : sprite.height();
}

void Entity::setSize(int width, int height) {
    widthOverride = width;
    heightOverride = height;
}

void Entity::collisionLogic(Stickman &player) {
    if (!player.isColliding()) this->updateCoordinate();
}

void Entity::updateCoordinate() {
    coordinate.setXCoordinate(coordinate.getQtRenderingXCoordinate() - velocity);
}

void Entity::updateSprite(unsigned int time) {
    if (name == "cactus" || name == "cloud" || name == "flag" || name == "giant") {
        return;
    }
    std::string spritePath = ":sprites/" + name + std::to_string((time/10)%2).append(".png");
    QPixmap sprite(QString::fromStdString(spritePath));
    setSprite(sprite);
}

QPixmap &Entity::getSprite() {
    return sprite;
}

void Entity::setSprite(QPixmap &pm) {
    if (widthOverride >= 0 && heightOverride >= 0) {
        this->sprite = pm.scaled(widthOverride, heightOverride);
    } else {
        this->sprite = pm;
    }
}

void Entity::render(Renderer &renderer, unsigned int time) {
    renderer.draw(coordinate.getQtRenderingXCoordinate(), coordinate.getQtRenderingYCoordinate() - sprite.height(), sprite);
    updateSprite(time);
}

Bird::Bird(Coordinate coordinate, int velocity):
    Entity("bird", coordinate, velocity) {}

// Spawn bird at random height in the sky
void Bird::randomiseHeight() {
    this->coordinate.setYCoordinate(150 + 35*(rand() % 4));
}

Cactus::Cactus(Coordinate coordinate, int velocity):
    Entity("cactus", coordinate, velocity) {}

// Choose from 3 random cactuses
void Cactus::randomiseSprite() {
    std::string spritePath = ":sprites/" + name + std::to_string(rand() % 3) + ".png";
    QPixmap sprite(QString::fromStdString(spritePath));
    setSprite(sprite);
}

Cloud::Cloud(Coordinate coordinate, int velocity):
    Entity("cloud", coordinate, velocity) {
    std::string spritePath = ":/sprites" + name + "0.png";
    QPixmap sprite(QString::fromStdString(spritePath));
    this->sprite = sprite;
}

// Clouds can spawn at random height in the sky
void Cloud::randomiseHeight() {
    this->coordinate.setYCoordinate(coordinate.getQtRenderingYCoordinate() + 30*(rand() % 6));
}


