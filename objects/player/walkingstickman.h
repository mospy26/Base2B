#ifndef WALKINGSTICKMAN_H
#define WALKINGSTICKMAN_H

#include "jumpingstickman.h"
#include "collision.h"

class WalkingStickman : public JumpingStickman {
public:
    WalkingStickman(int floor, int jumpImpulse = 15, int maxJumpCount = 2, int gravity = -1);

    void handleInput(QKeyEvent& event) override;
    void update(std::vector<std::unique_ptr<Entity>>& obstacles) override;

    void putBack();
    void blink(int time);
    bool getBlinking() const;
    void setBlinker(int blinker);
    int getVelocity() const;
    void setVelocity(int velocity);
    void handleReleasedInput(QKeyEvent& event);
    bool isMovingRight() const;
    bool isMovingLeft() const;

private:
    bool movingRight;
    bool movingLeft;
    Coordinate initialCoordinates;
    int velocity = 0;
    bool blinking = false;
    int blinker = 0;
};

#endif // WALKINGSTICKMAN_H
