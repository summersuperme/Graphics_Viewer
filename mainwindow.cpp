#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置场景显示于当前窗口下
    //scene.setParent(this);
    setAcceptDrops(true);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setAcceptDrops(false);
    ui->graphicsView->setInteractive(true);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->graphicsView->setRubberBandSelectionMode(Qt::ContainsItemShape);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete item;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    QStringList acceptFileTypes;
    acceptFileTypes.append("jpg");
    acceptFileTypes.append("png");
    acceptFileTypes.append("bmp");

    if(event->mimeData()->hasUrls() && event->mimeData()->urls().count() ==1)
    {
        QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
        /*
         * 判断acceptFileTypes是否包含拖拽文件的后缀名
         * suffix用于提取后缀名
         * toLower把大写字母转换为小写字母
         */
        if(acceptFileTypes.contains(file.suffix().toLower()))
            event->acceptProposedAction();
    }
}

/*
 * 加载拖拽文件并展示在label标签中
 */
void MainWindow::dropEvent(QDropEvent *event)
{
    //保证加载新图像时重置缩放比例
    ui->graphicsView->resetTransform();
    QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
    if(pixmap.load(file.absoluteFilePath()))
    {
        QPoint viewPos = ui->graphicsView->mapFromParent(event->pos());
        QPointF sceneDropPos = ui->graphicsView->mapToScene(viewPos);
        item = new QGraphicsPixmapItem(pixmap);
        scene.addItem(item);
        item->setPos(sceneDropPos);
        item->setFlag(QGraphicsItem::ItemIsSelectable);
        item->setAcceptedMouseButtons(Qt::LeftButton);
        ui->graphicsView->show();
    }
    else
    {
        QMessageBox::critical(this,tr("Error"),
                              tr("The image file cannot be read!"));
    }

}

void MainWindow::on_pushButton_clicked()
{
    item->setGraphicsEffect(new QCustomGraphicsEffect(this));
    ui->graphicsView->show();
}
