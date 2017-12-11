#include "lift.h"

TLift::TLift() : QObject()
{
  m_currentFloor = 1;
  m_floorTime = 1000;
  m_doorFl = false;
}

TLift::~TLift()
{

}

void TLift::timerEvent(QTimerEvent* ev)
{
  if(ev->timerId() == m_timer)
  {
    if(m_upFl)
      m_currentFloor++;
    else
      m_currentFloor--;
    emit sig_message(QString("Лифт на этаже №%1\n").arg(m_currentFloor));
    if(m_currentFloor == m_floorNeed)
    {//Завершить перемещение лифта
      killTimer(m_timer);
      sl_openDoor();
    }
  }
}

//Получить параметры
void TLift::sl_setParams(SLiftParams slp)
{
  qDebug()<<"Set lift parameters!!!";
  m_params    = slp;
  m_floorTime = m_params.hFloor / m_params.speed * 1000;
}

//Перемещение/движение лифта
void TLift::sl_moove(int floor)
{
  m_floorNeed = floor;
  if(m_currentFloor == m_floorNeed)
    sl_openDoor();
  else
  {
    m_upFl = true;
    if(m_floorNeed < m_currentFloor)
      m_upFl = false;
    m_timer = startTimer(m_floorTime);
  }
}

//Открыть/Закрыть дверь
void TLift::sl_openDoor()
{
  emit sig_message("Дверь открылась\n");
  QTimer::singleShot(m_params.doorTime *1000,this,SLOT(sl_closeDoor()));
}

void TLift::sl_closeDoor()
{
  emit sig_message("Дверь закрылась\n");
  emit sig_finish();
}
