#include "walkunderneathtest.h"

WalkUnderneathTest::WalkUnderneathTest()
    : TestRunner("WalkUnderneathTest")
{
    stickman = std::make_unique<WalkingStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setSize("tiny");
    stickman->provideAbility(Ability::NoEffect);

    obstacles.push_back(std::move(std::make_unique<Bird>(Coordinate(400, 70, 450), 2)));
}

void WalkUnderneathTest::update() {
    stickman->update(obstacles);
    stickman->setVelocity(8);
    obstacles[0]->setVelocity(0);
    auto &o = obstacles[0];
    o->collisionLogic(*stickman);
    if (stickman->getCoordinate().getXCoordinate() > 800) {
        status = Status::Passed;
    }
}

void WalkUnderneathTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    obstacles[0]->render(renderer, counter);
}
