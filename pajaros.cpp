#include "pajaros.h"

Pajaros::Pajaros(double px_, double py_,bool P_)
{
    setCursor(Qt::OpenHandCursor);
    px=px_;
    py=py_;
    paj=P_;
    M=0.2;
    ay=0.0;
    vx=0.0;
    vy=0.0;
    mov=false;
}

double Pajaros::get_vy()
{
    return vy;
}

double Pajaros::get_vx()
{
    return vx;
}

void Pajaros::set_vy(double vy_)
{
    vy = vy_;
}

void Pajaros::set_vx(double vx_)
{
    vx=vx_;
}

void Pajaros::set_py(double py_)
{
    py=py_;
}

void Pajaros::set_px(double px_)
{
    px=px_;
}

void Pajaros::set_mover(bool M_)
{
    mov=M_;
}

bool Pajaros::get_band2()
{
    return band2;
}

double Pajaros::get_px()
{
    return px;
}

double Pajaros::get_py()
{
    return py;
}

void Pajaros::calc_vel()
{
    double vp;
    vp=(pow(compresion,2)/M)-(2*G*compresion*sin(ang));

    if(vp>0.0)
        V=sqrt(vp);
    else
        V=0.0;
    vy = -V*sin(ang);

    if(!paj)
        vx = V*cos(ang);
    else
        vx = -V*cos(ang);
}

void Pajaros::calc_pos()
{
    vy += ay;
    px += vx;
    py += vy+(ay/2.0);
}

void Pajaros::mover()
{
    //qDebug()<<"px= "<<px << "  py= "<<py<<endl;
    setPos(px,py);
}

void Pajaros::calc_par()
{
    double h;
    if(!paj)
    {
        h = sqrt(pow(40.0-px,2)+pow(490.0-py,2));
        ang = atan2(py-490.0,abs(px-40.0));
    }
    else
    {
        h = sqrt(pow(1160.0-px,2)+pow(490.0-py,2));
        ang = atan2(py-490.0,abs(px-1160.0));
    }

    compresion = h*0.7;
    //qDebug()<<py<<" py "<<px<<" px";
    //qDebug()<<ang<<"angulo";
    calc_vel();
}

QRectF Pajaros::boundingRect() const
{
    return QRectF(-20,-20,40,40);
}

void Pajaros::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->setBrush(Qt::darkRed);
    //painter->drawEllipse(boundingRect());

    QPixmap pixmap;
    if(!paj)
        pixmap.load(":/images/pajaro.png");
    else
        pixmap.load(":/images/pajaro2.png");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());

}

void Pajaros::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::ClosedHandCursor);
}

void Pajaros::mouseMoveEvent(QGraphicsSceneMouseEvent *ev)
{
    QPointF scene = this->mapToParent(ev->pos());
    double x,y;
    x = double(scene.x());
    y = double(scene.y());
    if(!paj && mov)
    {
        if(x>-20.0 && x<40.0)
            px = x;
        if(y>480.0 && y<550.0)
            py = y;
    }
    else if(paj && mov)
    {
        if(x>1160.0 && x<1220.0)
            px = x;
        if(y>480.0 && y<550.0)
            py = y;
    }
}

void Pajaros::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::OpenHandCursor);
    if(mov)
    {
        calc_par();
        ay=9.8;
        band2 = true;
    }
}
