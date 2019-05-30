#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdlib.h>

class Coordinate {
public:
    Coordinate() = default;
    Coordinate(unsigned int xCoordinate, unsigned int yCoordinate, unsigned int frameHeight);
    ~Coordinate() = default;

    int getQtRenderingXCoordinate();
    int getQtRenderingYCoordinate();

    int getXCoordinate();
    int getYCoordinate();

    void setXCoordinate(int x);
    void setYCoordinate(int y);

    unsigned int getFrameHeight();

private:
    unsigned int m_xCoordinate;
    unsigned int m_yCoordinate;
    unsigned int m_frameHeight;
};

#endif // COORDINATE_H
