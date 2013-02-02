#ifndef QRLABEL_H
#define QRLABEL_H

#include <QLabel>

class QRLabel : public QLabel
{
  Q_OBJECT
public:
  explicit QRLabel(QWidget *parent = 0);
  void setPixmap(const QPixmap &pixmap);

protected:
  void resizeEvent(QResizeEvent *);
  void adjustPixmapSize();

signals:
  
public slots:

private:
  QPixmap m_originalPixmap;
};

#endif // QRLABEL_H
