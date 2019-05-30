#ifndef LARGEPOWERUPTEST_H
#define LARGEPOWERUPTEST_H

#include "testrunner.h"
#include "walkingstickman.h"
#include "largepowerup.h"
#include "displayscore.h"

class LargePowerupTest : public TestRunner {
public:
    LargePowerupTest();

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    Score score;
    bool incremented = false;
    std::unique_ptr<WalkingStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
    std::vector<std::unique_ptr<LargePowerup>> powerups;
};

#endif // LARGEPOWERUPTEST_H
