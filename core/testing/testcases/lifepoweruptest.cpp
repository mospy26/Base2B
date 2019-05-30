#include "lifepoweruptest.h"

LifePowerupTest::LifePowerupTest()
    : TestRunner("LifePowerupTest"), lifeScore("lives")
{
    stickman = std::make_unique<WalkingStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setSize("normal");
    stickman->provideAbility(Ability::NoEffect);
    stickman->setLives(3);

    obstacles.push_back(std::move(std::make_unique<Bird>(Coordinate(400, 50, 450), 2)));
    powerups.push_back(std::make_unique<LifePowerup>(Coordinate(50, 450, 450), 0));
    QPixmap sprite(":/sprites/life.png");
    sprite = sprite.scaledToHeight(40);
    powerups[0]->setSprite(sprite);
    lifeScore.increment(3);
}

void LifePowerupTest::update() {
    stickman->update(obstacles);
    if(powerups[0]) powerups[0]->updateCoordinate();
    obstacles[0]->setVelocity(0);
    auto &o = obstacles[0];
    o->collisionLogic(*stickman);
    if(powerups[0]) powerups[0]->collisionLogic(*stickman);
    if(stickman->collidedWithPowerup()) {
        if(!incremented) {
            lifeScore.increment();
            incremented = true;
        }
        powerups[0] = nullptr;
    }
    if (stickman->getLives() == 4) {
        status = Status::Passed;
    }
}

void LifePowerupTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    obstacles[0]->render(renderer, counter);
    if(powerups[0]) powerups[0]->render(renderer, counter);
    lifeScore.render(renderer, 600, 60);
}
