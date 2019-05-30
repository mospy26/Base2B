#ifndef MOON_H
#define MOON_H

#define PI 3.14159265

#include <string>
#include <QPixmap>
#include <QPainter>
#include "coordinate.h"
#include "renderer.h"

class Moon {
public:
    Moon() = default;
    Moon(Coordinate origin, double angle, int radius, int moonPhase = 2);

    bool render(Renderer &renderer, unsigned int time);

private:
    Coordinate origin;
    double angle;
    int radius;
    QPixmap sprite;
    int moonPhase;

    void updatePosition();
    void updateSprite();

    bool compareDouble(double a, double b, double epsilon = 0.1);
};

#endif // MOON_H
