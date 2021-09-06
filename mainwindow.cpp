#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Time=new QTimer(this);
    TimePajaro1=new QTimer(this);
    TimePajaro2=new QTimer(this);
    scene=new QGraphicsScene(this);

    condi=true;
    Ccerdos=1;
    Cpajaros=0;
    Cpajaros2=0;
    puntos1=0;
    puntos2=0;
    nivel=1;

    scene->setSceneRect(0,0,1200,600);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(scene->width(),scene->height()+50);
    this->resize(ui->graphicsView->width()+100,ui->graphicsView->height()+100);

    QPixmap fondo(":/images/Mapa.jpg");
    ui->graphicsView->setBackgroundBrush(fondo.scaled(1200,650,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    connect(Time,SIGNAL(timeout()),this,SLOT(AnimarPajaro()));
    connect(TimePajaro1,SIGNAL(timeout()),this,SLOT(CrearPajaro1()));
    connect(TimePajaro2,SIGNAL(timeout()),this,SLOT(CrearPajaro2()));

    Time->start(33);
}


MainWindow::~MainWindow()
{
    delete ui;
}
//---------------------------------------------- CREAR PAJAROS -------------------------------------------------------------

void MainWindow::CrearPajaro1()
{
    Mypajaro1.append(new Pajaros(40.0,480.0,false));
    Mypajaro1.at(Cpajaros)->setPos(Mypajaro1.at(Cpajaros)->get_px(),-(Mypajaro1.at(Cpajaros)->get_py()));
    scene->addItem(Mypajaro1.at(Cpajaros));
    Cpajaros++;
    TimePajaro1->stop();
}

void MainWindow::CrearPajaro2()
{
    Mypajaro2.append(new Pajaros(1160.0,480.0,true));
    Mypajaro2.at(Cpajaros2)->setPos(Mypajaro2.at(Cpajaros2)->get_px(),-(Mypajaro2.at(Cpajaros2)->get_py()));
    scene->addItem(Mypajaro2.at(Cpajaros2));
    Cpajaros2++;
    TimePajaro2->stop();
}

//-------------------------------------------------- MOVER PAJARO ---------------------------------------------------------

void MainWindow::AnimarPajaro(){
    if(condi)
    {
        if(!band)
            generarMundo(":/Data/Nivel_1.txt");
        else
            generarMundo(":/Data/2Nivel_1.txt");
        condi=false;
    }
    if (cerdos.isEmpty())
    {
        if(nivel<4)
        {
            if(!band)
                QMessageBox::information(this,"Resultados","Siquiente de nivel\nPuntaje: "+QString::number(puntos1));
            else
            {
                if(puntos1>puntos2)
                    QMessageBox::information(this,"Resultados","¡EL JUGADOR 1 ES EL GANADOR!\nPuntaje: "+QString::number(puntos1));
                else if(puntos2>puntos1)
                    QMessageBox::information(this,"Resultados","¡EL JUGADOR 2 ES EL GANADOR!\nPuntaje: "+QString::number(puntos2));
                else
                    QMessageBox::information(this,"Resultados","¡EMPATE!");
            }
            Avanzar();
        }
        else
        {
            QMessageBox::warning(this,"Fin","¡FIN DEL JUEGO!");
            players *Players = new players(0);
            Players->show();
            Time->stop();
            close();
        }
    }
    if(!turno)
    {
        Mypajaro1.at(Cpajaros-1)->set_mover(true);
        if(band)
            Mypajaro2.at(Cpajaros2-1)->set_mover(false);
    }
    else
    {
        Mypajaro1.at(Cpajaros-1)->set_mover(false);
        Mypajaro2.at(Cpajaros2-1)->set_mover(true);
    }
    for(int i=0;i<Cpajaros;i++)
    {
        ChoqueCerdos(Mypajaro1.at(i), false);
        if(Mypajaro1.at(i)->get_vx()==0.0 && Mypajaro1.at(i)->get_vy()==0.0 && Mypajaro1.at(i)->get_band2())
            scene->removeItem(Mypajaro1.at(i));
        double e=-0.6;
        double Ax,Ay;
        Ax=Mypajaro1.at(i)->get_px();
        Ay=Mypajaro1.at(i)->get_py();
        Mypajaro1.at(i)->calc_pos();
        if(Mypajaro1.at(i)->get_py()+20.0>=570.0)
        {
            if(Mypajaro1.at(i)->get_vy()>=0.0)
            {
                Mypajaro1.at(i)->set_vy(Mypajaro1.at(i)->get_vy()*e);
                Mypajaro1.at(i)->set_vx(Mypajaro1.at(i)->get_vx()*0.6);
            }
            Mypajaro1.at(i)->set_py(550.0);
        }
        Mypajaro1.at(i)->mover();
        ChoqueBloques(Ax,Ay,Mypajaro1.at(i));
    }
    if(Mypajaro1.at(Cpajaros-1)->get_band2())
    {
        if(band)
            turno=true;
        if(Cpajaros<10)
            TimePajaro1->start(40);
    }

    if(band)
    {
        for(int i=0;i<Cpajaros2;i++)
        {
            ChoqueCerdos(Mypajaro2.at(i), true);
            if(Mypajaro2.at(i)->get_vx()==0 && Mypajaro2.at(i)->get_vy()==0 && Mypajaro2.at(i)->get_band2())
                scene->removeItem(Mypajaro2.at(i));
            double e=-0.9;
            double Ax,Ay;
            Ax=Mypajaro2.at(i)->get_px();
            Ay=Mypajaro2.at(i)->get_py();
            Mypajaro2.at(i)->calc_pos();
            if(Mypajaro2.at(i)->get_py()+20.0>=570.0)
            {
                if(Mypajaro2.at(i)->get_vy()>=0.0)
                {
                    Mypajaro2.at(i)->set_vy(Mypajaro2.at(i)->get_vy()*e);
                    Mypajaro2.at(i)->set_vx(Mypajaro2.at(i)->get_vx()*0.6);
                }
                Mypajaro2.at(i)->set_py(550.0);
            }
            Mypajaro2.at(i)->mover();
            ChoqueBloques(Ax,Ay,Mypajaro2.at(i));
        }
        if(Mypajaro2.at(Cpajaros2-1)->get_band2())
        {
            turno=false;
            if(Cpajaros2<10)
                TimePajaro2->start(40);
        }
    }

}


//----------------------------------------- VERIFICAR CHOQUES DE LOS BLOQUES -------------------------------------


void MainWindow::ChoqueBloques(double Ax,double Ay,Pajaros *Paj)
{
    double e=-0.6;
    for(int j=0;j < bloques.size(); j++)
    {
        if(Paj->collidesWithItem(bloques.at(j)))
        {
            if(Ax<Paj->get_px() && Ax+20.0<=double(bloques.at(j)->getX()))
            {
                Paj->set_px(double(bloques.at(j)->getX()-20));
                Paj->set_vx(Paj->get_vx()*e);
                Paj->set_vy(-Paj->get_vy()*e);

            }
            else if(Ax>Paj->get_px() && Ax-20.0>=double(bloques.at(j)->getX()+50))
            {
                Paj->set_px(double(bloques.at(j)->getX()+70));
                Paj->set_vx(Paj->get_vx()*e);
                Paj->set_vy(-Paj->get_vy()*e);
            }
            if(Ay<Paj->get_py() && Ay+20.0<=double(bloques.at(j)->getY()))
            {
                Paj->set_py(double(bloques.at(j)->getY()-20));
                Paj->set_vy(Paj->get_vy()*e);
                Paj->set_vx(-Paj->get_vx()*e);
            }
            else if(Ay>Paj->get_py() && Ay-20.0>=double(bloques.at(j)->getY()+50))
            {
                Paj->set_py(double(bloques.at(j)->getY()+70));
                Paj->set_vy(Paj->get_vy()*e);
                Paj->set_vx(-Paj->get_vx()*e);
            }
        }
    }
}

//----------------------------------------- VERIFICAR CHOQUES DE LOS CERDOS--------------------------------------

void MainWindow::ChoqueCerdos(Pajaros *Paj,bool b)
{
    for(int j=0;j < cerdos.size(); j++)
    {
        if(Paj->collidesWithItem(cerdos.at(j)))
        {
            scene->removeItem(cerdos.at(j));
            cerdos.removeAt(j);
            if(!b){
                puntos1++;
            }
            else{
                puntos2++;}
        }

    }
}

//-------------------------------------------------- GENERAR MUNDO --------------------------------------------------------

void MainWindow::generarMundo(QString direccion)
{
    if(!band)
    {
        R1= new resortera();
        R1->setPos(40.0,480.0);
        scene->addItem(R1);
    }
    else
    {
        R2= new resortera();
        R2->setPos(1160.0,480.0);
        scene->addItem(R2);
    }
    CrearPajaro1();
    CrearPajaro2();
    QString info;

    QFile file(direccion);
    if(!file.exists()){
        qDebug() << "NO FILE FOUND";
} else{
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    info=file.readLine();

    QList<QString> dats;
    int n=0;
    while(n>=0){
        n = info.indexOf(" ");
        if(n!=0){
            dats.append(info.left(n));
        }
        info=info.remove(0,n+1);
    }

    n=0;
    //nivel=dats.at(n++).toInt();
    //ui->label_3->setText("Nivel: "+QString::number(nivel));
    while(n<dats.size()){
        if(dats.at(n)=="B"){
            bloques.append(new Bloque(dats.at(++n).toFloat(),v_limit-dats.at(++n).toFloat()-80));
        }
        else if(dats.at(n)=="C"){
            cerdos.append(new Cerdo(dats.at(++n).toFloat(),v_limit-dats.at(++n).toFloat()-80));
        }
        n++;
    }

    for(int i=0;i<bloques.size();i++){
        scene->addItem(bloques.at(i));
    }
    for(int i=0;i<cerdos.size();i++){
        scene->addItem(cerdos.at(i));
        }
    }
}



//-------------------------------------------------- BORRAR MUNDO ---------------------------------------------------------
void MainWindow::borrarMundo()
{
    qDebug() << "Borrando";
    int n = bloques.size();
    for(int i = 0; i < n; i++)
    {
        scene->removeItem(bloques.at(0));
        bloques.removeAt(0);
    }
    n=Mypajaro1.size();
    for(int i = 0; i < n; i++)
    {
        scene->removeItem(Mypajaro1.at(0));
        Mypajaro1.removeAt(0);
    }
    n=Mypajaro2.size();
    for(int i = 0; i < n; i++)
    {
        scene->removeItem(Mypajaro2.at(0));
        Mypajaro2.removeAt(0);
    }

}

//-------------------------------------------------- GUARDAR MUNDO -------------------------------------------------

void MainWindow::guardarMundo()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Angry Birds - Guardar partida.", "", "Text Files (*.txt)");
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(file.open(QFile::WriteOnly))
        {
            file.write(QString::number(nivel).toUtf8()+" ");
            for(int i = 0; i < bloques.size(); i++)
            {
                file.write("B "+QString::number(bloques.at(i)->getX()).toUtf8()+" "+QString::number(bloques.at(i)->getY()).toUtf8()+" ");
            }
            for(int i = 0; i < cerdos.size(); i++)
            {
                file.write("C "+QString::number(cerdos.at(i)->getX()).toUtf8()+" "+QString::number(cerdos.at(i)->getY()).toUtf8()+" ");
            }
        }
    }
}

//-------------------------------------------------- CARGAR MUNDO -------------------------------------------------

void MainWindow::cargarMundo()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Angry Birds - Cargar partida.", "", "All Files (*.*)");
    if(!fileName.isEmpty()){
        borrarMundo();
        generarMundo(fileName);
    }
}

void MainWindow::set_band(bool band_)
{
    band=band_;
}

void MainWindow::Avanzar()
{
    puntos1=0;
    puntos2=0;
    Cpajaros=0;
    Cpajaros2=0;
    nivel++;
    borrarMundo();
    if(!band)
        generarMundo(":/Data/Nivel_"+QString::number(nivel)+".txt");
    else
        generarMundo(":/Data/2Nivel_"+QString::number(nivel)+".txt");

}

//-------------------------------------------------- MENÚ CARGAR Y GUARDAR -----------------------------------------


void MainWindow::on_actionCargar_Partida_triggered()
{
    cargarMundo();
}


void MainWindow::on_actionGuardar_Partida_triggered()
{
        guardarMundo();
}
