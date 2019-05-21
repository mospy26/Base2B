#ifndef WALKINGSTICKMAN_H
#define WALKINGSTICKMAN_H

#include "jumpingstickman.h"
#include "collision.h"

class WalkingStickman : public JumpingStickman {
public:
    WalkingStickman(int floor, int jumpImpulse = 15, int maxJumpCount = 2, int gravity = -1);

    void handleInput(QKeyEvent& event) override;
    void update(std::vector<std::unique_ptr<Entity>>& obstacles) override;

    void walk();
    void putBack();
    void blink(int time);
    bool getBlinking() const;
    void setBlinker(int blinker);
    void handleReleasedInput(QKeyEvent& event);

private:
    bool movingRight;
    bool movingLeft;
    Coordinate initialCoordinates;
    bool blinking = false;
    int blinker = 0;
};

#endif // WALKINGSTICKMAN_H
