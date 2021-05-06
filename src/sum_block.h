#ifndef SUM_BLOCK_H
#define SUM_BLOCK_H

#include <QGraphicsItem>
#include <QPainter>

class sum_block : public QGraphicsItem {
public:
    sum_block(QGraphicsItem *parent = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};

#endif // SUM_BLOCK_H
