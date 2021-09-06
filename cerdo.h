#ifndef CERDO_H
#define CERDO_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Cerdo: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    float px;
    float py;
public:
    Cerdo(float _px, float _py, QGraphicsItem *cerdo = 0);
    float getX();
    float getY();
};

#endif // CERDO_H
