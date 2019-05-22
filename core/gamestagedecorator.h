#ifndef GAMESTAGEDECORATOR_H
#define GAMESTAGEDECORATOR_H

#include <memory>
#include "gamestage.h"

class GameStageDecorator : public GameStage {
public:
    GameStageDecorator(std::unique_ptr<GameStage> stage);
    virtual ~GameStageDecorator() = 0;

    virtual void update();
    virtual void render(Renderer& renderer);
    virtual void input(QKeyEvent& event);
    virtual void releasedInput(QKeyEvent& event);

private:
    std::unique_ptr<GameStage> stage;
};

#endif // GAMESTAGEDECORATOR_H
