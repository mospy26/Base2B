#ifndef STAGE3DIALOG_H
#define STAGE3DIALOG_H

#include "stage2dialog.h"
#include "walkingstickman.h"
#include "checkpoint.h"
#include "level.h"
#include "keypresscommand.h"
#include "keyreleasedcommand.h"
#include <QMediaPlayer>

class Stage3Dialog : public Stage2Dialog
{
public:
    Stage3Dialog(Game& game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout, unsigned int lives, std::vector<std::unique_ptr<Level>> levels);

    void input(QKeyEvent& event) override;
    void releasedInput(QKeyEvent& event) override;
    void update() override;
    void render(Renderer& renderer) override;
    void spawnObstacles(unsigned int counter) override;
    void moveBackground();
    void restartLevel();
    void nextLevel();
    void win();

private:
    std::vector<Coordinate> checkpointLocations;
    unsigned int lives;
    std::unique_ptr<QMediaPlayer> dieSong;
    std::vector<std::unique_ptr<Level>> levels;
    std::unique_ptr<QMediaPlayer> winSong;
    std::unique_ptr<KeyPressCommand> keyPress;
    std::unique_ptr<KeyReleasedCommand> keyReleased;
    bool checkpointPlaced = false;
    bool playedWin = false;
};

#endif // STAGE3DIALOG_H
