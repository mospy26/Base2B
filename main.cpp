#include "dialog.h"
#include <QApplication>

#include <iostream>
#include <QTextStream>
#include <QFileInfo>
#include <time.h>
#include <vector>
#include <tuple>
#include "entityfactory.h"
#include "jumpingstickman.h"
#include "colouredentity.h"
#include "flyingentity.h"
#include "stage2dialog.h"
#include "testrunner.h"
#include "testingdialog.h"
#include "collisiontest.h"
#include "jumptest.h"
#include "swaprendererstage.h"
#include "flyingobstacletest.h"
#include "stagefactory.h"
#include "level.h"
#include <iostream>
using namespace std;

inline bool exists(const std::string& name) {
    QFileInfo fileInfo(name.c_str());
    return fileInfo.exists();
}

bool isNumber(string value) {
    for (size_t i = 0; i < value.length(); i++) {
        if(!isdigit(value[i])) {
            return false;
        }
    }
    return true;
}

// A better version of the above method, but I don't want to remove it in case I lose marks
bool isNumber(QString value) {
    bool ok;
    value.toInt(&ok);
    return ok;
}

vector<pair<std::unique_ptr<Entity>, int>> obstacleLayoutReader(QString value) {
    vector<pair<std::unique_ptr<Entity>, int>> obstacles;
    QStringList parts = value.split("|");
    EntityFactory factory;
    for (QString &s : parts) {
        QStringList sl = s.split(",");

        // Make sure each obstacle config has 8 integer parameters
        bool ok = true;
        for (int i = 0; i < sl.length() && ok; i++) {
            ok = isNumber(sl.at(i));
        }
        if (sl.length() != 8 || !ok) {
            cout << "Invalid obstacle values. Terminating.";
            exit(-1);
        }

        // Make a coloured bird obstacle according to the config
        auto e = factory.getEntity("bird");
        e = make_unique<ColouredEntity>(move(e), QColor(sl.at(4).toInt(), sl.at(5).toInt(), sl.at(6).toInt()));
        e->setSize(sl.at(0).toInt(), sl.at(1).toInt());
        e->getCoordinate().setYCoordinate(sl.at(2).toInt());
        int flyRate = sl.at(7).toInt();
        if (flyRate != 0) {
            e = make_unique<FlyingEntity>(move(e), flyRate);
        }

        // Add the pair (obstacle, spacing_to_next_obstacle) to our obstacle layout
        obstacles.push_back(make_pair(move(e), sl.at(3).toInt()));
    }

    return move(obstacles);
}

int main(int argc, char *argv[]) {
    srand(time(nullptr));

    QApplication a(argc, argv);

    Game game;

    // Set up background
    Background background;
    background.setSprite(":ground.png");
    background.setCoordinate(Coordinate(0, 150, 450));

    StageFactory::Config stageConfig;
    vector<pair<unique_ptr<Entity>, int>> obstacles;
    stageConfig.obstacles = &obstacles;
    stageConfig.game = &game;

    vector<unique_ptr<Level>> levels;
    stageConfig.levels = &levels;

    int infiniteMode = -1;
    stageConfig.infiniteMode = false;

    // Read config file and set basic game attributes
    if (!exists("../../../../Base2B/config.txt")) {
        cout << "Config file not found. Terminating" << endl;
        return -1;
    }
    QFile inputFile(QString("../../../../Base2B/config.txt"));
    inputFile.open(QIODevice::ReadOnly);
    QTextStream stream(&inputFile);
    QString line = stream.readLine();
    while (!line.isNull()) {
        QStringList args = line.split(" ");
        if (args.length() != 2) {
            cout << "Invalid config format. Terminating" << endl;
            return -1;
        }
        string setting = line.split(" ").at(0).toStdString();
        QString value = line.split(" ").at(1);
        if (setting == "size:") {
            std::string size = value.toStdString();
            if (size.compare("tiny") != 0 &&
                    size.compare("normal") != 0 &&
                    size.compare("large") != 0 &&
                    size.compare("giant") != 0) {
                cout << "Size must be tiny, normal, large or giant. Terminating" << endl;
                return -1;
            }
            stageConfig.size = size;
        } else if (setting == "x:") {
            if (!isNumber(value.toStdString())) {
                cout << "X coordinate must be set to a postive integer. Terminating";
                return -1;
            }
            unsigned int x = value.toUInt();
            if (x > 800) {
                cout << "X coordinate must be between 0 and 800. Terminating";
                return -1;
            }
            stageConfig.coord = Coordinate(x, 150, 450);
        } else if (setting == "velocity:") {
            if (!isNumber(value.toStdString())) {
                cout << "Velocity must be set to a positive integer. Terminating";
                return -1;
            }
            stageConfig.velocity = value.toInt();
        } else if (setting == "background:") {
            string path = value.toStdString();
            if (exists(path)) {
                stageConfig.background = path;
            } else {
                cout << "File \"" + path + "\" not found. Terminating";
                return -1;
            }
        } else if (setting == "stage:") {
            if (!isNumber(value.toStdString())) {
                cout << "Stage value must be a positive integer. Terminating";
                return -1;
            }
            stageConfig.stage = value.toInt();
            if (stageConfig.stage != 1 && stageConfig.stage != 2 && stageConfig.stage != 3) {
                cout << "Invalid stage value. Terminating";
                return -1;
            }
        } else if (setting == "obstacles:") {
            obstacles = obstacleLayoutReader(value);
        } else if (setting == "testMode:") {
            stageConfig.testMode = value.compare("on") == 0;
        } else if (setting == "lives:") {
            bool ok = isNumber(value);
            if(!ok) {
                cout << "Invalid lives value. Terminating.";
                return -1;
            }
            int lives = value.toInt();
            if(lives <= 0) {
                cout << "Cannot start with 0 or negative lives. Terminating.";
                return -1;
            }
            stageConfig.lives = lives;
        } else if(setting == "moreObstacles:") {
            QStringList layoutList = value.split("->");
            if(layoutList.size() < 1) {
                cout << "Need to have level 2 obstacles and perhaps more. Terminating.";
                return -1;
            }
            vector<pair<std::unique_ptr<Entity>, int>> obs;
            for(int i = 0; i < layoutList.size(); i++) {
                obs = obstacleLayoutReader(layoutList[i]);
                levels.push_back(make_unique<Level>(move(obs)));
                obs.clear();
            }
        } else if(setting == "infiniteMode:") {
            if(value == "yes") {
                stageConfig.infiniteMode = true;
            }
            else if(value == "no") {
                stageConfig.infiniteMode = false;
            }
            else {
                cout << "Infinite mode must be \"yes\" or \"no\". Terminating." << std::endl;
                return -1;
            }
        }
        line = stream.readLine();
    };

    if(stageConfig.stage == 3 && levels.size() < 1) {
        cout << "Need to have at least 2 levels. Terminating.";
        return -1;
    }

    // Construct and set stage
    game.setStage(StageFactory(stageConfig).createStage());
    game.show();

    return a.exec();
}
