#include "collisiontest.h"
#include "coordinate.h"

CollisionTest::CollisionTest() : TestRunner("CollisionTest") {
    stickman = std::make_unique<JumpingStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setSize("normal");

    obstacles.push_back(std::move(std::make_unique<Bird>(Coordinate(400, 50, 450), 2)));
}

void CollisionTest::update() {
    stickman->update(obstacles);
    if (stickman->isColliding()) {
        status = Status::Passed;
    }
    obstacles[0]->collisionLogic(*stickman);
}

void CollisionTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    obstacles[0]->render(renderer, counter);
}
