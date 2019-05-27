#include "stage3dialog.h"

Stage3Dialog::Stage3Dialog(Game& game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout, unsigned int lives, std::vector<std::unique_ptr<Level>> levels, bool infiniteMode)
    : Stage2Dialog(game, std::move(stickman), std::move(factory), std::move(obstacleLayout)), lives(lives), levels(std::move(levels)), infiniteMode(infiniteMode)
{
    background.setVelocity(0);
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&(*this->stickman));
    walkingStickman->setInitialCoordinates(this->stickman->getCoordinate());
    dieSong = std::make_unique<QMediaPlayer>(nullptr, QMediaPlayer::LowLatency);
    dieSong->setMedia(QUrl("qrc:/die.mp3"));
    winSong = std::make_unique<QMediaPlayer>(nullptr, QMediaPlayer::LowLatency);
    winSong->setMedia(QUrl("qrc:/win.mp3"));
    winSong->setVolume(1000);
    if(infiniteMode) {
        std::unique_ptr<Level> initialLevel = std::make_unique<Level>(std::move(obstacleLayout));
        levels.insert(levels.begin(), std::move(initialLevel));
        obstacleLayout = levels.front()->getObstacleLayout();
    }
}

void Stage3Dialog::render(Renderer &renderer) {
    Dialog::render(renderer);
}

void Stage3Dialog::update() {

    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&(*stickman));

    moveBackground();

    if(nextObstacle == obstacleLayout.size() && !checkpointPlaced && obstacles.size() >= 1 && obstacles.back()->getCoordinate().getXCoordinate() < -obstacles.back()->getSprite().width() + 9) {
        Entity obstacle_back = *obstacles.back();
        std::unique_ptr<Entity> entity = std::make_unique<Entity>("flag", Coordinate(800, 150, 450), background.getVelocity());
        QPixmap pix(":/sprites/flag.png");
        pix = pix.scaledToHeight(220);
        entity->setSprite(pix);
        std::unique_ptr<Entity> checkpointSprite = std::make_unique<Checkpoint>(std::move(entity));
        checkpointPlaced = true;
        obstacles.push_back(std::move(checkpointSprite));
    }

    //stickman dies!
    if(walkingStickman->getLives() == 0) {
        background.setVelocity(0);
        for(auto& o: obstacles) {
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

    for (auto &o : obstacles) {
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
        if(levelPointer <= levels.size() - 1) {
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
    checkpointPlaced = false;
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

void Stage3Dialog::nextLevel() {
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&(*stickman));
    obstacles.clear();
    if(infiniteMode && levelPointer == levels.size()) {
        levelPointer = 0;
    }
    else {
        levelPointer++;
    }
    obstacleLayout = levels[levelPointer]->getObstacleLayout();
    walkingStickman->setReachedFlag(false);
    checkpointPlaced = false;
    nextObstacle = 0;
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
