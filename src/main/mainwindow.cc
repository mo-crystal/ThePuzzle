#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->stackedWidget->setStyleSheet("background-color: transparent;");
  ui->label->setVisible(false);
  Init();
  FLASHTIMER = startTimer(100);
  description_label_timer = new QTimer(this);
  description_label_timer->setInterval(DESCRIPTIONTIME);
  connect(description_label_timer, &QTimer::timeout, this, [=]()
          { ui->label->hide(); });
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
  QPixmap *frame = new QPixmap(QString::fromStdString("./res/items/selectframe.png"));
  for (int i = 0; i < TOOLBAR_SIZE; i++)
  {
    if (toolbar[i]->GetName() == inhand && inhand != "")
    {
      painter.drawPixmap(36 + i * (8 + 56), 644, 56, 56, *frame);
    }
  }

  delete p;
  delete frame;
  delete p_tool;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
}

void MainWindow::Use(std::string item_name)
{
  if (bag.find(item_name) != bag.end())
  {
    int res = bag[item_name].Use();
    if (res == EMPTY)
    {
      bag.erase(item_name);
    }
    else if (res == NOTENOUGH)
    {
      ShowDescription("I haven't found enough of this yet.");
    }
    else
    {
    }
    ToolbarRefresh();
  }
}

void MainWindow::Init()
{
  std::string temp_name = "";
  std::string temp_path = "";
  for (int i = 0; i < TOOLBAR_SIZE; i++)
  {
    if (page * 14 + i < bag.size())
    {
      auto it = bag.begin();
      advance(it, page * 14 + i);
      temp_name = (*it).first;
      temp_path = "./res/items/" + temp_name + ".png";
      // QMessageBox::information(this, "", QString::fromStdString(temp_path));
    }
    SceneButton *temp = new SceneButton(
        36 + i * (8 + 56), 644, 56, 56, temp_name, temp_path, [temp_name, this](SceneButton &obj)
        {
          if(inhand == obj.GetName()){
            ShowDescription(obj.GetDescription()); 
          } inhand = obj.GetName(); },
        this, "");
    toolbar.push_back(temp);
  }
  ToolbarRefresh();
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
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene_desk";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene->AddSceneButton(s1_desk);

  SceneButton *s1_computer = new SceneButton(
      123, 320, "computer", "./res/scene1_computer.png",
      [&, this](SceneButton &obj)
      {
        ShowDescription(obj.GetDescription());
      },
      this, "Some unimportant news.");
  scene->AddSceneButton(s1_computer);

  SceneButton *s1_bed = new SceneButton(
      596, 408, "bed", "./res/scene1_bed.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_nightstand";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene->AddSceneButton(s1_bed);

  SceneButton *s1_nightstand = new SceneButton(
      844, 508, "nightstand", "./res/scene1_nightstand.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_nightstand";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene->AddSceneButton(s1_nightstand);

  SceneButton *s1_plant = new SceneButton(
      39, 310, "plant", "./res/scene1_plant.png",
      [&, this](SceneButton &obj)
      {
        ShowDescription(obj.GetDescription());
      },
      this, "It's growing pretty well.");
  scene->AddSceneButton(s1_plant);

  SceneButton *s1_window = new SceneButton(
      239, 124, "window", "./res/scene1_window.png",
      [&, this](SceneButton &obj)
      {
        ShowDescription(obj.GetDescription());
      },
      this, "Am I on an island?");
  scene->AddSceneButton(s1_window);

  SceneButton *left = new SceneButton(
      10, 340, "left", "./res/left_arrow.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene3";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "right", "./res/right_arrow.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene->AddSceneButton(right);

  Scene *scene_desk = new Scene("./res/bgp_scene1_desk.png", "");
  AddScene("scene_desk", scene_desk);

  SceneButton *puzzle_piece = new SceneButton(
      652, 420, "puzzle_piece", "./res/puzzle_piece.png",
      [&, this](SceneButton &obj)
      {
        Item puzzle_piece(9, 1, "Piece.");
        AddItem("puzzle_piece", puzzle_piece);
        obj.SetValid(false);
      },
      this);
  scene_desk->AddSceneButton(puzzle_piece);

  SceneButton *scene_desk_return_button = new SceneButton(
      448, 580, "down_arrow", "./res/down_arrow.png",
      [&, this](SceneButton &obj)
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
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_nightstand";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(bed);

  SceneButton *nightstand = new SceneButton(
      212, 408, "nightstand", "./res/scene2_nightstand.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_nightstand";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(nightstand);

  SceneButton *shelf = new SceneButton(
      300, 164, "shelf", "./res/scene2_shelf.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_shelf";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(shelf);

  SceneButton *waterpot = new SceneButton(
      418, 132, "waterpot", "./res/scene2_waterpot.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_shelf";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(waterpot);

  SceneButton *plant = new SceneButton(
      340, 148, "plant", "./res/scene2_plant.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1_shelf";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(plant);

  SceneButton *paint = new SceneButton(
      636, 100, "paint", "./res/scene2_paint_state1.png",
      [&, this](SceneButton &obj)
      {
        if (obj.GetState() == "default" && inhand == "knife")
        {
          Use("knife");
          obj.StateChange("blood");
        }
        else if (obj.GetState() == "blood" && inhand == "waterpot")
        {
          Use("waterpot");
          Item waterpot_filled_with_blood(1, 1, "Filled with blood.");
          AddItem("waterpot_filled_with_blood", waterpot_filled_with_blood);
        }
        else if (obj.GetState() == "default")
        {
          ShowDescription(obj.GetDescription());
        }
        else if (obj.GetState() == "blood")
        {
          ShowDescription("Strange and pathetic now.");
        }
      },
      this, "A strange paint.Seems to be alive.");
  paint->AddState("blood", "./res/scene2_paint_state2.png");
  scene1->AddSceneButton(paint);

  SceneButton *left = new SceneButton(
      10, 340, "left", "./res/left_arrow.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "right", "./res/right_arrow.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene2";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene1->AddSceneButton(right);

  Scene *scene1_shelf = new Scene("./res/bgp_scene2_shelf.png", "");
  AddScene("scene1_shelf", scene1_shelf);

  SceneButton *puzzle_piece1 = new SceneButton(
      652, 280, "puzzle_piece", "./res/scene3_mirror_puzzle_piece.png",
      [&, this](SceneButton &obj)
      {
        Item puzzle_piece(9, 1, "Piece.");
        AddItem("puzzle_piece", puzzle_piece);
        obj.SetValid(false);
      },
      this);
  scene1_shelf->AddSceneButton(puzzle_piece1);

  SceneButton *scene1_shelf_waterpot = new SceneButton(
      448, 162, "waterpot", "./res/scene2_shelf_waterpot.png",
      [waterpot, this](SceneButton &obj)
      {
        Item item_waterpot(1, 1, "It's empty.");
        AddItem("waterpot", item_waterpot);
        obj.SetValid(false);
        SetValid("scene1", "waterpot", false);
      },
      this);
  scene1_shelf->AddSceneButton(scene1_shelf_waterpot);

  SceneButton *scene1_shelf_plant = new SceneButton(
      196, 212, "plant", "./res/scene2_shelf_plant.png",
      [&, this](SceneButton &obj)
      {
        if (obj.GetState() == "default" && inhand == "dirt")
        {
          Use("dirt");
          obj.StateChange("dirt");
        }
        else if (obj.GetState() == "default" && inhand != "dirt")
        {
          ShowDescription("Need some dirt.");
        }
        else if (obj.GetState() == "dirt" && inhand == "finger")
        {
          Use("finger");
          obj.StateChange("finger");
        }
        else if (obj.GetState() == "finger" && inhand == "waterpot_filled_with_blood")
        {
          Use("waterpot_filled_with_blood");
          SetVisible("scene1_shelf", "hand", true);
          obj.StateChange("dirt_hand");
        }
      },
      this);
  scene1_shelf_plant->AddState("dirt", "./res/scene2_shelf_plant_dirt.png");
  scene1_shelf_plant->AddState("dirt_hand", "./res/scene2_shelf_plant_dirt.png");
  scene1_shelf_plant->AddState("finger", "./res/scene2_shelf_plant_finger.png");
  scene1_shelf->AddSceneButton(scene1_shelf_plant);

  SceneButton *scene1_shelf_hand = new SceneButton(
      204, 172, "hand", "./res/scene2_shelf_plant_hand.png",
      [&, this](SceneButton &obj)
      {
        if (obj.GetState() == "handle")
        {
          Item item_handle(1, 1, "A handle.");
          AddItem("handle", item_handle);
          obj.StateChange("default");
        }
      },
      this);
  scene1_shelf_hand->AddState("handle", "./res/scene2_shelf_plant_hand_handle.png");
  scene1_shelf_hand->StateChange("handle");
  scene1_shelf_hand->SetVisible(false);
  scene1_shelf->AddSceneButton(scene1_shelf_hand);

  SceneButton *scene1_shelf_return_button = new SceneButton(
      448, 580, "down_arrow", "./res/down_arrow.png",
      [&, this](SceneButton &obj)
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
      [](SceneButton &obj) {
      },
      this);
  scene1_nightstand->AddSceneButton(scene1_nightstand_bed);

  SceneButton *scene1_nightstand_knife = new SceneButton(
      376, 384, "nightstand_knife", "./res/scene2_nightstand_knife.png",
      [&, this](SceneButton &obj)
      {
        Item item_knife(1, 2, "It's so sharp it looks like it can cut into another world.");
        AddItem("knife", item_knife);
        obj.SetValid(false);
      },
      this);
  scene1_nightstand_knife->SetVisible(false);
  scene1_nightstand->AddSceneButton(scene1_nightstand_knife);

  SceneButton *puzzle_piece = new SceneButton(
      604, 448, "puzzle_piece", "./res/puzzle_piece.png",
      [&, this](SceneButton &obj)
      {
        Item puzzle_piece(9, 1, "Piece.");
        AddItem("puzzle_piece", puzzle_piece);
        obj.SetValid(false);
      },
      this);
  puzzle_piece->SetVisible(false);
  scene1_nightstand->AddSceneButton(puzzle_piece);

  SceneButton *scene1_nightstand_draw2 = new SceneButton(
      326, 440, "nightstand_draw2", "./res/scene2_nightstand_draw2_close.png",
      [&, this](SceneButton &obj)
      {
        if (obj.GetState() == "default")
        {
          obj.StateChange("open");
          SetVisible("scene1_nightstand", "puzzle_piece", true);
        }
        else if (obj.GetState() == "open")
        {
          SetVisible("scene1_nightstand", "puzzle_piece", false);
          obj.StateChange("default");
        }
      },
      this);
  scene1_nightstand_draw2->AddState("open", "./res/scene2_nightstand_draw2.png");
  scene1_nightstand->AddSceneButton(scene1_nightstand_draw2);
  puzzle_piece->Raise();

  SceneButton *scene1_nightstand_draw1 = new SceneButton(
      326, 312, "nightstand_draw1", "./res/scene2_nightstand_draw1_close.png",
      [&, this](SceneButton &obj)
      {
        if (obj.GetState() == "default")
        {
          obj.StateChange("open");
          SetVisible("scene1_nightstand", "nightstand_knife", true);
        }
        else if (obj.GetState() == "open")
        {
          SetVisible("scene1_nightstand", "nightstand_knife", false);
          obj.StateChange("default");
        }
      },
      this);
  scene1_nightstand_draw1->AddState("open", "./res/scene2_nightstand_draw1.png");
  scene1_nightstand->AddSceneButton(scene1_nightstand_draw1);

  scene1_nightstand_knife->Raise();

  SceneButton *scene1_nightstand_key = new SceneButton(
      56, 364, "nightstand_key", "./res/scene2_nightstand_key.png",
      [&, this](SceneButton &obj)
      {
        Item item_key(1, 1, "Now I need a keyhole.");
        AddItem("key", item_key);
        obj.SetValid(false);
      },
      this);
  scene1_nightstand->AddSceneButton(scene1_nightstand_key);

  SceneButton *scene1_nightstand_pillow = new SceneButton(
      6, 336, "nightstand_pillow", "./res/scene2_nightstand_pillow.png",
      [this](SceneButton &obj)
      {
        if (!obj.IsMoved())
        {
          obj.GetButton()->move(6, 100);
          obj.GetLabel()->move(6, 100);
        }
        else
        {
          obj.LocationReset();
        }
      },
      this);
  scene1_nightstand->AddSceneButton(scene1_nightstand_pillow);

  SceneButton *scene1_nightstand_return_button = new SceneButton(
      448, 580, "down_arrow", "./res/down_arrow.png",
      [&, this](SceneButton &obj)
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

  SceneButton *bookshelf = new SceneButton(
      32, 184, "bookshelf", "./res/scene3_bookshelf.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene2_bookshelf";
        Scenes[nowScene]->SceneShow();
      },
      this);
  bookshelf->AddState("right_half", "./res/scene3_bookshelf_open_right_half.png");
  bookshelf->AddState("left_half", "./res/scene3_bookshelf_open_left_half.png");
  bookshelf->AddState("open", "./res/scene3_bookshelf_open.png");
  scene2->AddSceneButton(bookshelf);

  SceneButton *mirror = new SceneButton(
      640, 192, "mirror", "./res/scene3_mirror.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene2_mirror";
        Scenes[nowScene]->SceneShow();
      },
      this);
  mirror->AddState("broken", "./res/scene3_mirror_broken.png");
  scene2->AddSceneButton(mirror);

  Scene *scene3_mirror_mirror = new Scene("./res/scene3_mirror_mirror.png", "");
  AddScene("scene2_mirror", scene3_mirror_mirror);

  SceneButton *puzzle_piece = new SceneButton(
      620, 580, "puzzle_piece", "./res/scene3_mirror_puzzle_piece.png",
      [&, this](SceneButton &obj)
      {
        Item puzzle_piece(9, 1, "Piece.");
        AddItem("puzzle_piece", puzzle_piece);
        obj.SetValid(false);
      },
      this);
  scene3_mirror_mirror->AddSceneButton(puzzle_piece);

  SceneButton *scene3_mirror_mirror_hand = new SceneButton(
      620, 472, "hand", "./res/scene3_mirror_mirror_hand.png",
      [&, this](SceneButton &obj)
      {
        ShowDescription(obj.GetDescription());
      },
      this, "I don't want to hurt myself.");
  scene3_mirror_mirror->AddSceneButton(scene3_mirror_mirror_hand);

  scene3_mirror_mirror_hand->SetVisible(false);

  SceneButton *scene3_mirror_mirror_mirror = new SceneButton(
      256, 38, "scene3_mirror_mirror_well", "./res/scene3_mirror_mirror_well.png",
      [&, mirror, scene3_mirror_mirror_hand, this](SceneButton &obj)
      {
        if (obj.GetState() == "default")
        {
          SetVisible("scene2_mirror", "hand", true);
          obj.StateChange("well_hand");
        }
        else if (obj.GetState() == "well_hand" && inhand == "knife")
        {
          Use("knife");
          Item item_finger(1, 1, "I'm so glad it's not mine.");
          AddItem("finger", item_finger);
          mirror->StateChange("broken");
          obj.StateChange("broken_hand");
        }
        else if (obj.GetState() == "well_hand")
        {
          SetVisible("scene2_mirror", "hand", false);
          obj.StateChange("default");
        }
        else if (obj.GetState() == "broken_hand")
        {
          SetVisible("scene2_mirror", "hand", false);
          obj.StateChange("broken");
        }
        else if (obj.GetState() == "broken")
        {
          ShowDescription(obj.GetDescription());
        }
      },
      this, "It's broken now.");
  scene3_mirror_mirror_mirror->AddState("well_hand", "./res/scene3_mirror_mirror_well_with_hand.png");
  scene3_mirror_mirror_mirror->AddState("broken_hand", "./res/scene3_mirror_mirror_broken_with_hand.png");
  scene3_mirror_mirror_mirror->AddState("broken", "./res/scene3_mirror_mirror_broken.png");
  scene3_mirror_mirror->AddSceneButton(scene3_mirror_mirror_mirror);

  scene3_mirror_mirror_hand->Raise();

  SceneButton *scene3_mirror_mirror_return_button = new SceneButton(
      448, 580, "down_arrow", "./res/down_arrow.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene2";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene3_mirror_mirror->AddSceneButton(scene3_mirror_mirror_return_button);

  Scene *scene2_bookshelf_paper = new Scene("./res/scene3_bookshelf_bookshelf_paper.png", "");
  AddScene("scene2_bookshelf_paper", scene2_bookshelf_paper);

  Scene *scene3_bookshelf_bookshelf = new Scene("./res/scene3_bookshelf_bookshelf.png", "");
  AddScene("scene2_bookshelf", scene3_bookshelf_bookshelf);

  SceneButton *scene3_bookshelf_bookshelf_paper_return_button = new SceneButton(
      448, 580, "down_arrow", "./res/down_arrow.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene2_bookshelf";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene2_bookshelf_paper->AddSceneButton(scene3_bookshelf_bookshelf_paper_return_button);

  SceneButton *scene3_bookshelf_bookshelf_key = new SceneButton(
      321, 438, "scene3_bookshelf_bookshelf_key", "./res/key_blue.png",
      [&, this](SceneButton &obj)
      {
        Item item_key(1, 1, "A blue key.");
        AddItem("key_blue", item_key);
        obj.SetValid(false);
      },
      this);
  scene3_bookshelf_bookshelf->AddSceneButton(scene3_bookshelf_bookshelf_key);

  SceneButton *scene3_bookshelf_bookshelf_puzzle_piece = new SceneButton(
      421, 388, "scene3_bookshelf_bookshelf_puzzle_piece", "./res/puzzle_piece.png",
      [&, this](SceneButton &obj)
      {
        Item puzzle_piece(9, 1, "Piece.");
        AddItem("puzzle_piece", puzzle_piece);
        obj.SetValid(false);
      },
      this);
  scene3_bookshelf_bookshelf->AddSceneButton(scene3_bookshelf_bookshelf_puzzle_piece);

  SceneButton *scene3_bookshelf_bookshelf_paper = new SceneButton(
      760, 324, "scene3_bookshelf_bookshelf_paper", "./res/scene3_bookshelf_bookshelf_paper_item.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene2_bookshelf_paper";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene3_bookshelf_bookshelf->AddSceneButton(scene3_bookshelf_bookshelf_paper);

  SceneButton *scene3_bookshelf_bookshelf_dirt = new SceneButton(
      552, 324, "scene3_bookshelf_bookshelf_dirt", "./res/scene3_bookshelf_bookshelf_dirt.png",
      [&, this](SceneButton &obj)
      {
        Item item_dirt(1, 1, "A bag of dirt.");
        AddItem("dirt", item_dirt);
        obj.SetValid(false);
      },
      this);
  scene3_bookshelf_bookshelf->AddSceneButton(scene3_bookshelf_bookshelf_dirt);

  SceneButton *scene3_bookshelf_bookshelf_board = new SceneButton(
      97, 88, "scene3_bookshelf_bookshelf_board", "./res/scene3_bookshelf_bookshelf_board.png",
      [&, this](SceneButton &obj)
      {
        if (CheckState("scene2_bookshelf", "lock_1", "6") &&
            CheckState("scene2_bookshelf", "lock_2", "2") &&
            CheckState("scene2_bookshelf", "lock_3", "1") &&
            CheckState("scene2_bookshelf", "lock_4", "4") &&
            CheckState("scene2_bookshelf", "lock_5", "3"))
        {
          SetValid("scene2_bookshelf", "lock_1", false);
          SetValid("scene2_bookshelf", "lock_2", false);
          SetValid("scene2_bookshelf", "lock_3", false);
          SetValid("scene2_bookshelf", "lock_4", false);
          SetValid("scene2_bookshelf", "lock_5", false);
          obj.SetValid(false);
          if (CheckState("scene2", "bookshelf", "default"))
          {
            SetState("scene2", "bookshelf", "left_half");
          }
          else if (CheckState("scene2", "bookshelf", "right_half"))
          {
            SetState("scene2", "bookshelf", "open");
          }
          ShowDescription("It's open!");
        }
      },
      this);
  scene3_bookshelf_bookshelf->AddSceneButton(scene3_bookshelf_bookshelf_board);

  SceneButton *scene3_bookshelf_bookshelf_board_1 = new SceneButton(
      521, 88, "scene3_bookshelf_bookshelf_board_1", "./res/scene3_bookshelf_bookshelf_board_1.png",
      [&, this](SceneButton &obj)
      {
        if (inhand == "key")
        {
          obj.SetValid(false);
          Use("key");
          if (CheckState("scene2", "bookshelf", "default"))
          {
            SetState("scene2", "bookshelf", "right_half");
          }
          else if (CheckState("scene2", "bookshelf", "left_half"))
          {
            SetState("scene2", "bookshelf", "open");
          }
        }
      },
      this);
  scene3_bookshelf_bookshelf->AddSceneButton(scene3_bookshelf_bookshelf_board_1);

  SceneButton *lock_1 = new SceneButton(
      292, 242, "lock_1", "./res/lock_0.png",
      [&, this](SceneButton &obj)
      {
        obj.NextState();
      },
      this);
  lock_1->AddState("1", "./res/lock_1.png");
  lock_1->AddState("2", "./res/lock_2.png");
  lock_1->AddState("3", "./res/lock_3.png");
  lock_1->AddState("4", "./res/lock_4.png");
  lock_1->AddState("5", "./res/lock_5.png");
  lock_1->AddState("6", "./res/lock_6.png");
  lock_1->AddState("7", "./res/lock_7.png");
  lock_1->AddState("8", "./res/lock_8.png");
  lock_1->AddState("9", "./res/lock_9.png");
  scene3_bookshelf_bookshelf->AddSceneButton(lock_1);

  SceneButton *lock_2 = new SceneButton(
      333, 242, "lock_2", "./res/lock_0.png",
      [&, this](SceneButton &obj)
      {
        obj.NextState();
      },
      this);
  lock_2->AddState("1", "./res/lock_1.png");
  lock_2->AddState("2", "./res/lock_2.png");
  lock_2->AddState("3", "./res/lock_3.png");
  lock_2->AddState("4", "./res/lock_4.png");
  lock_2->AddState("5", "./res/lock_5.png");
  lock_2->AddState("6", "./res/lock_6.png");
  lock_2->AddState("7", "./res/lock_7.png");
  lock_2->AddState("8", "./res/lock_8.png");
  lock_2->AddState("9", "./res/lock_9.png");
  scene3_bookshelf_bookshelf->AddSceneButton(lock_2);

  SceneButton *lock_3 = new SceneButton(
      374, 242, "lock_3", "./res/lock_0.png",
      [&, this](SceneButton &obj)
      {
        obj.NextState();
      },
      this);
  lock_3->AddState("1", "./res/lock_1.png");
  lock_3->AddState("2", "./res/lock_2.png");
  lock_3->AddState("3", "./res/lock_3.png");
  lock_3->AddState("4", "./res/lock_4.png");
  lock_3->AddState("5", "./res/lock_5.png");
  lock_3->AddState("6", "./res/lock_6.png");
  lock_3->AddState("7", "./res/lock_7.png");
  lock_3->AddState("8", "./res/lock_8.png");
  lock_3->AddState("9", "./res/lock_9.png");
  scene3_bookshelf_bookshelf->AddSceneButton(lock_3);

  SceneButton *lock_4 = new SceneButton(
      415, 242, "lock_4", "./res/lock_0.png",
      [&, this](SceneButton &obj)
      {
        obj.NextState();
      },
      this);
  lock_4->AddState("1", "./res/lock_1.png");
  lock_4->AddState("2", "./res/lock_2.png");
  lock_4->AddState("3", "./res/lock_3.png");
  lock_4->AddState("4", "./res/lock_4.png");
  lock_4->AddState("5", "./res/lock_5.png");
  lock_4->AddState("6", "./res/lock_6.png");
  lock_4->AddState("7", "./res/lock_7.png");
  lock_4->AddState("8", "./res/lock_8.png");
  lock_4->AddState("9", "./res/lock_9.png");
  scene3_bookshelf_bookshelf->AddSceneButton(lock_4);

  SceneButton *lock_5 = new SceneButton(
      456, 242, "lock_5", "./res/lock_0.png",
      [&, this](SceneButton &obj)
      {
        obj.NextState();
      },
      this);
  lock_5->AddState("1", "./res/lock_1.png");
  lock_5->AddState("2", "./res/lock_2.png");
  lock_5->AddState("3", "./res/lock_3.png");
  lock_5->AddState("4", "./res/lock_4.png");
  lock_5->AddState("5", "./res/lock_5.png");
  lock_5->AddState("6", "./res/lock_6.png");
  lock_5->AddState("7", "./res/lock_7.png");
  lock_5->AddState("8", "./res/lock_8.png");
  lock_5->AddState("9", "./res/lock_9.png");
  scene3_bookshelf_bookshelf->AddSceneButton(lock_5);

  SceneButton *scene3_bookshelf_bookshelf_return_button = new SceneButton(
      448, 580, "down_arrow", "./res/down_arrow.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene2";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene3_bookshelf_bookshelf->AddSceneButton(scene3_bookshelf_bookshelf_return_button);

  SceneButton *left = new SceneButton(
      10, 340, "left_arrow", "./res/left_arrow.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene1";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene2->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "right_arrow", "./res/right_arrow.png",
      [&, this](SceneButton &obj)
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

  Scene *scene4_door_door = new Scene("./res/scene4_door_door.png", "");
  AddScene("scene4_door", scene4_door_door);

  Scene *scene4_puzzle_puzzle = new Scene("./res/scene4_puzzle_puzzle.png", "");
  AddScene("scene4_puzzle", scene4_puzzle_puzzle);

  SceneButton *door = new SceneButton(
      332, 200, "bookshelf", "./res/scene4_door.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene4_door";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene3->AddSceneButton(door);

  SceneButton *puzzle = new SceneButton(
      100, 240, "puzzle", "./res/scene4_puzzle.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene4_puzzle·";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene3->AddSceneButton(puzzle);

  SceneButton *left = new SceneButton(
      10, 340, "left_arrow", "./res/left_arrow.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene2";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene3->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "right_arrow", "./res/right_arrow.png",
      [&, this](SceneButton &obj)
      {
        Scenes[nowScene]->SceneDisappear();
        nowScene = "scene";
        Scenes[nowScene]->SceneShow();
      },
      this);
  scene3->AddSceneButton(right);
}

void MainWindow::ToolbarRefresh()
{
  for (int i = 0; i < TOOLBAR_SIZE; i++)
  {
    std::string temp_name = "";
    std::string temp_path = "";
    std::string temp_description = "";
    if (page * 14 + i < bag.size())
    {
      auto it = bag.begin();
      advance(it, page * 14 + i);

      temp_name = (*it).first;
      temp_description = (*it).second.GetDescription();
      if (temp_name == inhand)
      {
      }
      temp_path = "./res/items/" + temp_name + ".png";
    }
    toolbar[i]->SetPath(temp_path);
    toolbar[i]->SetName(temp_name);
    toolbar[i]->SetDescription(temp_description);
  }
  repaint();
}

void MainWindow::ShowDescription(std::string descrip)
{
  if (descrip != "")
  {
    ui->label->setText(QString::fromStdString(descrip));
    ui->label->show();
    description_label_timer->start();
  }
}

void MainWindow::AddItem(std::string name, Item item)
{
  if (bag.find(name) != bag.end())
  {
    bag[name].Add();
  }
  else
  {
    bag[name] = item;
  }
  int res = bag[name].GetRemain();
  if (res > 0)
  {
    ShowDescription("There are " + std::to_string(res) + " left.");
  }
  ToolbarRefresh();
}

bool MainWindow::CheckState(std::string scene_name, std::string button_name, std::string state)
{
  if (Scenes.find(scene_name) != Scenes.end())
  {
    return Scenes[scene_name]->CheckState(button_name, state);
  }
  return false;
}

void MainWindow::SetState(std::string scene_name, std::string button_name, std::string state)
{
  if (Scenes.find(scene_name) != Scenes.end())
  {
    Scenes[scene_name]->SetState(button_name, state);
  }
}

void MainWindow::SetVisible(std::string scene_name, std::string button_name, bool state)
{
  if (Scenes.find(scene_name) != Scenes.end())
  {
    Scenes[scene_name]->SetVisible(button_name, state);
  }
}

void MainWindow::SetValid(std::string scene_name, std::string button_name, bool state)
{
  if (Scenes.find(scene_name) != Scenes.end())
  {
    Scenes[scene_name]->SetValid(button_name, state);
  }
}