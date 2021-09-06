#include "iniciarregistrar.h"
#include "players.h"
#include "ui_iniciarregistrar.h"

iniciarregistrar::iniciarregistrar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::iniciarregistrar)
{
    ui->setupUi(this);
    //scene2->setSceneRect(0,0,310,300);
    //ui->graphicsView->setScene(scene);
    //ui->graphicsView->resize(scene->width(),scene->height()+50);
    //this->resize(ui->graphicsView->width()+100,ui->graphicsView->height()+50);

    QPixmap fondo2(":/images/acceso.jpg");
    ui->graphicsView->setBackgroundBrush(fondo2.scaled(401,351,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
}

iniciarregistrar::~iniciarregistrar()
{
    delete ui;
}

//---------------------------------------------- REGISTRAR USUARIO ------------------------------------------------------


void iniciarregistrar::on_registrar_clicked()
{
    QString name = ui->name->text();
    QString userR = ui->userR->text();
    QString passR = ui->passR->text();
    QString Confpass = ui->passR_2->text();

    //Condicional para iniciar sesión luego del registro
    if(userR == "" && Confpass == "") {
        QMessageBox::critical(this,"Registro", "El usuario y contraseña no deben estar vacios");
    }else if (ui->name->text()==name && ui->userR->text()==userR && ui->passR->text()==passR && ui->passR_2->text()==Confpass) {
        if(Confpass==passR){
            passwords.push_back(Confpass); //Vector contraseñas
            usuarios.push_back(userR);     //Vector Usuarios

            for(int w=0; w<usuarios.size();w++){qDebug()<<"Ahora: "<<usuarios[w]<<" es un usuario registrado";}
            for(int d=0; d<passwords.size();d++){qDebug()<<"Y su contrseña es: " <<passwords[d];}


            QMessageBox::information(this,"Registro exitoso","Ahora puede iniciar sesión");
            ui->name->clear();
            ui->userR->clear();
            ui->passR->clear();
            ui->passR_2->clear();
        }
         else
            QMessageBox::critical(this,"Error","Las contraseñas no coinciden");

    }

    outfile.open("DatosdeUsuario.txt",ios_base::app);
    outfile<<userR.toUtf8().toStdString()<<'\t'<<Confpass.toUtf8().toStdString()<<'\t';
    outfile.close();



}





//---------------------------------------------- INICIAR SESIÓN --------------------------------------------------------

void iniciarregistrar::on_iniciar_clicked()
{
    QString username = ui->user->text();
    QString password = ui->pass->text();
    QString passw;
    QString usua;


    infile.open("DatosdeUsuario.txt");

    while(infile.good()){
      string linea_texto;
      getline(infile,linea_texto);
      int pos_ini = 0;


      //Extraer el usuario del archivo
      int pos_fin = linea_texto.find_first_of('\t');
      string nombre= linea_texto.substr(pos_ini,pos_fin);
      usua = QString::fromStdString(nombre);    //Conversión de string a QString
      linea_texto.erase(0,pos_fin+1);


      //Extraer la contraseña del archivo
      pos_fin = linea_texto.find_first_of('\t');
      string contra= linea_texto.substr(pos_ini,pos_fin);
      passw = QString::fromStdString(contra);  //Conversión de string a QString
      linea_texto.erase(0,pos_fin+1);
    }

    infile.close();



    //Verificar si el usuario y contraseña están en la variable
    bool verf=false;   //flag
    bool verf2=false;   //flag

    if(username==usua && password==passw);
        verf=true;
        verf2=true;





    //No se pueden dejar user and pass vacios
    if(username == "" && password == "") {
        QMessageBox::critical(this,"Login", "El usuario y contraseña no deben estar vacios");


     // Si los datos están bien se loguea
    }else if (verf==true && verf2==true){
        ui->user->clear();
        ui->pass->clear();
        players *player = new players(0);
        player->show();
        close();

    } else{
        QMessageBox::warning(this,"Login", "Nombre de usuario y contraseña incorrectos");
                    }


}


