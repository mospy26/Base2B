#ifndef COLLISION_H
#define COLLISION_H

#include <QDebug>
#include "gameobject.h"


class Collision {
public:
    /**
     * @brief CollisionResult Stores flags indicating whether a collision occured at position relative to the collider
     */
    struct CollisonResult {
        bool overlapped, left, right, up, down;
    };

    /**
     * @brief overlaps Tests intersection between two GameObjects
     * @param a The first GameObject
     * @param b The second GameObject
     * @return Returns true if there's an intersection between both GameObjects
     */
    static bool overlaps(GameObject &a, GameObject &b) {
        Coordinate &ac = a.getCoordinate();
        Coordinate &bc = b.getCoordinate();
        bool xCollision = bc.getXCoordinate() <= ac.getXCoordinate() + a.width() && bc.getXCoordinate() + b.width() >= ac.getXCoordinate();
        bool yCollision = ac.getYCoordinate() <= bc.getYCoordinate() + b.height() && ac.getYCoordinate() + a.height() >= bc.getYCoordinate();
        return xCollision && yCollision;
    }

    /**
     * @brief moveCast Tests if a GameObject would intersect with another if it moved by a specified amount
     * @param a The GameObject to move
     * @param b The GameObject to check for a collision against
     * @param xMove The amount to move GameObject 'a' horizontally
     * @param yMove The amount to move GameObject 'a' vertically
     * @return Collision points betwen a and b if a were to move by the specified amounts
     */
    static CollisonResult moveCast(GameObject &a, GameObject &b, int xMove, int yMove) {
        CollisonResult res = { false, false, false, false, false };

        Coordinate &ac = a.getCoordinate();
        ac.setXCoordinate(ac.getXCoordinate() + xMove);
        ac.setYCoordinate(ac.getYCoordinate() + yMove);
        bool isOverlapping = overlaps(a, b);
        ac.setXCoordinate(ac.getXCoordinate() - xMove);
        ac.setYCoordinate(ac.getYCoordinate() - yMove);

        if (isOverlapping) {
            res.overlapped = true;
            Coordinate &bc = b.getCoordinate();

            if (ac.getYCoordinate() >= bc.getYCoordinate() + b.height()) {
                res.down = true;
            } else if (ac.getYCoordinate() + a.height() <= bc.getYCoordinate()) {
                res.up = true;
            }

            if (ac.getXCoordinate() <= bc.getXCoordinate()) {
                res.right = true;
            } else {
                res.left = true;
            }
        }

        return res;
    }

private:
    Collision();
};

#endif // COLLISION_H
