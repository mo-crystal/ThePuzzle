#include "scene_button.h"

SceneButton::SceneButton(double _x, double _y, double _size_x, double _size_y, std::string _name, std::string _path, std::function<void(SceneButton &)> _onClick, QWidget *parent, std::string descrip, bool visible)
    : QWidget(parent)
{
  this->x = _x;
  this->y = _y;
  this->size_x = _size_x;
  this->size_y = _size_y;
  this->name = _name;
  this->path = _path;
  this->onClick = _onClick;
  this->description = descrip;
  QPixmap p(QString::fromStdString(path));
  label = new QLabel(parent);
  button = new QPushButton(parent);
  this->init_visible = visible;

  movie = new QMovie(QString::fromStdString(path));
  label->setMovie(movie);

  AddState("default", _path);

  QString background_image = "image: url(" + QString::fromStdString(path) + ");";
  QString style_sheet = "background-color: rgba(255, 255, 255, 0);";
  label->setAttribute(Qt::WA_TranslucentBackground);
  label->setFixedSize(size_x, size_y);
  label->move(x, y);

  button->setStyleSheet(style_sheet);
  button->setFixedSize(size_x, size_y);
  button->move(x, y);
  button->setCursor(Qt::PointingHandCursor);
  // 连接动画的帧改变信号，当动画播放到结尾时
  QObject::connect(movie, &QMovie::frameChanged, [this](int frameNumber)
                   {
    if (frameNumber == movie->frameCount()-1) {
      
    } });
  // 连接按钮的 clicked() 信号与 onClick 槽函数
  QObject::connect(button, &QPushButton::clicked, this, [this]()
                   { emit clicked(*this); });
  QObject::connect(this, &SceneButton::clicked, onClick);
  movie->start();

  SetVisible(init_visible);
}

SceneButton::SceneButton(double _x, double _y, std::string _name, std::string _path, std::function<void(SceneButton &)> _onClick, QWidget *parent, std::string descrip, bool visible)
    : QWidget(parent)
{
  this->x = _x;
  this->y = _y;
  this->path = _path;
  this->onClick = _onClick;
  this->name = _name;
  this->description = descrip;
  this->init_visible = visible;

  QPixmap p(QString::fromStdString(path));

  this->size_x = p.width();
  this->size_y = p.height();
  label = new QLabel(parent);
  button = new QPushButton(parent);
  AddState("default", _path);
  movie = new QMovie(QString::fromStdString(path));
  label->setMovie(movie);

  QString background_image = "image: url(" + QString::fromStdString(path) + ");";
  QString style_sheet = "background-color: rgba(255, 255, 255, 0);";
  label->setAttribute(Qt::WA_TranslucentBackground);
  label->setFixedSize(p.width(), p.height());
  label->move(x, y);

  button->setStyleSheet(style_sheet);
  button->setFixedSize(p.width(), p.height());
  button->move(x, y);
  button->setCursor(Qt::PointingHandCursor);
  // 连接动画的帧改变信号，当动画播放到结尾时
  QObject::connect(movie, &QMovie::frameChanged, [this](int frameNumber)
                   {
    if (frameNumber == movie->frameCount()-1) {
      
    } });
  // 连接按钮的 clicked() 信号与 onClick 槽函数
  QObject::connect(button, &QPushButton::clicked, this, [this]()
                   { emit clicked(*this); });
  QObject::connect(this, &SceneButton::clicked, onClick);
  movie->start();
  SetVisible(init_visible);
}

SceneButton::~SceneButton()
{
  delete button;
  delete label;
  delete movie;
}

void SceneButton::LocationReset()
{
  label->move(x, y);
  button->move(x, y);
}

void SceneButton::SetVisible(bool s)
{
  visible = s;
  if (!s)
  {
    button->hide();
    label->hide();
  }
  else if (s && valid)
  {
    button->show();
    label->show();
  }
}

void SceneButton::SetPath(std::string _path)
{
  path = _path;
  delete movie;
  QPixmap p(QString::fromStdString(path));

  movie = new QMovie(QString::fromStdString(path));
  label->setMovie(movie);

  QString background_image = "image: url(" + QString::fromStdString(path) + ");";
  QString style_sheet = "background-color: rgba(255, 255, 255, 0);";
  label->setAttribute(Qt::WA_TranslucentBackground);
  label->setFixedSize(p.width(), p.height());
  label->move(x, y);

  button->setStyleSheet(style_sheet);

  movie->start();
}

void SceneButton::SetValid(bool s)
{
  valid = s;
  if (!s)
  {
    button->hide();
    label->hide();
  }
}

void SceneButton::NextState()
{
  auto it = states.find(nowstate);
  it++;
  if (it == states.end())
  {
    it = states.begin();
  }
  StateChange((*it).first);
}

void SceneButton::ResetAll()
{
  SetVisible(init_visible);
  LocationReset();
  SetValid(true);
  StateChange(init_state);
}

void SceneButton::SetInitVisible(bool state)
{
  init_visible = state;
  SetVisible(state);
}

void SceneButton::SetInitState(std::string state)
{
  init_state = state;
  StateChange(state);
}