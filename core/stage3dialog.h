#ifndef STAGE3DIALOG_H
#define STAGE3DIALOG_H

#include "stage2dialog.h"
#include "walkingstickman.h"

class Stage3Dialog : public Stage2Dialog
{
public:
    Stage3Dialog(Game& game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout, unsigned int lives);

    void update() override;
    void render(Renderer& renderer) override;
    void moveBackground();

private:
    QPixmap checkpointSprite;
    std::vector<Coordinate> checkpointLocations;
    unsigned int lives;
};

#endif // STAGE3DIALOG_H
