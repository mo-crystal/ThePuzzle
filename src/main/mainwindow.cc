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
  ShowToolbar(toolbarVisible);
  mediaPlayer = new QMediaPlayer(this);
  playlist = new QMediaPlaylist;
  mediaPlayer->setPlaylist(playlist);
  mediaPlayer->setVolume(50);
  playlist->addMedia(QUrl::fromLocalFile("./res/music/bgm.mp3"));
  playlist->setPlaybackMode(QMediaPlaylist::Loop);
  mediaPlayer->play();
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
  delete mediaPlayer;
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
  painter.drawPixmap(0, 0, p->width(), p->height(), *p);
  if (toolbarVisible)
  {
    QPixmap *frame, *p_tool;
    frame = new QPixmap(QString::fromStdString("./res/items/selectframe.png"));
    p_tool = new QPixmap("./res/toolbar.png");
    painter.drawPixmap(0, DEFUALT_HEIGHT, DEFUALT_WIDTH, DEFUALT_HEIGHT_TOOLBAR, *p_tool);
    for (int i = 0; i < TOOLBAR_SIZE; i++)
    {
      if (toolbar[i]->GetName() == inhand && inhand != "")
      {
        painter.drawPixmap(36 + i * (8 + 56), 644, 56, 56, *frame);
      }
    }
    delete frame;
    delete p_tool;
  }
  delete p;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
}

int MainWindow::Use(std::string item_name)
{
  if (bag.find(item_name) != bag.end())
  {
    int res = bag[item_name].Use();
    if (res == EMPTY)
    {
      bag.erase(item_name);
      ToolbarRefresh();
      return EMPTY;
    }
    else if (res == NOTENOUGH)
    {
      ShowDescription("I haven't found enough of this yet.");
      ToolbarRefresh();
      return NOTENOUGH;
    }
    ToolbarRefresh();
    return DONE;
  }
  ToolbarRefresh();
  return NOFOUND;
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
  Start();
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
    SceneChange(name);
  }
}

void MainWindow::Start()
{
  Scene *start = new Scene("./res/start.png", "");
  AddScene("start", start, 1);
  SceneButton *start_button = new SceneButton(
      360, 391, "start", "./res/startbutton.png",
      [&, this](SceneButton &obj)
      {
        ShowToolbar(true);
        SceneChange("scene");
      },
      this);
  start->AddSceneButton(start_button);
}

void MainWindow::Room1Init()
{
  Scene *scene = new Scene("./res/bgp_scene1.png", "./res/music/bgm.mp3");
  AddScene("scene", scene);

  SceneButton *s1_desk = new SceneButton(
      0, 360, "desk", "./res/scene1_desk.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene_desk");
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
        SceneChange("scene1_nightstand");
      },
      this);
  scene->AddSceneButton(s1_bed);

  SceneButton *s1_nightstand = new SceneButton(
      844, 508, "nightstand", "./res/scene1_nightstand.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene1_nightstand");
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
        SceneChange("scene3");
      },
      this);
  scene->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "right", "./res/right_arrow.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene1");
      },
      this);
  scene->AddSceneButton(right);

  Scene *scene_desk = new Scene("./res/bgp_scene1_desk.png", "./res/music/bgm.mp3");
  AddScene("scene_desk", scene_desk);

  SceneButton *puzzle_piece = new SceneButton(
      652, 420, "puzzle_piece", "./res/puzzle_piece.png",
      [&, this](SceneButton &obj)
      {
        Item puzzle_piece(8, 1, "Piece.");
        AddItem("puzzle_piece", puzzle_piece);
        obj.SetValid(false);
      },
      this);
  scene_desk->AddSceneButton(puzzle_piece);

  SceneButton *puzzle_piece1 = new SceneButton(
      640, 128, "puzzle_piece1", "./res/puzzle_piece2.png",
      [&, this](SceneButton &obj)
      {
        Item puzzle_piece(8, 1, "Piece.");
        AddItem("puzzle_piece", puzzle_piece);
        obj.SetValid(false);
      },
      this);
  puzzle_piece1->SetVisible(false);
  scene_desk->AddSceneButton(puzzle_piece1);

  SceneButton *draw = new SceneButton(
      212, 116, "draw", "./res/bgp_scene1_desk_draw_close.png",
      [&, this](SceneButton &obj)
      {
        if (obj.GetState() == "default" && inhand == "key_blue")
        {
          Use("key_blue");
          obj.StateChange("unlock");
          ShowDescription("Unlocked!");
        }
        else if (obj.GetState() == "unlock")
        {
          obj.StateChange("open");
          SetVisible("scene_desk", "puzzle_piece1", true);
        }
        else if (obj.GetState() == "open")
        {
          obj.StateChange("unlock");
          SetVisible("scene_desk", "puzzle_piece1", false);
        }
      },
      this);
  draw->AddState("unlock", "./res/bgp_scene1_desk_draw_close.png");
  draw->AddState("open", "./res/bgp_scene1_desk_draw_open.png");
  scene_desk->AddSceneButton(draw);
  puzzle_piece1->Raise();

  SceneButton *scene_desk_return_button = new SceneButton(
      448, 580, "down_arrow", "./res/down_arrow.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene");
      },
      this);
  scene_desk->AddSceneButton(scene_desk_return_button);
}

