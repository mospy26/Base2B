#include "stage3dialog.h"

Stage3Dialog::Stage3Dialog(Game& game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout, unsigned int lives, std::vector<std::unique_ptr<Level>> levels, bool infiniteMode)
    : Stage2Dialog(game, std::move(stickman), std::move(factory), std::move(obstacleLayout)), lives(lives), levels(std::move(levels)), infiniteMode(infiniteMode), lifeScore("lives"), levelScore("level"), maximumLevelsScore("slash")
{
    lifeScore.increment(lives);
    if(!infiniteMode) {
        maximumLevelsScore.increment(this->levels.size() + 1);
    }
    background.setVelocity(0);
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&(*this->stickman));
    keyPress = std::make_unique<KeyPressCommand>(*walkingStickman);
    keyReleased = std::make_unique<KeyReleasedCommand>(*walkingStickman);
    walkingStickman->setInitialCoordinates(this->stickman->getCoordinate());
    dieSong = std::make_unique<QMediaPlayer>(nullptr, QMediaPlayer::LowLatency);
    dieSong->setMedia(QUrl("qrc:/die.mp3"));
    winSong = std::make_unique<QMediaPlayer>(nullptr, QMediaPlayer::LowLatency);
    winSong->setMedia(QUrl("qrc:/win.mp3"));
    winSong->setVolume(1000);
    std::unique_ptr<Level> initialLevel = std::make_unique<Level>(std::move(obstacleLayout));
    this->levels.insert(this->levels.begin(), std::move(initialLevel));
    obstacleLayout = this->levels.front()->getObstacleLayout();
    if(!infiniteMode) {
        levelScore.increment(1);
    } else {
        levelScore.increment(9999);
    }

}

void Stage3Dialog::render(Renderer &renderer) {
    Dialog::render(renderer);
    renderPowerups(renderer);
    lifeScore.render(renderer, 700, 75);
    levelScore.render(renderer, 700, 45);
    if(!infiniteMode) {
        maximumLevelsScore.render(renderer, 730, 45, 2);
    }
}

void Stage3Dialog::update() {

    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&(*stickman));
    walkingStickman->setCollidedWithPowerup(false);

    if(!walkingStickman->isReachedFlag() && levels.size() >= 1) {
        moveBackground();
    }
    spawnPowerups(counter);

    if(nextObstacle == obstacleLayout.size() && !checkpointPlaced && obstacles.size() == 0 /*&& obstacles.back()->getCoordinate().getXCoordinate() < -obstacles.back()->getSprite().width() + 9*/) {
        std::unique_ptr<Entity> entity = std::make_unique<Checkpoint>(Coordinate(800, 150, 450), background.getVelocity());
        QPixmap pix(":/sprites/flag.png");
        pix = pix.scaledToHeight(220);
        entity->setSprite(pix);
        checkpointPlaced = true;
        obstacles.push_back(std::move(entity));
    }

    //stickman dies!
    if(walkingStickman->getLives() == 0) {
        background.setVelocity(0);
        for(auto& o: obstacles) {
            if(o == nullptr) continue;
            o->setVelocity(0);
        }
        if(dieSong->state() == QMediaPlayer::StoppedState) {
            exit(0);
        }
    }

    //update
    stickman->update(obstacles);
    if (!stickman->isColliding()) {
        // Reduce distance to next obstacle
        distanceToSpawn -= background.getVelocity();
        background.update();
    }
    spawnObstacles(counter);

    for (auto &c : clouds) {
        c->collisionLogic(*walkingStickman);
    }

    for (auto& powerup : powerups) {
        powerup->collisionLogic(*walkingStickman);
        if(walkingStickman->collidedWithPowerup()) break;
    }

    //erase the collected powerup
    if(powerups.size() > 0 && (walkingStickman->collidedWithPowerup() || powerups[0]->getCoordinate().getXCoordinate() < 0))  {
        if(walkingStickman->collidedWithPowerup()) { // only get the powerup points and score if stickman collided with it
            //deal with the score before deleting it
            // 50 for a life powerup, 30 for a giant powerup and 10 for other powerups
            if((*powerups.begin())->getName() == "life") {
                score.increment(50);
                lifeScore.increment();
            }
            else if((*powerups.begin())->getName() == "giant") {
                score.increment(30);
            }
            else {
                score.increment(10);
            }
        }
        powerups.erase(powerups.begin());
    }

    for (auto& o : obstacles) {
        if(o == nullptr) {
            continue;
        }
        o->collisionLogic(*walkingStickman);
    }

    //add 100 points for every destroyed obstacle by giant
    obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [&](const std::unique_ptr<Entity>& o) {
        if(o == nullptr) {
            score.increment(150); // 150 points for destroying obstacles
        }
        return o == nullptr;
    }), obstacles.end());

    //collided
    if(stickman->isColliding() && !walkingStickman->isReachedFlag()) {
        if(walkingStickman->getLives() > 0) {
            walkingStickman->setLives(walkingStickman->getLives() - 1);
            score.decrement(300); // lose 300 points when losing a life
        } if(walkingStickman->getLives() == 0) {
            powerups.clear();
            dieSong->play();
            lifeScore.decrement();
            walkingStickman->died();
        } else {
            walkingStickman->putBack();
            lifeScore.decrement();
            restartLevel();
            checkpointPlaced = false;
        }
    } else if(walkingStickman->isReachedFlag()) { //reached checkpoint
        if(levels.size() > 1) {
            nextLevel();
            levelScore.increment(infiniteMode ? 0 : 1);
            score.increment(500); // win 500 points for proceeding to next level
        }
        else if(!infiniteMode && levels.size() <= 1) {
            powerups.clear();
            win();
            if(winSong->state() == QMediaPlayer::StoppedState && playedWin) {
                exit(0);
            }
        }
    }
}

