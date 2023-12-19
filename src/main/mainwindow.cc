#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->stackedWidget->setStyleSheet("background-color: transparent;");
  Init();


}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{

}

void MainWindow::paintEvent(QPaintEvent *event)
{

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

}



void MainWindow::Init()
{

}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
 
}

