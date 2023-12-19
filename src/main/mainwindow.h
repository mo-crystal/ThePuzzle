#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <random>
#include <list>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

#include <QMainWindow>
#include <QPainter>
#include <QMovie>
#include <QDebug>

#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QTimer>

#define DEFUALT_WIDTH 960
#define DEFUALT_HEIGHT 640
#define BLOCK_SIZE 64
#define START_PAGE_BUTTON_WIDTH DEFUALT_WIDTH / 6
#define DECORATE_SIZE 32
#define MAP_WIDTH 256
#define MAP_HEIGHT 256
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void paintEvent(QPaintEvent *event);
  void timerEvent(QTimerEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  void handleDelayedKeyRelease();
  void mousePressEvent(QMouseEvent *event);

  void Init();

private:
  Ui::MainWindow *ui;

  bool isplaying = false;
  
private slots:

};

#endif // MAINWINDOW_H
