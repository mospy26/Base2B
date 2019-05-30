#ifndef NORMALPOWERUPTEST_H
#define NORMALPOWERUPTEST_H

#include "testrunner.h"
#include "walkingstickman.h"
#include "tinypowerup.h"
#include "displayscore.h"

class NormalPowerupTest : public TestRunner {
public:
    NormalPowerupTest();

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    Score score;
    bool incremented = false;
    std::unique_ptr<WalkingStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
    std::vector<std::unique_ptr<TinyPowerup>> powerups;
};

#endif // NORMALPOWERUPTEST_H
