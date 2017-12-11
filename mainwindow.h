#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "lift.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_pb_clearDump_clicked(); //Очистка дампа
    void on_pb_apply_clicked();    //Применить параметры
    void on_pb_lift_clicked();     //Вызвать лифт с этажа
    void on_pb_floor_clicked();    //Нажать кнопку в кабине
    void sl_message(QString);      //Вывод сообщений
    void sl_finish();              //Лифт выполнил команду

signals:
    void sig_moove(int);                //Команда на вызов лифта
    void sig_changeParams(SLiftParams); //Изменение параметров

private:
    Ui::MainWindow *ui;
    TLift*     m_lift;   //Объект Лифт
    QThread*  m_thread;  //Отдельный поток для перемещения лифта
    bool      m_blokFl;  //Блокирующий флаг

};

#endif // MAINWINDOW_H
