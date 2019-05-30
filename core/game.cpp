#include <QPainter>
#include <QTimer>
#include "game.h"
#include "debugrenderer.h"

Game::Game(QWidget *parent) : QDialog(parent) {
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(15);
}

void Game::setStage(std::unique_ptr<GameStage> stage) {
    this->stage = std::move(stage);
}

void Game::paintEvent(QPaintEvent* /*event*/) {
    if (stage != nullptr) {
        stage->update();
        QPainter painter(this);
        Renderer renderer(painter);
        stage->render(renderer);
    }
}

void Game::keyPressEvent(QKeyEvent* event) {
    if (stage != nullptr) {
        stage->input(*event);
    }
}


void Game::keyReleaseEvent(QKeyEvent* event) {
    if(stage != nullptr) {
        stage->releasedInput(*event);
    }
}

void Game::nextFrame() {
    update();
}
