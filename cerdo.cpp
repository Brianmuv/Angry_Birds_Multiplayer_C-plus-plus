#include "cerdo.h"

Cerdo::Cerdo(float _px, float _py, QGraphicsItem *cerdo):QGraphicsPixmapItem(cerdo)
{
    px=_px;
    py=_py;
    setPixmap(QPixmap(":/images/pig.png"));
    setPos(px,py);
}

float Cerdo::getX()
{
    return px;
}

float Cerdo::getY()
{
    return 500-py;
}
