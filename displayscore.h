#ifndef DISPLAYSCORE_H
#define DISPLAYSCORE_H

#include "score.h"

class DisplayScore : public Score
{
public:
    DisplayScore(std::string name);

    void render(Renderer& renderer, unsigned int xCoordinate, unsigned int yCoordinate) override;

private:
    std::string name;
    QPixmap sprite;
};

#endif // DISPLAYSCORE_H
