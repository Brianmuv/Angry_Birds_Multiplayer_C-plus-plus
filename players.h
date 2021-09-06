#ifndef PLAYERS_H
#define PLAYERS_H

#include <QWidget>

namespace Ui {
class players;
}

class players : public QWidget
{
    Q_OBJECT

public:
    explicit players(QWidget *parent = 0);
    ~players();

private slots:
    void on_unJug_clicked();

    void on_dosJug_clicked();


    void on_salir_clicked();

private:
    Ui::players *ui;
    bool flag1=false;
};

#endif // PLAYERS_H
