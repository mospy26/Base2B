#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QKeyEvent>
#include <memory>
#include "gamestage.h"

class Game : public QDialog {
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game() = default;

    void setStage(std::unique_ptr<GameStage> stage);

protected:
    void keyPressEvent(QKeyEvent* event);
    void paintEvent(QPaintEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    std::unique_ptr<GameStage> stage;

public slots:
    void nextFrame();
};

#endif // GAME_H
