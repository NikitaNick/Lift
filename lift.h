#ifndef LIFT_H
#define LIFT_H

#include <QObject>
#include <QTimerEvent>
#include <QDebug>
#include <QTime>
#include <QTimer>

struct SLiftParams
{
 // SLiftParams() {}
  int    nFloor;  //Число этажей
  double hFloor,  //Высота этажа, м
         speed,   //Скорость, м/с
         doorTime;//Время между открытием и закрытием дверей, с
};

Q_DECLARE_METATYPE(SLiftParams)

class TLift : public QObject
{
  Q_OBJECT
public:
  TLift();
  ~TLift();

protected:
  void timerEvent(QTimerEvent* ev);

public slots:
  void sl_moove(int);      //Перемещение/движение лифта на заданный этаж
  //Получить параметры
  void sl_setParams(SLiftParams);

  //Открыть/Закрыть дверь
  void sl_openDoor();
  void sl_closeDoor();

signals:
  void sig_message(QString); //Выдача сообщений
  void sig_finish();         //Перемещение окончено

protected:
  int              m_timer,         //Таймер
                       //Таймер для открытия/закрытия двери
                   m_currentFloor,  //Текущее положение лифта
                   m_floorTime,     //Время для перемещения на 1 этаж, мс
                   m_floorNeed;     //Заданный(необходимый) этаж
  SLiftParams      m_params;        //Параметры
  bool             m_upFl,          //Движение вверх или вниз
                   m_doorFl;        //Флаг положения двери (true - открыта)

  int m_timerDoor;
};

#endif // LIFT_H
