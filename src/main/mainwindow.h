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
#include <QMessageBox>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QTimer>

#include "../core/scene.h"

#define DEFUALT_WIDTH 960
#define DEFUALT_HEIGHT 640
#define DEFUALT_HEIGHT_TOOLBAR 60
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
  std::string nowScene;

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void paintEvent(QPaintEvent *event);
  void timerEvent(QTimerEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  void handleDelayedKeyRelease();
  void mousePressEvent(QMouseEvent *event);
  void AddScene(std::string name, Scene *, bool default_scene = 0);
  void Init();
  void Room1Init();
  void Room2Init();
  void Room3Init();
  void Room4Init();
private:
  Ui::MainWindow *ui;
  std::map<std::string, Scene *> Scenes;

  bool isplaying = false;
  int FLASHTIMER;
private slots:
};

#endif // MAINWINDOW_H
