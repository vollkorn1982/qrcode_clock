#ifndef QRCODE_CLOCK_H
#define QRCODE_CLOCK_H

#include <QMainWindow>
#include <QSize>

class QRLabel;
class QLabel;
class QImage;

namespace Ui {
  class qrcode_clock;
}

class qrcode_clock : public QMainWindow
{
  Q_OBJECT

public:
  explicit qrcode_clock(QWidget *parent = 0);
  ~qrcode_clock();

private slots:
  void updateTime();
#ifdef QT_DEBUG
  void startStop();
#endif

private:
  Ui::qrcode_clock *ui;
  QRLabel          *m_qrClock;
  QLabel           *m_humanClock;
  QImage           *m_qrImage;
  QSize             m_clockSize;
  QTimer           *m_timer;
};

#endif // QRCODE_CLOCK_H
