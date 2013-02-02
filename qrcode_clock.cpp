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
//  setWindowState(windowState() ^ Qt::WindowFullScreen);

  // hide cursor
  setCursor(Qt::BlankCursor);

  // quit application at ESC
  QAction *exitAct = new QAction(this);
  exitAct->setShortcut(Qt::Key_Escape);
  connect(exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));
  addAction(exitAct);

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
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
  timer->start(1000);

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
  QRcode *qrCodeMatrix(QRcode_encodeString8bit(timeStr.toAscii(), 0, QR_ECLEVEL_L));

  // transfer QR code into picture
  m_qrImage = new QImage(qrCodeMatrix->width, qrCodeMatrix->width, QImage::Format_Mono);
  for (int i = 0; i < qrCodeMatrix->width; ++i) {
      for (int j = 0; j < qrCodeMatrix->width; ++j) {
          m_qrImage->setPixel(i, j, qrCodeMatrix->data[i * qrCodeMatrix->width + j] & 1);
        }
    }

  QRcode_free(qrCodeMatrix);

  m_qrImage->setColor(0, qRgb(255,255,255));
  m_qrImage->setColor(1, qRgb(0,0,0));

  m_qrClock->setPixmap(QPixmap::fromImage(*m_qrImage));

  // show human readable time
  m_humanClock->setText(time.toUTC().toString() + " UTC");
}
