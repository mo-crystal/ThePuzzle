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
  QPixmap *p_tool=new QPixmap("./res/toolbar.png");
  painter.drawPixmap(0, DEFUALT_HEIGHT, DEFUALT_WIDTH, DEFUALT_HEIGHT_TOOLBAR, *p_tool);

  delete p;
  delete p_tool;
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
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
}

void MainWindow::AddScene(std::string name, Scene *s, bool default_scene)
{
  Scenes[name] = s;
  if (default_scene)
  {
    if (Scenes.find(nowScene) != Scenes.end())
    {
      Scenes[nowScene]->SceneDisappear();
    }
    nowScene = name;
    s->SceneShow();
  }
}

void MainWindow::Room1Init()
{
  Scene *scene = new Scene("./res/bgp_scene1.png", "");
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

  SceneButton *s1_nightstand = new SceneButton(
      844, 508, "./res/scene1_nightstand.png",
      [&, this]()
      {
        QMessageBox::information(this, "", "nightstand");
      },
      this);
  scene->AddSceneButton(s1_nightstand);

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
  Scene *scene1 = new Scene("./res/scene2.png", "");
  AddScene("scene1", scene1, 1);

  SceneButton *bed = new SceneButton(
      0, 360, "./res/scene2_bed.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_nightstand";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(bed);

  SceneButton *nightstand = new SceneButton(
      212, 408, "./res/scene2_nightstand.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_nightstand";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(nightstand);

  SceneButton *shelf = new SceneButton(
      300, 164, "./res/scene2_shelf.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_shelf";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(shelf);

  SceneButton *waterpot = new SceneButton(
      418, 132, "./res/scene2_waterpot.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_shelf";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(waterpot);

  SceneButton *plant = new SceneButton(
      340, 148, "./res/scene2_plant.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_shelf";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(plant);

  SceneButton *paint = new SceneButton(
      636, 100, "./res/scene2_paint_state1.png",
      [&, this]()
      {
        QMessageBox::information(this, "scene2", "paint");
      },
      this);
  scene1->AddSceneButton(paint);

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

  Scene *scene1_shelf = new Scene("./res/bgp_scene2_shelf.png", "");
  AddScene("scene1_shelf", scene1_shelf);

  SceneButton *scene1_shelf_return_button = new SceneButton(
      448, 580, "./res/down_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1_shelf->AddSceneButton(scene1_shelf_return_button);

  Scene *scene1_nightstand = new Scene("./res/bgp_scene2_nightstand.png", "");
  AddScene("scene1_nightstand", scene1_nightstand);

  SceneButton *scene1_nightstand_return_button = new SceneButton(
      448, 580, "./res/down_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1_nightstand->AddSceneButton(scene1_nightstand_return_button);
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
