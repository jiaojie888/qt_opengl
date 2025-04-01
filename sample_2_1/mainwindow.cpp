#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->openGLWidget);

    ui->toolBar->setMovable(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDrawRect_triggered()
{
    ui->openGLWidget->drawShape(MyOpenGLWidget::Rect);
}


void MainWindow::on_actionClear_triggered()
{
    ui->openGLWidget->drawShape(MyOpenGLWidget::None);
}


void MainWindow::on_actionWireframe_triggered(bool checked)
{
    ui->openGLWidget->setWireFrame(checked);
}

