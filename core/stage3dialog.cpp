#include "stage3dialog.h"

Stage3Dialog::Stage3Dialog(Game& game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout, unsigned int lives)
    : Stage2Dialog(game, std::move(stickman), std::move(factory), std::move(obstacleLayout)), lives(lives)
{
    background.setVelocity(0);
}

void Stage3Dialog::render(Renderer &renderer) {
    Dialog::render(renderer);
}

void Stage3Dialog::update() {

    moveBackground();
    stickman->update(obstacles);
    if (!stickman->isColliding()) {
        // Reduce distance to next obstacle
        distanceToSpawn -= background.getVelocity();
        background.update();
        //speedUp(counter);
        score.increment();
    }
    spawnObstacles(counter);

    for (auto &c : clouds) {
        c->collisionLogic(*stickman);
    }

    for (auto &o : obstacles) {
        o->collisionLogic(*stickman);
    }

    Stickman& stickmanPtr = *stickman;
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickmanPtr);

//    if(stickman->isColliding()) {
//        walkingStickman->putBack();
//    }

//    if(walkingStickman->getBlinking()) {
//        walkingStickman->blink(counter);
//    }
//    else {
//        walkingStickman->setBlinker(0);
//    }
}

void Stage3Dialog::moveBackground() {
    int stickmanFront = stickman->getCoordinate().getXCoordinate() + stickman->width();
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&(*stickman));

    if(stickmanFront >= 400 && stickmanFront <= 409 && walkingStickman->isMovingRight()) {
        background.setVelocity(8);
        walkingStickman->setVelocity(0);
        for(auto& obs : obstacles) {
            obs->setVelocity(8);
        }
    }
    else if(stickmanFront - stickman->width() <= 0 && stickmanFront - stickman->width() >= -9 && walkingStickman->isMovingLeft()) {
        walkingStickman->getCoordinate().setXCoordinate(0);
        walkingStickman->setVelocity(0);
        for(auto& obs : obstacles) {
            obs->setVelocity(0);
        }

        //do stickman : can go backwards instead of stopping it - extension
    }
    else if(walkingStickman->getVelocity() == 0) {
        background.setVelocity(0);
        for(auto& obs : obstacles) {
            obs->setVelocity(0);
        }
    }
}
