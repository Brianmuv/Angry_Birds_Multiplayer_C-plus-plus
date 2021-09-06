#include "resortera.h"

resortera::resortera()
{

}
QRectF resortera::boundingRect() const
{
    return QRectF(-20,-20,50,90);
}

void resortera::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/images/resortera.png");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}
