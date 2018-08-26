#ifndef ZTOOLTIP_H
#define ZTOOLTIP_H
#include <QTextEdit>

class ZToolTip : public QTextEdit
{
    Q_OBJECT

public:
    ZToolTip(QWidget* parent = 0);
    ~ZToolTip();
    void start();

protected slots:
    void setOpacity();

protected:
//    void paintEvent(QPaintEvent *e);

    QTimer *m_timer;
    int m_currentAlpha;
    QColor m_startColor;
    int m_duration;
    qreal m_opacity;
};

#endif // ZTOOLTIP_H
