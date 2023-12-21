#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->stackedWidget->setStyleSheet("background-color: transparent;");
  Init();
  FLASHTIMER = startTimer(100);

  Scene *scene = new Scene("./res/bgp.png", "");

  AddScene("0", scene);

  Scene *scene1 = new Scene("./res/bgp1.png", "");
  AddScene("1", scene1, 1);

  nowScene = "1";

  SceneButton *bottle = new SceneButton(
      100, 244, "./res/bottle.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "1";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene->AddSceneButton(bottle);

  SceneButton *bottle1 = new SceneButton(
      100, 100, "./res/test.gif",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "0";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(bottle1);
}

MainWindow::~MainWindow()
{
  delete ui;
  for (auto i = Scenes.begin(); i != Scenes.end(); i++)
  {
    delete (*i).second;
  }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
  if (event->timerId() == FLASHTIMER)
  {
    repaint();
  }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  QPixmap *p = new QPixmap(QString::fromStdString(Scenes[nowScene]->GetSceneBGP()));
  painter.drawPixmap(0, 0, DEFUALT_WIDTH, DEFUALT_HEIGHT, *p);
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

void MainWindow::AddScene(std::string name, Scene *s, bool default_scene)
{
  Scenes[name] = s;
  if (default_scene)
  {
    nowScene = name;
    s->SceneShow();
  }
}