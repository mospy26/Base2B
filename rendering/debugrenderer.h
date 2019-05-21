#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H

#include "renderer.h"

class DebugRenderer : public Renderer {
public:
    /**
     * @brief DebugRenderer Renders objects as bounding boxes with debugging information such as its position.
     * @param painter The QPainter object to draw with.
     */
    DebugRenderer(QPainter &painter);

    void draw(int x, int y, QPixmap &pm);
};

#endif // DEBUGRENDERER_H
