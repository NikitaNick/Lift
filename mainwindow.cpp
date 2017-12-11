#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType <SLiftParams> ("SLiftParams");
    m_blokFl = false;
    m_lift = new TLift();
    m_thread = new QThread();
    m_lift->moveToThread(m_thread);
    connect(this, SIGNAL(sig_moove(int)), m_lift, SLOT(sl_moove(int)));
    connect(this, SIGNAL(sig_changeParams(SLiftParams)), m_lift, SLOT(sl_setParams(SLiftParams)));
    connect(m_lift, SIGNAL(sig_message(QString)),this, SLOT(sl_message(QString)));
    connect(m_lift, SIGNAL(sig_finish()),this, SLOT(sl_finish()));

    on_pb_apply_clicked();
    m_thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    m_thread->quit();
    m_thread->wait();

  if(!m_lift)
    delete m_lift;
}

void MainWindow::on_pb_clearDump_clicked() //Очистка дампа
{
  qDebug()<<"Clear!!!";
  ui->textEdit->clear();
}

void MainWindow::on_pb_apply_clicked()//Применить параметры
{
  SLiftParams slp;
  slp.nFloor = ui->sb_nFloor->value();
  slp.hFloor = ui->sb_hFloor->value();
  slp.speed  =  ui->sb_speed->value();
  slp.doorTime = ui->sb_doorTime->value();
  ui->sb_floor->setMaximum(slp.nFloor);
  ui->sb_lift->setMaximum(slp.nFloor);
  emit sig_changeParams(slp);
}

void MainWindow::on_pb_lift_clicked() //Вызвать лифт с этажа
{
  if(!m_blokFl)
  {//Если лифт свободен
    m_blokFl = true;
    emit sig_moove(ui->sb_lift->value());
  }
  else
    sl_message("Лифт занят!!!\n");
}

void MainWindow::on_pb_floor_clicked() //Нажать кнопку в кабине
{
  if(!m_blokFl)
  {//Если лифт свободен
    m_blokFl = true;
    emit sig_moove(ui->sb_floor->value());
  }
  else
    sl_message("Лифт занят!!!\n");
}

//Вывод сообщений
void MainWindow::sl_message(QString str)
{
  ui->textEdit->insertPlainText(str);
}

//Лифт выполнил команду
void MainWindow::sl_finish()
{
  m_blokFl = false;
}
