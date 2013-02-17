#include "qrcode_clock.h"
#include "ui_qrcode_clock.h"
#include <qrencode.h>
#include <QLabel>
#include <QDebug>
#include <QPalette>
#include <QDateTime>
#include <QTimer>
#include <QAction>

#include "qrlabel.h"

qrcode_clock::qrcode_clock(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::qrcode_clock)
{
  ui->setupUi(this);

  // go fullscreen
  setWindowState(windowState() ^ Qt::WindowFullScreen);

  // hide cursor
  setCursor(Qt::BlankCursor);

  // quit application at ESC
  QAction *exitAct = new QAction(this);
  exitAct->setShortcut(Qt::Key_Escape);
  connect(exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));
  addAction(exitAct);

#ifdef QT_DEBUG
  // pause resume clock with space.
  // JUST FOR DEBUGGING, DEFEATS THE PURPOSE OF SHOWING ACCURATE TIME!!!
  QAction *startStopAct = new QAction(this);
  startStopAct->setShortcut(Qt::Key_Space);
  connect(startStopAct, SIGNAL(triggered()), this, SLOT(startStop()));
  addAction(startStopAct);
#endif

  m_qrClock = findChild<QRLabel*>("clock");
  if (!m_qrClock) {
      qDebug() << "QLabel named 'clock' not found!";
      qApp->exit();
    }

  m_humanClock = findChild<QLabel*>("time");
  if (!m_humanClock) {
      qDebug() << "QLabel named 'time' not found!";
      qApp->exit();
    }

  // start timer which encodes the time every second
  m_timer = new QTimer(this);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTime()));
  m_timer->start(1000);

  // set background color to white
  QPalette pal = palette();
  pal.setColor(QPalette::Window, QColor(Qt::white));
  setPalette(pal);

  // initialize clock
  updateTime();
}

qrcode_clock::~qrcode_clock()
{
  delete ui;
}

void qrcode_clock::updateTime()
{
  // get time
  QDateTime time = QDateTime::currentDateTime();
  QString timeStr(QString::number(time.toTime_t()));

  // encode time as QR code
  QRcode *qrCodeMatrix(QRcode_encodeString8bit(timeStr.toStdString().c_str(), 0, QR_ECLEVEL_L));

  if (!qrCodeMatrix) {
      qDebug() << "kein QrCode erzeugt";
      return;
    }

  // transfer QR code into picture
  m_qrImage = new QImage(qrCodeMatrix->width, qrCodeMatrix->width, QImage::Format_Mono);
  for (int i = 0; i < qrCodeMatrix->width; ++i) {
      for (int j = 0; j < qrCodeMatrix->width; ++j) {
          m_qrImage->setPixel(j, i, qrCodeMatrix->data[i * qrCodeMatrix->width + j] & 1);
        }
    }

  QRcode_free(qrCodeMatrix);

  m_qrImage->setColor(0, qRgb(255,255,255));
  m_qrImage->setColor(1, qRgb(0,0,0));

  m_qrClock->setPixmap(QPixmap::fromImage(*m_qrImage));

  // show human readable time
  m_humanClock->setText(time.toUTC().toString() + " UTC");
}

#ifdef QT_DEBUG
void qrcode_clock::startStop()
{
  if (m_timer->isActive())
    m_timer->stop();
  else
    m_timer->start();
}
#endif
