#include "bloque.h"

Bloque::Bloque(float _px, float _py, QGraphicsItem *bloque):QGraphicsPixmapItem(bloque)
{
    px=_px;
    py=_py;
    setPixmap(QPixmap(":/images/bloque.png"));
    setPos(px,py);
}

float Bloque::getX()
{
    return px;
}

float Bloque::getY()
{
    return py;
}
