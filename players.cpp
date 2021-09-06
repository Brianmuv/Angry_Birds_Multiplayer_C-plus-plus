#include "players.h"
#include "mainwindow.h"
#include "ui_players.h"

players::players(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::players)
{
    ui->setupUi(this);
    QPixmap fondo2(":/images/menu.png");
    ui->graphicsView->setBackgroundBrush(fondo2.scaled(651,301,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
}

players::~players()
{
    delete ui;
}

void players::on_unJug_clicked()
{
    MainWindow *mainwindow = new MainWindow(0);
    mainwindow->band = false;
    mainwindow->show();
    close();
}

void players::on_dosJug_clicked()
{
    MainWindow *mainwindow = new MainWindow(0);
    mainwindow->band = true;
    mainwindow->show();
    close();
}

void players::on_salir_clicked()
{
    close();
}
