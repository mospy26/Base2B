#include "stickmandiestest.h"

StickmanDiesTest::StickmanDiesTest() : TestRunner("StickmanDiesTest"), lifeScore("lives"), score(), velocity(8) {
    stickman = std::make_unique<WalkingStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setSize("normal");
    stickman->provideAbility(Ability::NoEffect);
    stickman->setLives(1);

    lifeScore.increment(stickman->getLives());
    score.increment(500);

    obstacles.push_back(std::move(std::make_unique<Bird>(Coordinate(400, 50, 450), 2)));
}

void StickmanDiesTest::update() {
    stickman->update(obstacles);

    obstacles[0]->collisionLogic(*stickman);
    obstacles[0]->setVelocity(velocity);
    stickman->setVelocity(velocity);

    if(stickman->isColliding()) {
        velocity = 0;
        stickman->setLives(stickman->getLives() - 1);
        lifeScore.decrement();
        stickman->died();
        score.decrement(300); // lose 300 points for dying
    }

    if(stickman->getCoordinate().getYCoordinate() < 0) {
        status = Status::Passed;
    }
}

void StickmanDiesTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    obstacles[0]->render(renderer, counter);
    score.render(renderer, 600, 20);
    lifeScore.render(renderer, 600, 60);
}
