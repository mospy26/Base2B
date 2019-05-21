#include "stage3dialog.h"

Stage3Dialog::Stage3Dialog(Game& game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout, unsigned int lives)
    : Stage2Dialog(game, std::move(stickman), std::move(factory), std::move(obstacleLayout)), lives(lives)
{
    background.setVelocity(0);
}

void Stage3Dialog::render(Renderer &renderer) {
    Dialog::render(renderer);
//    renderBackground(renderer, counter);
//    renderObstacles(renderer, counter);
//    stickman->render(renderer, counter);
}

void Stage3Dialog::update() {
    stickman->update(obstacles);

    Stickman& stickmanPtr = *stickman;
    WalkingStickman* walkingStickman = dynamic_cast<WalkingStickman*>(&stickmanPtr);

    if(stickman->isColliding()) {
        walkingStickman->putBack();
    }

    if(walkingStickman->getBlinking()) {
        walkingStickman->blink(counter);
    }
    else {
        walkingStickman->setBlinker(0);
    }
}
