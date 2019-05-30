#include "coordinate.h"

Coordinate::Coordinate(
        unsigned int x,
        unsigned int y,
        unsigned int frameHeight)
    : m_xCoordinate(x), m_yCoordinate(y), m_frameHeight(frameHeight) {
}

int Coordinate::getQtRenderingXCoordinate() {
    return m_xCoordinate;
}

int Coordinate::getQtRenderingYCoordinate() {
    return m_frameHeight - m_yCoordinate;
}

int Coordinate::getXCoordinate() {
    return m_xCoordinate;
}

int Coordinate::getYCoordinate() {
    return m_yCoordinate;
}

void Coordinate::setXCoordinate(int x) {
    m_xCoordinate = x;
}

void Coordinate::setYCoordinate(int y) {
    m_yCoordinate = y;
}

unsigned int Coordinate::getFrameHeight() {
    return m_frameHeight;
}
