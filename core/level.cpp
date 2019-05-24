#include "level.h"

Level::Level(std::vector<std::pair<std::unique_ptr<Entity>, int>> layout)
    : obstacleLayout(std::move(layout))
{

}

std::vector<std::pair<std::unique_ptr<Entity>, int>> Level::getObstacleLayout() {
    return std::move(obstacleLayout);
}
