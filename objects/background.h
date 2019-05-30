#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>
#include "coordinate.h"
#include "renderer.h"

class Background {
public:
    Background() = default;

    void setCoordinate(Coordinate coordinate);

    int getVelocity();
    void setVelocity(int velocity);

    void setSprite(std::string path);

    void render(Renderer &renderer, unsigned int time);
    void update();

private:
    Coordinate coordinate;
    int velocity;
    QPixmap sprite;
};

#endif // BACKGROUND_H
