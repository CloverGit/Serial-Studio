/*
 * Copyright (c) 2020-2023 Alex Spataru <https://github.com/alex-spataru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <QScreen>
#include <QApplication>
#include <QTimerEvent>
#include "Misc/TimerEvents.h"

/**
 * Returns a pointer to the only instance of the class
 */
Misc::TimerEvents &Misc::TimerEvents::instance()
{
  static TimerEvents singleton;
  return singleton;
}

/**
 * Stops all the timers of this module
 */
void Misc::TimerEvents::stopTimers()
{
  m_timer1Hz.stop();
  m_timer10Hz.stop();
  m_timer20Hz.stop();
  m_timer24Hz.stop();
}

/**
 * Emits the @c timeout signal when the basic timer expires
 */
void Misc::TimerEvents::timerEvent(QTimerEvent *event)
{
  if (event->timerId() == m_timer1Hz.timerId())
    Q_EMIT timeout1Hz();

  else if (event->timerId() == m_timer10Hz.timerId())
    Q_EMIT timeout10Hz();

  else if (event->timerId() == m_timer20Hz.timerId())
    Q_EMIT timeout20Hz();

  else if (event->timerId() == m_timer24Hz.timerId())
    Q_EMIT timeout24Hz();

  else if (event->timerId() == m_screenTimer.timerId())
    Q_EMIT timeoutScreen();
}

/**
 * Starts all the timer of the module
 */
void Misc::TimerEvents::startTimers()
{
  int screenHz = 32;
  if (qApp->primaryScreen())
    screenHz = qMin(screenHz, qFloor(qApp->primaryScreen()->refreshRate()));

  m_timer1Hz.start(1000, Qt::PreciseTimer, this);
  m_timer20Hz.start(1000 / 20, Qt::PreciseTimer, this);
  m_timer24Hz.start(1000 / 24, Qt::PreciseTimer, this);
  m_timer10Hz.start(1000 / 10, Qt::PreciseTimer, this);
  m_screenTimer.start(1000 / screenHz, Qt::PreciseTimer, this);
}
