#ifndef SWAPRENDERERSTAGE_H
#define SWAPRENDERERSTAGE_H

#include "gamestagedecorator.h"

class SwapRendererStage : public GameStageDecorator {
public:
    SwapRendererStage(std::unique_ptr<GameStage> stage);

    void render(Renderer &renderer);
    void input(QKeyEvent &event);

private:
    /**
     * @brief debug A flag for the debug rendering mode.
     */
    bool debug;
};

#endif // SWAPRENDERERSTAGE_H
