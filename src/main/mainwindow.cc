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
  playlist->addMedia(QUrl::fromLocalFile(""));
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
    frame = new QPixmap(QString::fromStdString(""));
    p_tool = new QPixmap("");
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
      temp_path = ""//"./res/items/" + temp_name + ".png";
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
      temp_path = ""//"./res/items/" + temp_name + ".png";
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
    playlist->clear();
    playlist->addMedia(QUrl::fromLocalFile(path));
    mediaPlayer->setPlaylist(playlist);
    mediaPlayer->play();
  }
}

void MainWindow::Reset()
{
  for (auto i = Scenes.begin(); i != Scenes.end(); i++)
  {
    (*i).second->Reset();
    (*i).second->SceneDisappear();
  }

  bag.clear();
  ToolbarRefresh();
}
