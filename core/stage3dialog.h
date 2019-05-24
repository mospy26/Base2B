#ifndef STAGE3DIALOG_H
#define STAGE3DIALOG_H

#include "stage2dialog.h"
#include "walkingstickman.h"
#include "checkpoint.h"
#include <QMediaPlayer>

class Stage3Dialog : public Stage2Dialog
{
public:
    Stage3Dialog(Game& game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout, unsigned int lives);

    void update() override;
    void render(Renderer& renderer) override;
    void spawnObstacles(unsigned int counter) override;
    void moveBackground();
    void restartLevel();

private:
    std::unique_ptr<Entity> checkpointSprite;
    std::vector<Coordinate> checkpointLocations;
    unsigned int lives;
    std::unique_ptr<QMediaPlayer> dieSongs;
    bool checkpointPlaced;

};

#endif // STAGE3DIALOG_H
