#include <time.h>
#include <QApplication>
#include "debugrenderer.h"

DebugRenderer::DebugRenderer(QPainter &painter) : Renderer(painter) {

}

void DebugRenderer::draw(int x, int y, QPixmap &pm) {
    // Draw a randomly-coloured box
    srand(pm.cacheKey());
    painter.fillRect(x, y, pm.width(), pm.height(), QColor(rand() % 256, rand() % 256, rand() % 256));

    painter.save();
    painter.setFont(QApplication::font());
    painter.setPen(Qt::red);

    // Calculate space needed for positional text
    QFontMetrics fm(painter.font());
    QString str = QString("x:%1,y:%2").arg(x).arg(y);
    QRect rect(x, y, std::max(fm.width(str), pm.width()), std::max(fm.height(), pm.height()));

    // Draw positional text
    painter.drawText(rect, Qt::AlignCenter, str);
    painter.restore();
}
