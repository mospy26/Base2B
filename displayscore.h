#ifndef DISPLAYSCORE_H
#define DISPLAYSCORE_H

#include "score.h"

class DisplayScore : public Score {
public:
    /**
     * @brief DisplayScore Make a score with a sprite representing the score, intialises the sprite
     * @param name
     */
    DisplayScore(std::string name);

    void render(Renderer& renderer, unsigned int xCoordinate, unsigned int yCoordinate, int padding = 20) override;

private:
    std::string name;
    QPixmap sprite;
};

#endif // DISPLAYSCORE_H