void Stage3Dialog::moveBackground() {
    int stickmanFront = stickman->getCoordinate().getXCoordinate() + stickman->width();
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&(*stickman));

    if(stickmanFront >= 400 && walkingStickman->isMovingRight()) {
        background.setVelocity(8);
        walkingStickman->setVelocity(0);
        for(auto& obs : obstacles) {
            if(obs == nullptr) continue;
            obs->setVelocity(8);
        }
        for(auto& powerup : powerups) {
            powerup->setVelocity(8);
        }
    }
    else if(stickmanFront - stickman->width() <= 0 && stickmanFront - stickman->width() >= -9 && walkingStickman->isMovingLeft()) {
        walkingStickman->getCoordinate().setXCoordinate(0);
        walkingStickman->setVelocity(0);
        for(auto& obs : obstacles) {
            if(obs == nullptr) continue;
            obs->setVelocity(0);
        }
        for(auto& powerup : powerups) {
            powerup->setVelocity(0);
        }

        //do stickman : can go backwards instead of stopping it - extension
    }
    else if(walkingStickman->getVelocity() == 0) {
        background.setVelocity(0);
        for(auto& obs : obstacles) {
            if(obs == nullptr) continue;
            obs->setVelocity(0);
        }
        for(auto& powerup : powerups) {
            powerup->setVelocity(0);
        }
    }
}

void Stage3Dialog::restartLevel() {
    background.setCoordinate(Coordinate(0,150,450));
    obstacles.clear();
    nextObstacle = 0;
    checkpointPlaced = false;
    powerups.clear();
}

void Stage3Dialog::spawnObstacles(unsigned int counter) {
    // Check if it's time to spawn an obstacle
    if (obstacleLayout.size() == 0 || distanceToSpawn > 0) return;
    auto& e = obstacleLayout[nextObstacle];

    // Check for collisions between next obstacle and current obstacles
    bool isOverlapping = false;
    if(nextObstacle < obstacleLayout.size()) {
        for (auto& o : obstacles) {
            if(o == nullptr) continue;
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

void Stage3Dialog::nextLevel() {
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&(*stickman));
    obstacles.clear();
    if(infiniteMode) {
        levels.push_back(std::make_unique<Level>(std::move(obstacleLayout)));
    }
    levels.erase(levels.begin());
    obstacleLayout = levels.front()->getObstacleLayout();
    walkingStickman->setReachedFlag(false);
    checkpointPlaced = false;
    nextObstacle = 0;
    powerups.clear();
}

void Stage3Dialog::win() {
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&(*stickman));
    if(winSong->state() == QMediaPlayer::StoppedState && !playedWin) {
        winSong->play();
        score.increment(2000); // 2000 points if won the game
        playedWin = true;
    }
    background.setVelocity(0);
    for(auto& o : obstacles) {
        o->setVelocity(0);
    }
    for(auto& p : powerups) {
        p->setVelocity(0);
    }
    walkingStickman->setVelocity(0);
    walkingStickman->getCoordinate().setXCoordinate(walkingStickman->getCoordinate().getXCoordinate() + 3);
}

void Stage3Dialog::input(QKeyEvent &event) {
    keyPress->execute(&event);
}

void Stage3Dialog::releasedInput(QKeyEvent &event) {
    keyReleased->execute(&event);
}

void Stage3Dialog::spawnPowerups(unsigned int counter) {
    srand(time(NULL));
    if(counter % 200 == 0) {
        int randomX = rand() % 800 + 400;
        int randomName = rand() % 8;
        std::unique_ptr<Powerup> powerup;
        switch(randomName) {
            case 0:
                powerup = std::make_unique<GiantPowerup>(Coordinate(randomX, 450, 450), background.getVelocity());
                break;
            case 1:
            case 2:
                powerup = std::make_unique<NormalPowerup>(Coordinate(randomX, 450, 450), background.getVelocity());
                break;
            case 3:
            case 4:
                powerup = std::make_unique<TinyPowerup>(Coordinate(randomX, 450, 450), background.getVelocity());
                break;
            case 5:
            case 6:
                powerup = std::make_unique<LifePowerup>(Coordinate(randomX, 450, 450), background.getVelocity());
                break;
            case 7:
            case 8:
                powerup = std::make_unique<LargePowerup>(Coordinate(randomX, 450, 450), background.getVelocity());
                break;
        }
        QPixmap pix(":/sprites/" + QString(powerup->getName().c_str()) + ".png");
        pix = pix.scaledToHeight(50);
        powerup->setSprite(pix);
        powerups.push_back(std::move(powerup));
    }
}

void Stage3Dialog::renderPowerups(Renderer& renderer) {
    for(auto& powerup : powerups) {
        powerup->render(renderer, counter);
        powerup->updateCoordinate();
    }
}
