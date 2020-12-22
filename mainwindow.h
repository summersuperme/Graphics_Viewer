#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <graphics.h>
#include <QGraphicsScene>
#include <QFileInfo>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>
#include <QPixmap>
#include <QMessageBox>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMenu>
#include "qcustomgraphicseffect.h"
#include "qenhancedgraphicsview.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
private slots:
    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    QPixmap pixmap;
    QGraphicsPixmapItem *item;
};
#endif // MAINWINDOW_H
