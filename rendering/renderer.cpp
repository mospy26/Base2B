#include "renderer.h"

Renderer::Renderer(QPainter &painter) : painter(painter) {

}

Renderer::~Renderer() {

}

void Renderer::draw(int x, int y, QPixmap &pm) {
    painter.drawPixmap(x, y, pm);
}

QPainter &Renderer::getPainter() {
    return painter;
}