void MainWindow::Room2Init()
{
  Scene *scene1 = new Scene("./res/scene2.png", "./res/music/bgm.mp3");
  AddScene("scene1", scene1);

  SceneButton *bed = new SceneButton(
      0, 360, "bed", "./res/scene2_bed.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene1_nightstand");
      },
      this);
  scene1->AddSceneButton(bed);

  SceneButton *nightstand = new SceneButton(
      212, 408, "nightstand", "./res/scene2_nightstand.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene1_nightstand");
      },
      this);
  scene1->AddSceneButton(nightstand);

  SceneButton *shelf = new SceneButton(
      300, 164, "shelf", "./res/scene2_shelf.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene1_shelf");
      },
      this);
  scene1->AddSceneButton(shelf);

  SceneButton *waterpot = new SceneButton(
      418, 132, "waterpot", "./res/scene2_waterpot.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene1_shelf");
      },
      this);
  scene1->AddSceneButton(waterpot);

  SceneButton *plant = new SceneButton(
      340, 148, "plant", "./res/scene2_plant.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene1_shelf");
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
        SceneChange("scene");
      },
      this);
  scene1->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "right", "./res/right_arrow.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene2");
      },
      this);
  scene1->AddSceneButton(right);

  Scene *scene1_shelf = new Scene("./res/bgp_scene2_shelf.png", "./res/music/bgm.mp3");
  AddScene("scene1_shelf", scene1_shelf);

  SceneButton *puzzle_piece1 = new SceneButton(
      652, 280, "puzzle_piece", "./res/scene3_mirror_puzzle_piece.png",
      [&, this](SceneButton &obj)
      {
        Item puzzle_piece(8, 1, "Piece.");
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
        SceneChange("scene1");
      },
      this);
  scene1_shelf->AddSceneButton(scene1_shelf_return_button);

  Scene *scene1_nightstand = new Scene("./res/bgp_scene2_nightstand.png", "./res/music/bgm.mp3");
  AddScene("scene1_nightstand", scene1_nightstand);

  SceneButton *nightstand_puzzle_piece = new SceneButton(
      112, 88, "nightstand_puzzle_piece", "./res/scene3_mirror_puzzle_piece.png",
      [&, this](SceneButton &obj)
      {
        Item puzzle_piece1(8, 1, "Piece.");
        AddItem("puzzle_piece", puzzle_piece1);
        obj.SetValid(false);
      },
      this);
  scene1_nightstand->AddSceneButton(nightstand_puzzle_piece);

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
        Item puzzle_piece(8, 1, "Piece.");
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
        SceneChange("scene1");
      },
      this);
  scene1_nightstand->AddSceneButton(scene1_nightstand_return_button);
}

