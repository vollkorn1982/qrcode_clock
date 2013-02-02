#include "qrlabel.h"

#include <QDebug>

QRLabel::QRLabel(QWidget *parent) :
  QLabel(parent)
{
}

void QRLabel::resizeEvent(QResizeEvent *)
{
  QSize scaledSize = m_originalPixmap.size();
  scaledSize.scale(size(), Qt::KeepAspectRatio);
  if (!pixmap() || scaledSize != pixmap()->size())
    adjustPixmapSize();
}

void QRLabel::adjustPixmapSize()
{
  QLabel::setPixmap(m_originalPixmap.scaled(size(), Qt::KeepAspectRatio));
  setMinimumSize(100, 100);
}

void QRLabel::setPixmap(const QPixmap &pixmap)
{
  m_originalPixmap = pixmap;
  adjustPixmapSize();
}
