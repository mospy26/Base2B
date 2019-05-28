#ifndef WALKINGSTICKMAN_H
#define WALKINGSTICKMAN_H

#include "jumpingstickman.h"
#include "collision.h"

enum Ability {
    BreakObstacles, HigherJumping, NoEffect
};

class WalkingStickman : public JumpingStickman {
public:
    WalkingStickman(int floor, int jumpImpulse = 15, int maxJumpCount = 2, int gravity = -1);

    void handleInput(QKeyEvent& event) override;
    void update(std::vector<std::unique_ptr<Entity>>& obstacles) override;

    void putBack();
    void setInitialCoordinates(Coordinate& coordinate);
    void setLives(int lives);
    int getLives() const;
    void died();
    void setMovingIndicators(bool right, bool left);
    void setReachedFlag(bool reached);
    bool isReachedFlag() const;
    bool collidedWithPowerup() const;
    void setCollidedWithPowerup(bool collided);
    void provideAbility(enum Ability ability);
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
    bool powerupColliding = false;
    Ability ability = Ability::NoEffect;
};

#endif // WALKINGSTICKMAN_H
