#include "scene_button.h"

SceneButton::SceneButton(double _x, double _y, double _size_x, double _size_y, std::string _path, std::function<void()> _onClick, QWidget *parent)
{
  this->x = _x;
  this->y = _y;
  this->size_x = _size_x;
  this->size_y = _size_y;
  this->path = _path;
  this->onClick = _onClick;
  QPixmap p(QString::fromStdString(path));
  label = new QLabel(parent);
  button = new QPushButton(parent);

  movie = new QMovie(QString::fromStdString(path));
  label->setMovie(movie);

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
  QObject::connect(button, &QPushButton::clicked, onClick);
  movie->start();
}

SceneButton::SceneButton(double _x, double _y, std::string _path, std::function<void()> _onClick, QWidget *parent)
{
  this->x = _x;
  this->y = _y;
  this->path = _path;
  this->onClick = _onClick;
  QPixmap p(QString::fromStdString(path));

  this->size_x = p.width();
  this->size_y = p.height();
  label = new QLabel(parent);
  button = new QPushButton(parent);

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
  QObject::connect(button, &QPushButton::clicked, onClick);
  movie->start();
}

SceneButton::~SceneButton()
{
  delete button;
  delete label;
  delete movie;
}
