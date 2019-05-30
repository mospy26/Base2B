#ifndef BREAKOBSTACLETEST_H
#define BREAKOBSTACLETEST_H

#include "testrunner.h"
#include "walkingstickman.h"


class BreakObstacleTest : public TestRunner {
public:
    BreakObstacleTest();

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    std::unique_ptr<WalkingStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
};

#endif // BREAKOBSTACLETEST_H
