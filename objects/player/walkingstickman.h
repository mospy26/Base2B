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

    void update(std::vector<std::unique_ptr<Entity>>& obstacles) override;

    /**
     * @brief putBack Put the stickman back at the beginning of the level
     */
    void putBack();
    /**
     * @brief setInitialCoordinates Set the initial coordinates of the stickman
     * @param coordinate
     */
    void setInitialCoordinates(Coordinate& coordinate);
    /**
     * @brief setLives Setter for lives
     * @param lives
     */
    void setLives(int lives);
    /**
     * @brief getLives Getter for lives
     * @return
     */
    int getLives() const;
    /**
     * @brief died Animation effect when the stickman dies
     */
    void died();
    /**
     * @brief setMovingIndicators Setters for moving right and moving left variables
     * @param right
     * @param left
     */
    void setMovingIndicators(bool right, bool left);
    /**
     * @brief setReachedFlag Setter for isReachedFlag
     * @param reached
     */
    void setReachedFlag(bool reached);
    /**
     * @brief isReachedFlag Getter for isReachedFlag
     * @return
     */
    bool isReachedFlag() const;
    /**
     * @brief collidedWithPowerup returns true if stickman had collided with a powerup
     * @return
     */
    bool collidedWithPowerup() const;
    /**
     * @brief setCollidedWithPowerup Setter for collided with powerup
     * @param collided
     */
    void setCollidedWithPowerup(bool collided);
    /**
     * @brief provideAbility Enhance the stickman with an ability based off the powerup it grabs
     * @param ability
     */
    void provideAbility(enum Ability ability);
    /**
     * @brief getVelocity Getter for stickman velocity
     * @return
     */
    int getVelocity() const;
    /**
     * @brief setVelocity Setter for velocity
     * @param velocity
     */
    void setVelocity(int velocity);

    /**
     * @brief isMovingRight Getter for moving right flag
     * @return
     */
    bool isMovingRight() const;
    /**
     * @brief isMovingLeft Getter for moving left flag
     * @return
     */
    bool isMovingLeft() const;

private:
    Coordinate initialCoordinates;
    int lives;
    int velocity = 0;
    Ability ability = Ability::NoEffect;
    bool movingRight;
    bool movingLeft;
    bool reachedFlag;
    bool collidedPowerup;
    bool powerupColliding = false;
};

#endif // WALKINGSTICKMAN_H
