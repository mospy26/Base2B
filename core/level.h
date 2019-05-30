#ifndef LEVEL_H
#define LEVEL_H

#include "entity.h"

class Level {
public:
    /**
     * @brief Level Takes a vector of obstacle layouts and creates a level off it
     * @param layout
     */
    Level(std::vector<std::pair<std::unique_ptr<Entity>, int>> layout);

    std::vector<std::pair<std::unique_ptr<Entity>, int>> getObstacleLayout();

private:
    std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout;
    std::vector<std::unique_ptr<Entity>> powerups;
};

#endif // LEVEL_H
