#ifndef QCUSTOMGRAPHICSEFFECT_H
#define QCUSTOMGRAPHICSEFFECT_H

#include <QObject>
#include <QGraphicsEffect>
#include <QPainter>
#include <QDebug>
class QCustomGraphicsEffect : public QGraphicsEffect
{
    Q_OBJECT
public:
    explicit QCustomGraphicsEffect(QObject *parent = nullptr);

signals:

public slots:

protected:
    void draw(QPainter *painter) override;
};

#endif // QCUSTOMGRAPHICSEFFECT_H
