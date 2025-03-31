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