void MainWindow::Room3Init()
{
  Scene *scene2 = new Scene("./res/bgp_blank.png", "./res/music/bgm.mp3");
  AddScene("scene2", scene2);

  SceneButton *puzzle_piece1 = new SceneButton(
      52, 172, "puzzle_piece1", "./res/scene3_mirror_puzzle_piece.png",
      [&, this](SceneButton &obj)
      {
        Item puzzle_piece(8, 1, "Piece.");
        AddItem("puzzle_piece", puzzle_piece);
        obj.SetValid(false);
      },
      this);
  scene2->AddSceneButton(puzzle_piece1);

  SceneButton *bookshelf = new SceneButton(
      32, 184, "bookshelf", "./res/scene3_bookshelf.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene2_bookshelf");
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
        SceneChange("scene2_mirror");
      },
      this);
  mirror->AddState("broken", "./res/scene3_mirror_broken.png");
  scene2->AddSceneButton(mirror);

  Scene *scene3_mirror_mirror = new Scene("./res/scene3_mirror_mirror.png", "./res/music/bgm.mp3");
  AddScene("scene2_mirror", scene3_mirror_mirror);

  SceneButton *puzzle_piece = new SceneButton(
      620, 580, "puzzle_piece", "./res/scene3_mirror_puzzle_piece.png",
      [&, this](SceneButton &obj)
      {
        Item puzzle_piece(8, 1, "Piece.");
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
        SceneChange("scene2");
      },
      this);
  scene3_mirror_mirror->AddSceneButton(scene3_mirror_mirror_return_button);

  Scene *scene2_bookshelf_paper = new Scene("./res/scene3_bookshelf_bookshelf_paper.png", "./res/music/bgm.mp3");
  AddScene("scene2_bookshelf_paper", scene2_bookshelf_paper);

  Scene *scene3_bookshelf_bookshelf = new Scene("./res/scene3_bookshelf_bookshelf.png", "./res/music/bgm.mp3");
  AddScene("scene2_bookshelf", scene3_bookshelf_bookshelf);

  SceneButton *scene3_bookshelf_bookshelf_paper_return_button = new SceneButton(
      448, 580, "down_arrow", "./res/down_arrow.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene2_bookshelf");
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
        Item puzzle_piece(8, 1, "Piece.");
        AddItem("puzzle_piece", puzzle_piece);
        obj.SetValid(false);
      },
      this);
  scene3_bookshelf_bookshelf->AddSceneButton(scene3_bookshelf_bookshelf_puzzle_piece);

  SceneButton *scene3_bookshelf_bookshelf_paper = new SceneButton(
      760, 324, "scene3_bookshelf_bookshelf_paper", "./res/scene3_bookshelf_bookshelf_paper_item.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene2_bookshelf_paper");
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
        SceneChange("scene2");
      },
      this);
  scene3_bookshelf_bookshelf->AddSceneButton(scene3_bookshelf_bookshelf_return_button);

  SceneButton *left = new SceneButton(
      10, 340, "left_arrow", "./res/left_arrow.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene1");
      },
      this);
  scene2->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "right_arrow", "./res/right_arrow.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene3");
      },
      this);
  scene2->AddSceneButton(right);
}

