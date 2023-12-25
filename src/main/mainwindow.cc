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
  for (int i = 0; i < TOOLBAR_SIZE; i++)
  {
    delete toolbar[i];
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
  QPixmap *p_tool = new QPixmap("./res/toolbar.png");
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
  std::string temp_name = "";
  for (int i = 0; i < TOOLBAR_SIZE; i++)
  {
    if (page * 14 + i < bag.size())
    {
      temp_name = bag[page * 14 + i];
    }
    SceneButton *temp = new SceneButton(
        36 + i * (8 + 56), 644, 56, 56, "", "", [temp_name, this]()
        {inhand=temp_name;
        QMessageBox::information(this,"",QString::fromStdString(inhand)); },
        this);
    toolbar.push_back(temp);
  }

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
      0, 360, "desk", "./res/scene1_desk.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene_desk";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene->AddSceneButton(s1_desk);

  SceneButton *s1_computer = new SceneButton(
      123, 320, "computer", "./res/scene1_computer.png",
      [&, this]()
      {
        QMessageBox::information(this, "", "computer");
      },
      this);
  scene->AddSceneButton(s1_computer);

  SceneButton *s1_bed = new SceneButton(
      596, 408, "bed", "./res/scene1_bed.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_nightstand";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene->AddSceneButton(s1_bed);

  SceneButton *s1_nightstand = new SceneButton(
      844, 508, "nightstand", "./res/scene1_nightstand.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_nightstand";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene->AddSceneButton(s1_nightstand);

  SceneButton *s1_plant = new SceneButton(
      39, 310, "plant", "./res/scene1_plant.png",
      [&, this]()
      {
        QMessageBox::information(this, "", "plant");
      },
      this);
  scene->AddSceneButton(s1_plant);

  SceneButton *s1_window = new SceneButton(
      239, 124, "window", "./res/scene1_window.png",
      [&, this]()
      {
        QMessageBox::information(this, "", "window");
      },
      this);
  scene->AddSceneButton(s1_window);

  SceneButton *left = new SceneButton(
      10, 340, "left", "./res/left_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene3";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "right", "./res/right_arrow.png",
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
      448, 580, "down_arrow", "./res/down_arrow.png",
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
      0, 360, "bed", "./res/scene2_bed.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_nightstand";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(bed);

  SceneButton *nightstand = new SceneButton(
      212, 408, "nightstand", "./res/scene2_nightstand.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_nightstand";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(nightstand);

  SceneButton *shelf = new SceneButton(
      300, 164, "shelf", "./res/scene2_shelf.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_shelf";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(shelf);

  SceneButton *waterpot = new SceneButton(
      418, 132, "waterpot", "./res/scene2_waterpot.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_shelf";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(waterpot);

  SceneButton *plant = new SceneButton(
      340, 148, "plant", "./res/scene2_plant.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_shelf";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(plant);

  SceneButton *paint = new SceneButton(
      636, 100, "paint", "./res/scene2_paint_state1.png",
      [&, this]()
      {
        QMessageBox::information(this, "scene2", "paint");
      },
      this);
  scene1->AddSceneButton(paint);

  SceneButton *left = new SceneButton(
      10, 340, "left", "./res/left_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "right", "./res/right_arrow.png",
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
      448, 580, "down_arrow", "./res/down_arrow.png",
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

  SceneButton *scene1_nightstand_bed = new SceneButton(
      0, 104, "nightstand_bed", "./res/scene2_nightstand_bed.png",
      []() {
      },
      this);
  scene1_nightstand->AddSceneButton(scene1_nightstand_bed);

  SceneButton *scene1_nightstand_pillow = new SceneButton(
      6, 336, "nightstand_pillow", "./res/scene2_nightstand_pillow.png",
      [&, this]() { 
        QMessageBox::information(this, "scene2", "pillow");
      },
      this);
  scene1_nightstand->AddSceneButton(scene1_nightstand_pillow);

  SceneButton *scene1_nightstand_return_button = new SceneButton(
      448, 580, "down_arrow", "./res/down_arrow.png",
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
      10, 340, "left_arrow", "./res/left_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene2->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "right_arrow", "./res/right_arrow.png",
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
      10, 340, "left_arrow", "./res/left_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene2";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene3->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "right_arrow", "./res/right_arrow.png",
      [&, this]()
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene3->AddSceneButton(right);
}
