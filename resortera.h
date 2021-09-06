#ifndef RESORTERA_H
#define RESORTERA_H

#include <QGraphicsItem>
#include <QPainter>

class resortera : public QGraphicsItem
{
public:
    resortera();
    QRectF boundingRect() const;
    void paint(QPainter *painter,
       const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // RESORTERA_H