void MainWindow::Room4Init()
{
  Scene *scene3 = new Scene("./res/bgp_blank.png", "./res/music/bgm.mp3");
  AddScene("scene3", scene3);

  Scene *scene4_door_door = new Scene("./res/scene4_door_door.png", "");
  AddScene("scene4_door", scene4_door_door);

  Scene *scene4_puzzle_puzzle = new Scene("./res/scene4_puzzle_bgp.png", "./res/music/bgm.mp3");
  AddScene("scene4_puzzle", scene4_puzzle_puzzle);

  SceneButton *piece1 = new SceneButton(
      334, 174, "piece1", "./res/scene4_puzzle_piece_0.png",
      [&, this](SceneButton &obj)
      {
        if (puzzles["scene4_puzzle"][1]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece2", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][3]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece4", obj.GetState());
          obj.StateChange("default");
        }
      },
      this);
  scene4_puzzle_puzzle->AddSceneButton(piece1);

  SceneButton *piece2 = new SceneButton(
      432, 174, "piece2", "./res/scene4_puzzle_piece_0.png",
      [&, this](SceneButton &obj)
      {
        if (puzzles["scene4_puzzle"][0]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece1", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][2]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece3", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][4]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece5", obj.GetState());
          obj.StateChange("default");
        }
      },
      this);
  scene4_puzzle_puzzle->AddSceneButton(piece2);

  SceneButton *piece3 = new SceneButton(
      529, 174, "piece3", "./res/scene4_puzzle_piece_0.png",
      [&, this](SceneButton &obj)
      {
        if (puzzles["scene4_puzzle"][1]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece2", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][5]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece6", obj.GetState());
          obj.StateChange("default");
        }
      },
      this);
  scene4_puzzle_puzzle->AddSceneButton(piece3);

  SceneButton *piece4 = new SceneButton(
      334, 272, "piece4", "./res/scene4_puzzle_piece_0.png",
      [&, this](SceneButton &obj)
      {
        if (puzzles["scene4_puzzle"][0]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece1", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][6]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece7", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][4]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece5", obj.GetState());
          obj.StateChange("default");
        }
      },
      this);
  scene4_puzzle_puzzle->AddSceneButton(piece4);

  SceneButton *piece5 = new SceneButton(
      432, 272, "piece5", "./res/scene4_puzzle_piece_0.png",
      [&, this](SceneButton &obj)
      {
        if (puzzles["scene4_puzzle"][1]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece2", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][3]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece4", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][5]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece6", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][7]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece8", obj.GetState());
          obj.StateChange("default");
        }
      },
      this);
  scene4_puzzle_puzzle->AddSceneButton(piece5);

  SceneButton *piece6 = new SceneButton(
      529, 272, "piece6", "./res/scene4_puzzle_piece_0.png",
      [&, this](SceneButton &obj)
      {
        if (puzzles["scene4_puzzle"][2]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece3", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][4]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece5", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][8]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece9", obj.GetState());
          obj.StateChange("default");
        }
      },
      this);
  scene4_puzzle_puzzle->AddSceneButton(piece6);

  SceneButton *piece7 = new SceneButton(
      334, 369, "piece7", "./res/scene4_puzzle_piece_0.png",
      [&, this](SceneButton &obj)
      {
        if (puzzles["scene4_puzzle"][3]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece4", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][7]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece8", obj.GetState());
          obj.StateChange("default");
        }
      },
      this);
  scene4_puzzle_puzzle->AddSceneButton(piece7);

  SceneButton *piece8 = new SceneButton(
      432, 369, "piece8", "./res/scene4_puzzle_piece_0.png",
      [&, this](SceneButton &obj)
      {
        if (puzzles["scene4_puzzle"][4]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece5", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][6]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece7", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][8]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece9", obj.GetState());
          obj.StateChange("default");
        }
      },
      this);
  scene4_puzzle_puzzle->AddSceneButton(piece8);

  SceneButton *piece9 = new SceneButton(
      529, 369, "piece9", "./res/scene4_puzzle_piece_0.png",
      [&, this](SceneButton &obj)
      {
        if (puzzles["scene4_puzzle"][5]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece6", obj.GetState());
          obj.StateChange("default");
        }
        else if (puzzles["scene4_puzzle"][7]->GetState() == "default")
        {
          SetState("scene4_puzzle", "piece8", obj.GetState());
          obj.StateChange("default");
        }
      },
      this);
  scene4_puzzle_puzzle->AddSceneButton(piece9);

  puzzles["scene4_puzzle"].push_back(piece1);
  puzzles["scene4_puzzle"].push_back(piece2);
  puzzles["scene4_puzzle"].push_back(piece3);
  puzzles["scene4_puzzle"].push_back(piece4);
  puzzles["scene4_puzzle"].push_back(piece5);
  puzzles["scene4_puzzle"].push_back(piece6);
  puzzles["scene4_puzzle"].push_back(piece7);
  puzzles["scene4_puzzle"].push_back(piece8);
  puzzles["scene4_puzzle"].push_back(piece9);

  std::vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  std::random_shuffle(nums.begin(), nums.end());
  int inversions = 0;

  for (int i = 0; i < nums.size() - 1; ++i)
  {
    for (int j = i + 1; j < nums.size(); ++j)
    {
      if (nums[i] > nums[j])
      {
        inversions++;
      }
    }
  }

  if (inversions % 2 != 0)
  {
    std::swap(nums[nums.size() - 2], nums[nums.size() - 1]);
  }

  for (int i = 0; i < puzzles["scene4_puzzle"].size(); i++)
  {
    puzzles["scene4_puzzle"][i]->SetVisible(false);
    for (int j = 1; j <= 9; j++)
    {
      std::string path = "./res/scene4_puzzle_piece_" + std::to_string(j) + ".png";
      puzzles["scene4_puzzle"][i]->AddState(std::to_string(j), path);
    }
    puzzles["scene4_puzzle"][i]->StateChange(std::to_string(nums[i]));
  }

  SceneButton *puzzle_puzzle = new SceneButton(
      280, 120, "puzzle_puzzle", "./res/scene4_puzzle_bgp_puzzle.png",
      [&, this](SceneButton &obj)
      {
        if (obj.GetState() == "default" && inhand == "puzzle_piece" && Use("puzzle_piece") != NOTENOUGH)
        {
          SetState("scene3", "puzzle", "unfinished");
          SetVisible("scene4_puzzle", "piece1", true);
          SetVisible("scene4_puzzle", "piece2", true);
          SetVisible("scene4_puzzle", "piece3", true);
          SetVisible("scene4_puzzle", "piece4", true);
          SetVisible("scene4_puzzle", "piece5", true);
          SetVisible("scene4_puzzle", "piece6", true);
          SetVisible("scene4_puzzle", "piece7", true);
          SetVisible("scene4_puzzle", "piece8", true);
          SetVisible("scene4_puzzle", "piece9", true);
          obj.StateChange("start");
          SetState("scene3", "puzzlex", "find_all");
        }
        else if (obj.GetState() == "start")
        {
          for (int i = 0; i < puzzles["scene4_puzzle"].size() - 1; i++)
          {
            if (puzzles["scene4_puzzle"][i]->GetState() != std::to_string(i + 1))
            {
              return;
            }
          }
          if (puzzles["scene4_puzzle"][puzzles["scene4_puzzle"].size() - 1]->GetState() != "default")
          {
            return;
          }
          for (int i = 0; i < puzzles["scene4_puzzle"].size(); i++)
          {
            puzzles["scene4_puzzle"][i]->SetVisible(false);
          }
          obj.StateChange("finished");
          SetState("scene3", "puzzlex", "done");
          SetVisible("scene4_puzzle", "screwdriver", true);
          ShowDescription("Done!");
        }
      },
      this);
  puzzle_puzzle->AddState("start", "./res/scene4_puzzle_bgp_puzzle.png");
  puzzle_puzzle->AddState("finished", "./res/scene4_puzzle_bgp_puzzle_open.png");
  scene4_puzzle_puzzle->AddSceneButton(puzzle_puzzle);

  piece1->Raise();
  piece2->Raise();
  piece3->Raise();
  piece4->Raise();
  piece5->Raise();
  piece6->Raise();
  piece7->Raise();
  piece8->Raise();
  piece9->Raise();

  SceneButton *screwdriver = new SceneButton(
      432, 469, "screwdriver", "./res/scene4_puzzle_screwdriver.png",
      [&, this](SceneButton &obj)
      {
        Item item_screwdriver(1, 1, "A screwdriver.");
        AddItem("screwdriver", item_screwdriver);
        obj.SetValid(false);
      },
      this);
  screwdriver->SetVisible(false);
  scene4_puzzle_puzzle->AddSceneButton(screwdriver);

  SceneButton *scene_puzzle_return_button = new SceneButton(
      448, 580, "scene_puzzle_down_arrow", "./res/down_arrow.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene3");
      },
      this);
  scene4_puzzle_puzzle->AddSceneButton(scene_puzzle_return_button);

  SceneButton *door = new SceneButton(
      332, 200, "door", "./res/scene4_door.png",
      [&, this](SceneButton &obj)
      {
        if (obj.GetState() == "default" && inhand == "handle")
        {
          Use("handle");
          obj.StateChange("with_handle");
          ShowDescription("Still needs to be reinforced.");
        }
        else if (obj.GetState() == "default")
        {
          ShowDescription("The handle is missing.");
        }
        else if (obj.GetState() == "with_handle" && inhand == "screwdriver")
        {
          Use("screwdriver");
          obj.StateChange("with_handle_fixed");
          ShowDescription("Done.");
        }
        else if (obj.GetState() == "with_handle")
        {
          ShowDescription("Maybe I need a screwdriver.");
        }

        else if (obj.GetState() == "with_handle_fixed")
        {
          obj.StateChange("open");
        }
        else if (obj.GetState() == "open")
        {
          SceneChange("scene4_door");
        }
      },
      this);
  door->AddState("with_handle", "./res/scene4_door_with_handle.png");
  door->AddState("with_handle_fixed", "./res/scene4_door_with_handle.png");
  door->AddState("open", "./res/scene4_door_open.png");
  scene3->AddSceneButton(door);

  SceneButton *puzzle = new SceneButton(
      100, 240, "puzzlex", "./res/scene4_puzzle.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene4_puzzle");
      },
      this);
  puzzle->AddState("find_all", "./res/scene4_puzzle_unfinished.png");
  puzzle->AddState("done", "./res/scene4_puzzle_finished.png");
  scene3->AddSceneButton(puzzle);

  SceneButton *desk = new SceneButton(
      800, 340, "desk", "./res/scene3_desk.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene_desk");
      },
      this);

  scene3->AddSceneButton(desk);

  SceneButton *left = new SceneButton(
      10, 340, "left_arrow", "./res/left_arrow.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene2");
      },
      this);
  scene3->AddSceneButton(left);

  SceneButton *right = new SceneButton(
      900, 340, "right_arrow", "./res/right_arrow.png",
      [&, this](SceneButton &obj)
      {
        SceneChange("scene");
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

void MainWindow::ShowToolbar(bool state)
{
  toolbarVisible = state;
  for (int i = 0; i < toolbar.size(); i++)
  {
    toolbar[i]->SetVisible(state);
  }
}

void MainWindow::SceneChange(std::string scene_name)
{
  std::string bgm = "";
  if (Scenes.find(nowScene) != Scenes.end())
  {
    Scenes[nowScene]->SceneDisappear();
    bgm = Scenes[nowScene]->GetSceneBGM();
  }

  if (Scenes.find(scene_name) == Scenes.end())
  {
    return;
  }

  nowScene = scene_name;
  Scenes[nowScene]->SceneShow();
  if (Scenes[nowScene]->GetSceneBGM() != bgm)
  {
    QString path = QString::fromStdString(Scenes[nowScene]->GetSceneBGM());
    //QMessageBox::information(this,"",path);
    playlist->clear();
    playlist->addMedia(QUrl::fromLocalFile(path));
    mediaPlayer->setPlaylist(playlist);
    mediaPlayer->play();
  }
}