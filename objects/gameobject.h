#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "coordinate.h"

class GameObject {
public:
    GameObject();
    virtual ~GameObject() = 0;

    virtual Coordinate &getCoordinate() = 0;
    virtual int width() = 0;
    virtual int height() = 0;
};

#endif // GAMEOBJECT_H
