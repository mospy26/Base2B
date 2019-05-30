#ifndef RENDERER_H
#define RENDERER_H

#include <QPainter>

class Renderer {
public:
    /**
     * @brief Renderer Renders objects by redirecting calls to the draw method to the stored QPainter
     * @param painter The QPainter object to draw with.
     */
    Renderer(QPainter &painter);
    virtual ~Renderer();

    virtual void draw(int x, int y, QPixmap &pm);
    QPainter &getPainter();

protected:
    QPainter &painter;
};

#endif // RENDERER_H
