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
    void setInitialCoordinates(Coordinate& coordinate);
    void setLives(int lives);
    int getLives() const;
    void died();

    void setMovingIndicators(bool right, bool left);

    bool getBlinking() const;
    void setBlinker(int blinker);

    void setReachedFlag(bool reached);
    bool isReachedFlag() const;

    bool collidedWithPowerup() const;
    void setCollidedWithPowerup(bool collided);

    int getBlinker() const;
    int getVelocity() const;
    void setVelocity(int velocity);
    void handleReleasedInput(QKeyEvent& event);
    bool isMovingRight() const;
    bool isMovingLeft() const;

private:
    bool movingRight;
    bool movingLeft;
    Coordinate initialCoordinates;
    int lives;
    int velocity = 0;
    bool reachedFlag;
    bool collidedPowerup;

    bool blinking = false;
    int blinker = 0;
};

#endif // WALKINGSTICKMAN_H
