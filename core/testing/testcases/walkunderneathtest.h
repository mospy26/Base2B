#ifndef WALKUNDERNEATHTEST_H
#define WALKUNDERNEATHTEST_H

#include "testrunner.h"
#include "walkingstickman.h"

class WalkUnderneathTest : public TestRunner
{
public:
    WalkUnderneathTest();

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    std::unique_ptr<WalkingStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
};

#endif // WALKUNDERNEATHTEST_H
