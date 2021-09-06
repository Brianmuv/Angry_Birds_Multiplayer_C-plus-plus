#ifndef PAJAROS_H
#define PAJAROS_H
#define G 10
#define P 3.16

#include <QGraphicsItem>
#include <QPainter>
#include <math.h>
#include <QKeyEvent>
#include <QDebug>
#include <QtWidgets>

class Pajaros : public QGraphicsItem
{
public:
    Pajaros(double px_, double py_, bool P_);
    void set_vy(double vy_);
    void set_vx(double vx_);
    void set_py(double py_);
    void set_px(double px_);
    void set_mover(bool M_);
    bool get_band2();
    double get_vy();
    double get_vx();
    double get_px();
    double get_py();
    void calc_vel();
    void calc_pos();
    void mover();
    void calc_par();
    QRectF boundingRect() const;
    void paint(QPainter *painter,
       const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *ev) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev) Q_DECL_OVERRIDE;

private:
    double ay,vx,vy;
    double ang,compresion;
    double V,M;
    double px,py;
    bool band2=false;
    bool paj,mov;

};

#endif // PAJAROS_H
