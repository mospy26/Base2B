#include "jumptest.h"
#include "coordinate.h"

JumpTest::JumpTest() : TestRunner("JumpTest") {
    stickman = std::make_unique<JumpingStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setSize("normal");

    obstacles.push_back(std::move(std::make_unique<Bird>(Coordinate(400, 50, 450), 2)));
}

void JumpTest::update() {
    stickman->update(obstacles);
    if (stickman->isColliding()) {
        stickman->jump();
    }

    auto &o = obstacles[0];
    o->collisionLogic(*stickman);
    if (o->getCoordinate().getXCoordinate() < 0) {
        status = Status::Passed;
    }
}

void JumpTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    obstacles[0]->render(renderer, counter);
}
