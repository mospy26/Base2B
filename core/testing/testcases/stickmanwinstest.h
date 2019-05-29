#ifndef STICKMANWINSTEST_H
#define STICKMANWINSTEST_H

#include "testrunner.h"
#include "walkingstickman.h"
#include "displayscore.h"

class StickmanWinsTest : public TestRunner
{
public:
    StickmanWinsTest();

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    Score score;
    int velocity = 8;
    std::unique_ptr<WalkingStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
};

#endif // STICKMANWINSTEST_H
