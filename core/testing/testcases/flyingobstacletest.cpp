#include "flyingobstacletest.h"
#include "flyingentity.h"

FlyingObstacleTest::FlyingObstacleTest() : TestRunner("FlyingObstacleTest") {
    stickman = std::make_unique<JumpingStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setSize("normal");

    auto bird = std::make_unique<FlyingEntity>(std::make_unique<Bird>(Coordinate(400, 50, 450), 2), 2);
    obstacles.push_back(std::move(bird));
}

void FlyingObstacleTest::update() {
    stickman->update(obstacles);
    if (obstacles[0]->getCoordinate().getXCoordinate() < 0) {
        status = Status::Passed;
    }
    obstacles[0]->collisionLogic(*stickman);
}

void FlyingObstacleTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    obstacles[0]->render(renderer, counter);
}
