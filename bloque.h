#ifndef BLOQUE_H
#define BLOQUE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Bloque: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    float px;
    float py;
public:
    Bloque(float px, float py, QGraphicsItem *bloque = 0);
    float getX();
    float getY();
};

#endif // BLOQUE_H
