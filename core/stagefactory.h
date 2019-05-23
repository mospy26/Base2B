#ifndef STAGEFACTORY_H
#define STAGEFACTORY_H

#include <QString>
#include <memory>
#include "entity.h"
#include "gamestage.h"
#include "game.h"
#include "entityfactory.h"
#include "dialog.h"

class StageFactory {
public:
    // This wouldn't be necessary if JSON was used instead of a custom config file format, but rewriting it wasn't an option
    struct Config {
        int stage;
        bool testMode;
        std::string background;
        Coordinate coord;
        int velocity;
        std::string size;
        int lives;
        Game *game;
        std::vector<std::pair<std::unique_ptr<Entity>, int>> *obstacles;
    };

    /**
     * @brief StageFactory
     * @param config The initial configuration the constructed stage will be based on
     */
    StageFactory(Config config);

    std::unique_ptr<GameStage> createStage();

private:
    /**
     * @brief genericDialogInitializer
     * @param dialog A helper method for performing tasks common among all stages to avoid code duplication (e.g. background setup)
     */
    void genericDialogInitializer(Dialog &dialog);

    Config config;
};

#endif // STAGEFACTORY_H
