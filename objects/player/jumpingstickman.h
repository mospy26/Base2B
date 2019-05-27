#ifndef JUMPINGSTICKMAN_H
#define JUMPINGSTICKMAN_H

#include <memory>
#include "entity.h"
#include "stickman.h"

class JumpingStickman : public Stickman {
public:
    /**
     * @brief JumpingStickman An extension of the Stickman class which adds jumping and collision detection
     * @param floor The y position which is considered the floor (i.e. will stop falling at)
     * @param jumpImpulse The vertical velocity applied when jumping
     * @param maxJumpCount The maximum amount of jumps that can be peformed mid-air (including the initial jump)
     * @param gravity The falling rate
     */
    JumpingStickman(int floor, int jumpImpulse = 15, int maxJumpCount = 2, int gravity = -1);
    ~JumpingStickman();

    void jump();
    bool canJump();

    virtual void handleInput(QKeyEvent &event) override;
    virtual void update(std::vector<std::unique_ptr<Entity>> &obstacles) override;

protected:
    int floor;
    int jumpImpulse;
    int jumpVelocity;
    int gravity;
    bool grounded;
    int jumpCount;
    int maxJumpCount;
};

#endif // JUMPINGSTICKMAN_H
