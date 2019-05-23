#include "stage3dialog.h"

Stage3Dialog::Stage3Dialog(Game& game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout, unsigned int lives)
    : Stage2Dialog(game, std::move(stickman), std::move(factory), std::move(obstacleLayout)), lives(lives)
{
    background.setVelocity(0);
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&(*this->stickman));
    walkingStickman->setInitialCoordinates(this->stickman->getCoordinate());
    dieSongs = std::make_unique<QMediaPlayer>(nullptr, QMediaPlayer::LowLatency);
    dieSongs->setMedia(QUrl("qrc:/die.mp3"));
}

void Stage3Dialog::render(Renderer &renderer) {
    Dialog::render(renderer);
}

void Stage3Dialog::update() {

    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&(*stickman));

    moveBackground();

    if(walkingStickman->getLives() == 0) {
        background.setVelocity(0);
        for(auto& o: obstacles) {
            o->setVelocity(0);
        }
        if(dieSongs->state() == QMediaPlayer::StoppedState) {
            exit(0);
        }
    }

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


    if(stickman->isColliding()) {
        if(walkingStickman->getLives() > 0) walkingStickman->setLives(walkingStickman->getLives() - 1);
        if(walkingStickman->getLives() == 0) {
            dieSongs->play();
            walkingStickman->died();
         }
        else {
            walkingStickman->putBack();
            restartLevel();
        }
    }
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

void Stage3Dialog::restartLevel() {
    background.setCoordinate(Coordinate(0,150,450));
    obstacles.clear();
    nextObstacle = 0;
}

void Stage3Dialog::spawnObstacles(unsigned int counter) {
    // Check if it's time to spawn an obstacle
    if (obstacleLayout.size() == 0 || distanceToSpawn > 0) return;
    auto &e = obstacleLayout[nextObstacle];

    // Check for collisions between next obstacle and current obstacles
    bool isOverlapping = false;
    if(nextObstacle < obstacleLayout.size()) {
        for (auto &o : obstacles) {
            if (Collision::overlaps(*e.first, *o)) {
                isOverlapping = true;
                break;
            }
        }
    }

    // Only spawn the obstacle if it isn't colliding with anything
    if (!isOverlapping && nextObstacle < obstacleLayout.size()) {
        auto obs = e.first->clone();
        obs->setVelocity(background.getVelocity());
        addObstacle(std::move(obs));
    }

    // Set next obstacle in sequence
    if(nextObstacle < obstacleLayout.size()) {
        distanceToSpawn = e.second;
        nextObstacle = (nextObstacle + 1);
    }
}
