#include "moon.h"
#include <cmath>

using namespace std;

Moon::Moon(Coordinate origin, double angle, int radius, int moonPhase):
    origin(origin), angle(angle), radius(radius), moonPhase(moonPhase) {
    string spritePath = ":sprites/moon";
    spritePath = spritePath + to_string(moonPhase) + ".png";
    QPixmap sprite(QString::fromStdString(spritePath));
    this->sprite = sprite;
}

// Draw and update moon position. Returns whether night cycle has just started/ended
bool Moon::render(Renderer &renderer, unsigned int /*time*/) {
    int x = origin.getQtRenderingXCoordinate() + cos(angle * PI / 180)*radius;
    int y = origin.getQtRenderingYCoordinate() - sin(angle * PI / 180)*radius;
    renderer.draw(x, y - sprite.height(), sprite);
    updatePosition();

    // Let us know whether it is nighttime
    return (compareDouble(angle, 20.0) || compareDouble(angle, 160.0));
}

// Moon position travels as an arc
void Moon::updatePosition() {
    angle = fmod(angle + 0.2, 360.0);
    // Precision checking for double
    if (angle < 0.1 || angle > 359.9) {
        moonPhase = (moonPhase + 1) % 7;
        updateSprite();
    }
}

// Change moon sprite based on the phase of the moon
void Moon::updateSprite() {
    string spritePath = ":sprites/moon";
    spritePath = spritePath + to_string(moonPhase) + ".png";
    QPixmap sprite(QString::fromStdString(spritePath));
    this->sprite = sprite;
}

bool Moon::compareDouble(double a, double b, double epsilon) {
    return std::abs(a - b) < epsilon;
}
