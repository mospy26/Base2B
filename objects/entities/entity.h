#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <cstdlib>
#include <string>
#include <QPixmap>
#include <QPainter>
#include <memory>
#include "stickman.h"
#include "coordinate.h"
#include "gameobject.h"
#include "renderer.h"

class Entity : public GameObject {
public:
    Entity() = default;
    Entity(std::string name, Coordinate coordinate, int velocity);
    virtual ~Entity() = default;

    virtual void collisionLogic(Stickman &player);
    virtual void updateCoordinate();
    virtual void render(Renderer &renderer, unsigned int time);

    virtual Coordinate &getCoordinate();
    virtual QPixmap &getSprite();
    virtual int width();
    virtual int height();
    virtual void setSize(int width, int height);
    virtual int getVelocity();
    virtual void setVelocity(int v);
    void setSprite(QPixmap &pm);
    std::string getName() const;

    virtual std::unique_ptr<Entity> clone();

protected:
    std::string name;
    Coordinate coordinate;
    int velocity;
    QPixmap sprite;
    int widthOverride;
    int heightOverride;

    void updateSprite(unsigned int time);
};

class Bird: public Entity {
public:
    Bird(Coordinate coordinate, int velocity);

    void randomiseHeight();
};

class Cactus: public Entity {
public:
    Cactus(Coordinate coordinate, int velocity);

    void randomiseSprite();
};

class Cloud: public Entity {
public:
    Cloud(Coordinate coordinate, int velocity);

    void randomiseHeight();
};

#endif // OBSTACLE_H
