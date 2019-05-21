#ifndef STICKMAN_H
#define STICKMAN_H

#include "gameobject.h"
#include "coordinate.h"
#include "renderer.h"
#include <string>
#include <QPainter>
#include <QKeyEvent>
#include <vector>
#include <memory>

class Entity;
class Stickman : public GameObject {
public:
    Stickman() = default;
    virtual ~Stickman();

    void setCoordinate(Coordinate coordinate);

    void setSize(std::string size);

    void setSprite(std::string path);

    Coordinate &getCoordinate();

    void render(Renderer &renderer, unsigned int time);

    virtual void handleInput(QKeyEvent &event);
    virtual void update(std::vector<std::unique_ptr<Entity>> &obstacles);

    bool isColliding();
    int width();
    int height();

protected:
    bool colliding;
    QPixmap sprite;

private:
    Coordinate coordinate;
    std::string size;
};

#endif // STICKMAN_H
