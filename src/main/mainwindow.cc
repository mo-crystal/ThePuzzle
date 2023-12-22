#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->stackedWidget->setStyleSheet("background-color: transparent;");
  Init();

  FLASHTIMER = startTimer(100);
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
  Room1Init();
  Room2Init();
  Room3Init();
  Room4Init();
  /*
  QPixmap cursorPixmap("./res/cursor_hovor.png");
  QCursor customCursor(cursorPixmap);
  setCursor(customCursor);
  */
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

void MainWindow::Room1Init()
{
  Scene *scene = new Scene("./res/bgp.png", "");
  AddScene("scene", scene, 1);

  SceneButton *s1_desk = new SceneButton(
      0, 360, "./res/scene1_desk.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene_desk";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene->AddSceneButton(s1_desk);

  SceneButton *s1_computer = new SceneButton(
      123, 320, "./res/scene1_computer.png",
      [&, this]()
      {
        QMessageBox::information(this, "", "computer");
      },
      this);
  scene->AddSceneButton(s1_computer);

  SceneButton *s1_bed = new SceneButton(
      596, 408, "./res/scene1_bed.png",
      [&, this]()
      {
        QMessageBox::information(this, "", "bed");
      },
      this);
  scene->AddSceneButton(s1_bed);

  SceneButton *s1_plant = new SceneButton(
      39, 310, "./res/scene1_plant.png",
      [&, this]()
      {
        QMessageBox::information(this, "", "plant");
      },
      this);
  scene->AddSceneButton(s1_plant);

  SceneButton *s1_window = new SceneButton(
      239, 124, "./res/scene1_window.png",
      [&, this]()
      {
        QMessageBox::information(this, "", "window");
      },
      this);
  scene->AddSceneButton(s1_window);

  SceneButton *left = new SceneButton(
      10, 340, "./res/left_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene3";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "./res/right_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene->AddSceneButton(right);

  Scene *scene_desk = new Scene("./res/bgp_scene1_desk.png", "");
  AddScene("scene_desk", scene_desk);

  SceneButton *scene_desk_return_button = new SceneButton(
      448, 580, "./res/down_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene_desk->AddSceneButton(scene_desk_return_button);
}

void MainWindow::Room2Init()
{
  Scene *scene1 = new Scene("./res/bgp_blank.png", "");
  AddScene("scene1", scene1);

  SceneButton *bed = new SceneButton(
      0, 360, "./res/scene2_bed.png",
      [&, this]()
      {
        QMessageBox::information(this, "scene2", "bed");
      },
      this);
  scene1->AddSceneButton(bed);

  SceneButton *left = new SceneButton(
      10, 340, "./res/left_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "./res/right_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene2";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(right);
}

void MainWindow::Room3Init()
{

  Scene *scene2 = new Scene("./res/bgp_blank.png", "");
  AddScene("scene2", scene2);
  SceneButton *left = new SceneButton(
      10, 340, "./res/left_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene2->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "./res/right_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene3";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene2->AddSceneButton(right);
}

void MainWindow::Room4Init()
{
  Scene *scene3 = new Scene("./res/bgp_blank.png", "");
  AddScene("scene3", scene3);
  SceneButton *left = new SceneButton(
      10, 340, "./res/left_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene2";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene3->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "./res/right_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene3->AddSceneButton(right);
}
