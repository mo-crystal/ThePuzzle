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
#define START_PAGE_BUTTON_WIDTH DEFUALT_WIDTH / 6
#define TOOLBAR_SIZE 14

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
  void Use(std::string item_name);
  void Init();
  void Room1Init();
  void Room2Init();
  void Room3Init();
  void Room4Init();
  void ToolbarRefresh();

private:
  Ui::MainWindow *ui;
  std::map<std::string, Scene *> Scenes;
  std::vector<SceneButton *> toolbar;
  std::vector<std::string> bag;
  int page = 0;
  std::string inhand = "";
  bool isplaying = false;
  int FLASHTIMER;
private slots:
};

#endif // MAINWINDOW_H
