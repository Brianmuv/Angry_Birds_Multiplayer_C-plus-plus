#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Headers
#include "resortera.h"
#include "players.h"
#include "pajaros.h"
#include "cerdo.h"
#include "bloque.h"

//Librerías
#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsrectItem>
#include <QTimer>
#include <QMessageBox>
#include <fstream>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void borrarMundo();
    void generarMundo(QString direccion);
    void guardarMundo();
    void cargarMundo();
    void set_band(bool band_);
    void Avanzar();
    bool band,condi,bandl;
    std::fstream file;


public slots:
    void ChoqueBloques(double Ax, double Ay, Pajaros *Paj);
    void ChoqueCerdos(Pajaros *Paj,bool b);
    void AnimarPajaro();
    void CrearPajaro1();
    void CrearPajaro2();

private slots:
    void on_actionCargar_Partida_triggered();
    void on_actionGuardar_Partida_triggered();

private:
    bool turno = false;  //Un lanzamiento por pajaro a la vez
    int Ccerdos;         //Contadores de los cerdos para reiniciar mundo
    int Cpajaros,Cpajaros2; // Contadores de los oajaros para reiniciar mundo
    int puntos1,puntos2;   //
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem* R;
    QTimer *Time;
    QTimer *TimePajaro1;
    QTimer *TimePajaro2;
    QList<Pajaros*> Mypajaro1;
    QList<Pajaros*> Mypajaro2;
    resortera *R1;
    resortera *R2;
    float nivel;
    QList<Bloque*> bloques;
    QList<Cerdo*> cerdos;
    float h_limit=1200;
    float v_limit=600;


};

#endif // MAINWINDOW_H
