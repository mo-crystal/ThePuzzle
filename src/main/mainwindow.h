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
#include <QSound>
#include <QProcess>

#include "../core/scene.h"
#include "../core/item.h"

#define DEFUALT_WIDTH 960
#define DEFUALT_HEIGHT 640
#define DEFUALT_HEIGHT_TOOLBAR 60
#define START_PAGE_BUTTON_WIDTH DEFUALT_WIDTH / 6
#define TOOLBAR_SIZE 14
#define DESCRIPTIONTIME 4000
#define NOFOUND -2

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
  int Use(std::string item_name);
  void Init();
  void Room1Init();
  void Room2Init();
  void Room3Init();
  void Room4Init();
  void ToolbarRefresh();
  void ShowDescription(std::string descrip);
  void AddItem(std::string name, Item item);
  bool CheckState(std::string scene_name, std::string button_name, std::string state);
  void SetState(std::string scene_name, std::string button_name, std::string state);
  void SetVisible(std::string scene_name, std::string name, bool state);
  void SetValid(std::string scene_name, std::string name, bool state);
  void Start();
  void ShowToolbar(bool state);
  void SceneChange(std::string scene_name);
  void Reset();
  void InitPuzzle(std::string puzzle_name);
private:
  Ui::MainWindow *ui;
  std::map<std::string, Scene *> Scenes;
  std::vector<SceneButton *> toolbar;
  std::map<std::string, Item> bag;
  int page = 0;
  std::string inhand = "";
  bool isplaying = false;
  int FLASHTIMER;
  QTimer *description_label_timer = NULL;
  std::map<std::string, std::vector<SceneButton *>> puzzles;
  bool toolbarVisible = false;
  QMediaPlayer *mediaPlayer;
  QMediaPlaylist *playlist;
private slots:
};

#endif // MAINWINDOW_H
