#include "stage3dialog.h"

Stage3Dialog::Stage3Dialog(Game& game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout, unsigned int lives, std::vector<std::unique_ptr<Level>> levels)
    : Stage2Dialog(game, std::move(stickman), std::move(factory), std::move(obstacleLayout)), lives(lives), levels(std::move(levels))
{
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
}

void Stage3Dialog::render(Renderer &renderer) {
    Dialog::render(renderer);
    renderPowerups(renderer);
}

void Stage3Dialog::update() {

    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&(*stickman));
    walkingStickman->setCollidedWithPowerup(false);

    moveBackground();
    spawnPowerups(counter);

    if(nextObstacle == obstacleLayout.size() && !checkpointPlaced && obstacles.size() >= 1 /*&& obstacles.back()->getCoordinate().getXCoordinate() < -obstacles.back()->getSprite().width() + 9*/) {
        std::unique_ptr<Entity> entity = std::make_unique<Checkpoint>("flag", Coordinate(1600, 150, 450), background.getVelocity());
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
        score.increment();
    }
    spawnObstacles(counter);

    for (auto &c : clouds) {
        c->collisionLogic(*walkingStickman);
    }

    for (auto& powerup : powerups) {
        powerup->collisionLogic(*walkingStickman);
    }

    //erase the collected powerup
    if(powerups.size() > 0 && (walkingStickman->collidedWithPowerup() || powerups[0]->getCoordinate().getXCoordinate() < 0)) {
        powerups.erase(powerups.begin());
    }

    for (auto& o : obstacles) {
        if(!o) continue;
        o->collisionLogic(*walkingStickman);
    }

    //collided
    if(stickman->isColliding() && !walkingStickman->isReachedFlag()) {
        if(walkingStickman->getLives() > 0) walkingStickman->setLives(walkingStickman->getLives() - 1);
        if(walkingStickman->getLives() == 0) {
            dieSong->play();
            walkingStickman->died();
         }
        else {
            walkingStickman->putBack();
            restartLevel();
            checkpointPlaced = false;
        }
    } else if(walkingStickman->isReachedFlag()) { //reached checkpoint
        if(levels.size() >= 1) {
            nextLevel();
        }
        else {
            win();
            if(winSong->state() == QMediaPlayer::StoppedState && playedWin) exit(0);
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
    auto &e = obstacleLayout[nextObstacle];

    // Check for collisions between next obstacle and current obstacles
    bool isOverlapping = false;
    if(nextObstacle < obstacleLayout.size()) {
        for (auto &o : obstacles) {
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
    obstacleLayout.clear();
    obstacleLayout = levels.front()->getObstacleLayout();
    levels.erase(levels.begin());
    walkingStickman->setReachedFlag(false);
    checkpointPlaced = false;
    nextObstacle = 0;
    powerups.clear();
}

void Stage3Dialog::win() {
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&(*stickman));
    if(winSong->state() == QMediaPlayer::StoppedState && !playedWin) {
        winSong->play();
        playedWin = true;
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
    if(counter%300 == 0) {
        int randomX = rand() % 800 + 800;
        int randomName = rand() % 4;
        std::string name;
        switch(randomName) {
            case 0:
                name = "small";
                break;
            case 1:
                name = "normal";
                break;
            case 2:
                name = "large";
                break;
            case 3:
                name = "giant";
                break;
        }
        QPixmap pix(":/sprites/giant.png");
        pix = pix.scaledToHeight(50);
        std::unique_ptr<Powerup> powerup = std::make_unique<GiantPowerup>("giant", Coordinate(randomX, 450, 450), background.getVelocity());
        powerup->setSprite(pix);
        powerups.push_back(std::move(powerup));
    }
}

void Stage3Dialog::renderPowerups(Renderer& renderer) {
    for(auto& powerup : powerups) {
        powerup->render(renderer, counter);
    }
    for(auto& powerup : powerups) {
        powerup->updateCoordinate();
    }
}
