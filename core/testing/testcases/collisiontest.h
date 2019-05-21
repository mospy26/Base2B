#ifndef COLLISIONTEST_H
#define COLLISIONTEST_H

#include "jumpingstickman.h"
#include "testrunner.h"
#include "entity.h"

class CollisionTest : public TestRunner {
public:
    CollisionTest();
    ~CollisionTest() = default;

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    std::unique_ptr<JumpingStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
};

#endif // COLLISIONTEST_H
