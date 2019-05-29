#include "breakobstacletest.h"
#include "flyingentity.h"

BreakObstacleTest::BreakObstacleTest()
    : TestRunner ("BreakObstacleTest")
{
    stickman = std::make_unique<WalkingStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setSize("giant");
    stickman->provideAbility(Ability::BreakObstacles);

    auto bird = std::make_unique<FlyingEntity>(std::make_unique<Bird>(Coordinate(300, 50, 450), 0), 0);
    obstacles.push_back(std::move(bird));
}

void BreakObstacleTest::update() {
    stickman->update(obstacles);
    stickman->setVelocity(8);
    if(obstacles[0]) obstacles[0]->collisionLogic(*stickman);
    if(stickman->isColliding()) {
        obstacles[0] = nullptr;
    }
    if(obstacles[0] == nullptr) status = Status::Passed;
}

void BreakObstacleTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    if(obstacles[0]) obstacles[0]->render(renderer, counter);
}
