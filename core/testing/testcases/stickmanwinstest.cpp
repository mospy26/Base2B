#include "stickmanwinstest.h"
#include "checkpoint.h"

StickmanWinsTest::StickmanWinsTest() : TestRunner("StickmanWinsTest"), score() {
    stickman = std::make_unique<WalkingStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setSize("normal");
    stickman->provideAbility(Ability::NoEffect);
    stickman->setLives(1);

    score.increment(500);

    QPixmap pix(":/sprites/flag.png");
    pix = pix.scaledToHeight(220);
    obstacles.push_back(std::move(std::make_unique<Checkpoint>(Coordinate(400, 50, 450), 2)));
    obstacles[0]->setSprite(pix);
}

void StickmanWinsTest::update() {
    stickman->update(obstacles);

    obstacles[0]->collisionLogic(*stickman);
    obstacles[0]->setVelocity(0);
    stickman->setVelocity(velocity);

    if(stickman->isColliding() && stickman->isReachedFlag()) {
        if(velocity != 3) {
            score.increment(2000); // gain 2000 points for winning
        }
        velocity = 3;
    }

    if(stickman->getCoordinate().getXCoordinate() > 650) {
        status = Status::Passed;
    }
}

void StickmanWinsTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    obstacles[0]->render(renderer, counter);
    score.render(renderer, 580, 20);
}
