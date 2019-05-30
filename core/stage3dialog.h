#ifndef STAGE3DIALOG_H
#define STAGE3DIALOG_H

#include "stage2dialog.h"
#include "walkingstickman.h"
#include "checkpoint.h"
#include "level.h"
#include "keypresscommand.h"
#include "keyreleasedcommand.h"
#include "time.h"
#include "giantpowerup.h"
#include "lifepowerup.h"
#include "normalpowerup.h"
#include "tinypowerup.h"
#include "largepowerup.h"
#include "displayscore.h"
#include <utility>
#include <QMediaPlayer>

class Stage3Dialog : public Stage2Dialog {
public:
    /**
     * @brief Stage3Dialog
     * @param game
     * @param stickman
     * @param factory
     * @param obstacleLayout
     * @param lives
     * @param levels Levels that contain the obstacle layouts
     * @param infiniteMode Infinite mode flag
     */
    Stage3Dialog(Game& game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout, unsigned int lives, std::vector<std::unique_ptr<Level>> levels, bool infiniteMode);

    /**
     * @brief input Handle the key input events
     * @param event
     */
    void input(QKeyEvent& event) override;

    /**
     * @brief releasedInput Handle the key released events
     * @param event
     */
    void releasedInput(QKeyEvent& event) override;

    void update() override;
    void render(Renderer& renderer) override;

    void spawnObstacles(unsigned int counter) override;

    /**
     * @brief renderPowerups Render powerups on the dialog
     * @param renderer
     */
    void renderPowerups(Renderer& renderer);

    /**
     * @brief moveBackground This is meant to move the background instead of the stickman when the stickman reaches half way of the screen
     */
    void moveBackground();

    /**
     * @brief restartLevel Restarts a level
     */
    void restartLevel();

    /**
     * @brief nextLevel Proceed to the next level
     */
    void nextLevel();

    /**
     * @brief win Win function for when the stickman wins the game
     */
    void win();

    /**
     * @brief spawnPowerups Meant to spawn powerups
     * @param counter
     */
    void spawnPowerups(unsigned int counter);

private:
    unsigned int lives;
    std::unique_ptr<QMediaPlayer> dieSong;
    std::unique_ptr<QMediaPlayer> winSong;
    std::unique_ptr<Command> keyPress;
    std::unique_ptr<Command> keyReleased;
    std::vector<std::unique_ptr<Level>> levels;
    std::vector<Coordinate> checkpointLocations;
    std::vector<std::unique_ptr<Powerup>> powerups;
    DisplayScore lifeScore;
    DisplayScore levelScore;
    DisplayScore maximumLevelsScore;
    bool infiniteMode;
    bool checkpointPlaced = false;
    bool playedWin = false;
};

#endif // STAGE3DIALOG_H
