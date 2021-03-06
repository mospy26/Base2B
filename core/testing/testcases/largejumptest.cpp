#include "largejumptest.h"

LargeJumpTest::LargeJumpTest() : TestRunner("LargeJumpTest") {
    stickman = std::make_unique<WalkingStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setSize("normal");
    stickman->provideAbility(Ability::HigherJumping);
    stickman->setLives(3);

    obstacles.push_back(std::move(std::make_unique<Bird>(Coordinate(400, 50, 450), 0)));
}


void LargeJumpTest::update() {
    stickman->update(obstacles);
    stickman->setVelocity(8);
    if (stickman->isColliding()) {
        stickman->jump();
    }
    auto &o = obstacles[0];
    o->collisionLogic(*stickman);
    if (stickman->getCoordinate().getXCoordinate() > 800) {
        status = Status::Passed;
    }
}

void LargeJumpTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    obstacles[0]->render(renderer, counter);
}
