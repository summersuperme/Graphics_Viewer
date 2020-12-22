#include "qenhancedgraphicsview.h"
#include <QDebug>
QEnhancedGraphicsView::QEnhancedGraphicsView(QWidget *parent) : QGraphicsView(parent)
{

}

void QEnhancedGraphicsView::wheelEvent(QWheelEvent *event)
{
    if(event->orientation() == Qt::Vertical)
    {
        double angleDeltaY = event->angleDelta().y();
        double zoomFactor = qPow(1.0015,angleDeltaY);
        scale(zoomFactor,zoomFactor);
        this->viewport()->update();
        event->accept();
    }
    else{
        event->ignore();
    }
}

void QEnhancedGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        QMenu menu;
        QAction *clearAllAction = menu.addAction("清除全部");
        connect(clearAllAction,SIGNAL(triggered(bool)),
                this,SLOT(clearAll(bool)));
        QAction *clearselectedAction = menu.addAction("删除被选择");
        connect(clearselectedAction,SIGNAL(triggered(bool)),
                this,SLOT(clearSelected(bool)));
        QAction *noEffectAction = menu.addAction("清晰");
        connect(noEffectAction,SIGNAL(triggered(bool)),
                this,SLOT(noEffect(bool)));
        QAction *blurEffectAction = menu.addAction("模糊");
        connect(blurEffectAction,SIGNAL(triggered(bool)),
                this,SLOT(blurEffect(bool)));
        QAction *dropShadowEffectAction = menu.addAction("加阴影");
        connect(dropShadowEffectAction,SIGNAL(triggered(bool)),
                this,SLOT(dropShadowEffect(bool)));
        QAction *colorizeEffectAction = menu.addAction("变颜色");
        connect(colorizeEffectAction,SIGNAL(triggered(bool)),
                this,SLOT(colorizeEffect(bool)));
        QAction *customEffectAction = menu.addAction("清晰度");
        connect(customEffectAction,SIGNAL(triggered(bool)),
                this,SLOT(customEffect(bool)));
        menu.exec(event->globalPos());
        event->accept();
    }
    else{
        QGraphicsView::mousePressEvent(event);
    }
}

void QEnhancedGraphicsView::clearAll(bool)
{
    scene()->clear();
}

void QEnhancedGraphicsView::clearSelected(bool)
{
    while(scene()->selectedItems().count()>0)
    {
        delete  scene()->selectedItems().at(0);
        scene()->selectedItems().removeAt(0);
    }
}

void QEnhancedGraphicsView::noEffect(bool)
{
    foreach (QGraphicsItem *item,scene()->selectedItems()) {
        item->setGraphicsEffect(Q_NULLPTR);
    }
}

void QEnhancedGraphicsView::blurEffect(bool)
{
    foreach (QGraphicsItem *item,scene()->selectedItems()) {
        item->setGraphicsEffect(new QGraphicsBlurEffect(this));
    }
}

void QEnhancedGraphicsView::dropShadowEffect(bool)
{
    foreach (QGraphicsItem *item,scene()->selectedItems()) {
        item->setGraphicsEffect(new QGraphicsDropShadowEffect(this));
    }
}

void QEnhancedGraphicsView::colorizeEffect(bool)
{
    foreach (QGraphicsItem *item,scene()->selectedItems()) {
        item->setGraphicsEffect(new QGraphicsColorizeEffect(this));
    }
}

void QEnhancedGraphicsView::customEffect(bool)
{
    foreach (QGraphicsItem *item,scene()->selectedItems()) {
        item->setGraphicsEffect(new QGraphicsOpacityEffect(this));
    }
}
