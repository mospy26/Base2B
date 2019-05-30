#ifndef STICKMANDIESTEST_H
#define STICKMANDIESTEST_H

#include "testrunner.h"
#include "walkingstickman.h"
#include "displayscore.h"

class StickmanDiesTest : public TestRunner
{
public:
    StickmanDiesTest();

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    DisplayScore lifeScore;
    Score score;
    int velocity;
    std::unique_ptr<WalkingStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
};

#endif // STICKMANDIESTEST_H
