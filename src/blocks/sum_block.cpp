#include "sum_block.h"

sum_block::sum_block(QGraphicsItem *parent) : QGraphicsItem(parent) { }

QRectF sum_block::boundingRect() const {
    return QRectF(0,0,130,100);
}

void sum_block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPen saved_pen = painter->pen();
    QPen local_pen;
    local_pen.setWidth(5);
    painter->setPen(local_pen);

    painter->drawRect(33, 3, 97, 97);
    painter->drawLine(0, 33, 33, 33);
    painter->drawLine(0, 66, 33, 66);
    painter->drawLine(97, 50, 130, 50);

    painter->setPen(saved_pen);
}
