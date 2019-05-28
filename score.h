#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <stack>
#include <QPainter>
#include <QPixmap>
#include "renderer.h"

class Score {
public:
    Score();

    void increment(unsigned int value = 1);
    void decrement(unsigned int value = 1);
    virtual void render(Renderer &renderer, unsigned int yPosition = 20);

private:
    unsigned int hiscore;
    unsigned int currScore;
    QPixmap digits[10];
};
#endif // SCORE_H
