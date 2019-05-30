#ifndef LARGEJUMPTEST_H
#define LARGEJUMPTEST_H

#include "testrunner.h"
#include "walkingstickman.h"

class LargeJumpTest : public TestRunner {
public:
    LargeJumpTest();

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    std::unique_ptr<WalkingStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
};

#endif // LARGEJUMPTEST_H
