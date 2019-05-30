#ifndef GIANTPOWERUPTEST_H
#define GIANTPOWERUPTEST_H

#include "testrunner.h"
#include "walkingstickman.h"
#include "giantpowerup.h"
#include "displayscore.h"

class GiantPowerupTest : public TestRunner {
public:
    GiantPowerupTest();

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    Score score;
    bool incremented = false;
    std::unique_ptr<WalkingStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
    std::vector<std::unique_ptr<GiantPowerup>> powerups;

};

#endif // GIANTPOWERUPTEST_H
