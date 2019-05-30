#include "dialog.h"
#include "ui_dialog.h"
#include "flyingentity.h"
#include "collision.h"

Dialog::Dialog(Game &game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory)
    : game(game),
    stickman(std::move(stickman)),
    factory(std::move(factory)),
    background(),
    obstacles(),
    clouds(),
    score(),
    counter(0),
    night(false),
    moon(),
    obstacleSpawnFrame(50),
    cloudSpawnFrame(20) {
        game.resize(800,450);
        game.setStyleSheet("background-color: #F7F7F7;");
}

Dialog::~Dialog() {
}

void Dialog::setStickman(std::unique_ptr<Stickman> stickman) {
    this->stickman = std::move(stickman);
}

void Dialog::setBackground(Background background) {
    this->background = background;
}

void Dialog::setMoon(Moon moon) {
    this->moon = moon;
}

void Dialog::update() {
    for (auto &c : clouds) {
        c->collisionLogic(*stickman);
    }

    for (auto &o : obstacles) {
        o->collisionLogic(*stickman);
    }

    background.update();
    spawnObstacles(counter);
    speedUp(counter);
    score.increment();
}

void Dialog::render(Renderer &renderer) {
    renderBackground(renderer, counter);
    renderObstacles(renderer, counter);
    renderClouds(renderer, counter);
    stickman->render(renderer, counter);
    score.render(renderer);
    counter++;
}

void Dialog::input(QKeyEvent &event) {
    stickman->handleInput(event);
}

void Dialog::releasedInput(QKeyEvent &event) {

}

// Draws ground and clouds and sets sky colour
void Dialog::renderBackground(Renderer &renderer, unsigned int counter) {
    background.render(renderer, counter);
    if (moon.render(renderer, counter)) {
        if (night) {
            game.setStyleSheet("background-color: #F7F7F7;");
        } else {
            game.setStyleSheet("background-color: #000000;");
        }
        night = !night;
    }
    renderClouds(renderer, counter);
}

// Render clouds and delete when they get off the screen
void Dialog::renderClouds(Renderer &renderer, unsigned int counter) {
    bool deleteCloud = false;
    for (auto &c: clouds) {
        c->render(renderer, counter);
        if (c->getCoordinate().getQtRenderingXCoordinate() + c->width() < 0) {
            deleteCloud = true;
        }
    }
    if (deleteCloud) {
        clouds.erase(clouds.begin());
    }
}

// Render "obstacles" and delete when they get off the screen
void Dialog::renderObstacles(Renderer &renderer, unsigned int counter) {
    bool deleteObstacle = false;
    for (auto &o: obstacles) {
        if(o == nullptr) continue;
        o->render(renderer, counter);
        if (o->getCoordinate().getQtRenderingXCoordinate() + o->width() < 0) {
            deleteObstacle = true;
        }
    }
    if (deleteObstacle) {
        obstacles.erase(obstacles.begin());
    }
}

#include "colouredentity.h"
// Spawn a new "obstacle" at random every so often
void Dialog::spawnObstacles(unsigned int counter) {
    if (counter == obstacleSpawnFrame) {
        if (rand() % 10 > 6) {
            addObstacle(factory->getEntity("bird"));
        } else {
            addObstacle(factory->getEntity("cactus"));
        }
        obstacleSpawnFrame += (300 / background.getVelocity()) + ((rand() % 16 )* 3);
    }

    if (counter == cloudSpawnFrame) {
        clouds.push_back(factory->getEntity("cloud"));
        cloudSpawnFrame += ((450 / background.getVelocity()) + (rand() % 64) * 3);
    }
}

void Dialog::addObstacle(std::unique_ptr<Entity> obstacle) {
    obstacles.push_back(std::move(obstacle));
}

// Incrementally speed up the scrolling speed
void Dialog::speedUp(unsigned int counter) {
    if (counter % 600 == 0) {
        background.setVelocity(background.getVelocity()+1);
        factory->setVelocity(background.getVelocity());
        // Have to speed up current entities too
        for (auto &o: obstacles) {
            o->setVelocity(background.getVelocity());
        }
        for (auto &c: clouds) {
            c->setVelocity(background.getVelocity());
        }
    }
}
