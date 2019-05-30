#include "largepoweruptest.h"

LargePowerupTest::LargePowerupTest()
    : TestRunner("LargePowerupTest")
{
    stickman = std::make_unique<WalkingStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setSize("normal");
    stickman->provideAbility(Ability::NoEffect);
    stickman->setLives(3);

    obstacles.push_back(std::move(std::make_unique<Bird>(Coordinate(400, 50, 450), 2)));
    powerups.push_back(std::make_unique<LargePowerup>(Coordinate(50, 450, 450), 0));
    QPixmap sprite(":/sprites/large.png");
    sprite = sprite.scaledToHeight(40);
    powerups[0]->setSprite(sprite);
}

void LargePowerupTest::update() {
    stickman->update(obstacles);
    if(powerups[0]) powerups[0]->updateCoordinate();
    obstacles[0]->setVelocity(0);
    auto &o = obstacles[0];
    o->collisionLogic(*stickman);
    if(powerups[0]) powerups[0]->collisionLogic(*stickman);
    if(stickman->collidedWithPowerup()) {
        stickman->setSize("large");
        if(!incremented) {
            score.increment(10); // 30 points gained for giant
            incremented = true;
        }
        powerups[0] = nullptr;
    }
    if (incremented) {
        status = Status::Passed;
    }
}

void LargePowerupTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    obstacles[0]->render(renderer, counter);
    if(powerups[0]) powerups[0]->render(renderer, counter);
    score.render(renderer, 600, 60);
}
