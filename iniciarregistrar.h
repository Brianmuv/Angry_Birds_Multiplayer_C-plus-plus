#ifndef INICIARREGISTRAR_H
#define INICIARREGISTRAR_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsView>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <String>
#include <QVector>
#include <QFile>
#include <fstream>
#include <QWidget>



using namespace std;



namespace Ui {
class iniciarregistrar;
}

class iniciarregistrar : public QWidget
{
    Q_OBJECT

public:
    explicit iniciarregistrar(QWidget *parent = 0);
    ~iniciarregistrar();

    QVector<QString> usuarios;
    QVector<QString> passwords;
    ifstream infile;
    ofstream outfile;

private slots:
    void on_iniciar_clicked();

    void on_registrar_clicked();

private:
    Ui::iniciarregistrar *ui;
    QGraphicsScene* scene2;

};
#endif // INICIARREGISTRAR_H
