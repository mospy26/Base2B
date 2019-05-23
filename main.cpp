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
#include <iostream>
using namespace std;

inline bool exists(const std::string& name) {
    QFileInfo fileInfo(name.c_str());
    std::cout << name << std::endl;
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

    // Read config file and set basic game attributes
    if (!exists("../../../../Base2B/config.txt")) {
        cout << "Config file not found. Terminating" << endl;
        return 0;
    }
    QFile inputFile(QString("../../../../Base2B/config.txt"));
    inputFile.open(QIODevice::ReadOnly);
    QTextStream stream(&inputFile);
    QString line = stream.readLine();
    while (!line.isNull()) {
        QStringList args = line.split(" ");
        if (args.length() != 2) {
            cout << "Invalid config format. Terminating" << endl;
            return 0;
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
                return 0;
            }
            stageConfig.size = size;
        } else if (setting == "x:") {
            if (!isNumber(value.toStdString())) {
                cout << "X coordinate must be set to a postive integer. Terminating";
                return 0;
            }
            unsigned int x = value.toUInt();
            if (x > 800) {
                cout << "X coordinate must be between 0 and 800. Terminating";
                return 0;
            }
            stageConfig.coord = Coordinate(x, 150, 450);
        } else if (setting == "velocity:") {
            if (!isNumber(value.toStdString())) {
                cout << "Velocity must be set to a positive integer. Terminating";
                return 0;
            }
            stageConfig.velocity = value.toInt();
        } else if (setting == "background:") {
            string path = value.toStdString();
            if (exists(path)) {
                stageConfig.background = path;
            } else {
                cout << "File \"" + path + "\" not found. Terminating";
                return 0;
            }
        } else if (setting == "stage:") {
            if (!isNumber(value.toStdString())) {
                cout << "Stage value must be a positive integer. Terminating";
                return 0;
            }
            stageConfig.stage = value.toInt();
            if (stageConfig.stage != 1 && stageConfig.stage != 2 && stageConfig.stage != 3) {
                cout << "Invalid stage value. Terminating";
                return 0;
            }
        } else if (setting == "obstacles:") {
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
                    return 0;
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
        } else if (setting == "testMode:") {
            stageConfig.testMode = value.compare("on") == 0;
        } else if (setting == "lives:") {
            bool ok = isNumber(value);
            if(!ok) {
                cout << "Invalid lives value. Terminating.";
                return 0;
            }
            int lives = value.toInt();
            if(lives <= 0) {
                cout << "Cannot start with 0 or negative lives. Terminating.";
                return 0;
            }
            stageConfig.lives = lives;
        }
        line = stream.readLine();
    };

    // Construct and set stage
    game.setStage(StageFactory(stageConfig).createStage());
    game.show();

    return a.exec();
}
