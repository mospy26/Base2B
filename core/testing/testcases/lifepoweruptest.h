#ifndef LIFEPOWERUPTEST_H
#define LIFEPOWERUPTEST_H

#include "testrunner.h"
#include "walkingstickman.h"
#include "lifepowerup.h"
#include "displayscore.h"

class LifePowerupTest : public TestRunner
{
public:
    LifePowerupTest();

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    DisplayScore lifeScore;
    bool incremented = false;
    std::unique_ptr<WalkingStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
    std::vector<std::unique_ptr<LifePowerup>> powerups;
};

#endif // LIFEPOWERUPTEST_H
