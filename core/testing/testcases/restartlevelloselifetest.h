#ifndef RESTARTLEVELLOSELIFETEST_H
#define RESTARTLEVELLOSELIFETEST_H

#include "testrunner.h"
#include "walkingstickman.h"
#include "displayscore.h"

class RestartLevelLoseLifeTest : public TestRunner {
public:
    RestartLevelLoseLifeTest();

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    DisplayScore lifeScore;
    Score score;
    int velocity;
    Coordinate initialCoordinate;
    std::unique_ptr<WalkingStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
};

#endif // RESTARTLEVELLOSELIFETEST_H
