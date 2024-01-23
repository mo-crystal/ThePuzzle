#ifndef SCENE_BUTTON_H
#define SCENE_BUTTON_H

#include <iostream>
#include <map>
#include <functional>

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QMovie>
#include <QMessageBox>

class SceneButton : public QWidget
{
  Q_OBJECT

private:
  double x, y;
  double size_x, size_y;
  std::string path = "";
  std::string name = "";
  std::function<void(SceneButton &)> onClick;
  QPushButton *button;
  QLabel *label;
  QMovie *movie;
  bool valid = true;
  std::map<std::string, std::string> states;
  std::string nowstate = "default";

public:
  explicit SceneButton(
      double _x, double _y, double _size_x, double _size_y, std::string _name, std::string _path, std::function<void(SceneButton &)> _onClick, QWidget *parent);
  explicit SceneButton(
      double _x, double _y, std::string _name, std::string _path, std::function<void(SceneButton &)> _onClick, QWidget *parent);
  ~SceneButton();
  std::string GetName() { return this->name; }
  std::string GetPath() { return this->path; }
  void SetName(std::string _name) { name = _name; }
  void SetPath(std::string _path);
  float GetX() { return x; }
  float GetY() { return y; }
  std::function<void(SceneButton &)> GetOnClickFunction() const { return onClick; }
  QPushButton *GetButton() { return button; }
  QLabel *GetLabel() { return label; }
  void LocationReset();
  bool IsMoved() { return !(x == label->x() && y == label->y()); }
  bool IsValid() { return valid; }
  void SetValid(bool s);
  void AddState(std::string _name, std::string _path)
  {
    states[_name] = _path;
  }
  void StateChange(std::string state)
  {
    auto it = states.find(state);

    // 检查是否找到键
    if (it != states.end())
    {
      nowstate = state;
      movie = new QMovie(QString::fromStdString(states[state]));
      label->setMovie(movie);
      movie->start();
      QPixmap p(QString::fromStdString(states[state]));
      QString background_image = "image: url(" + QString::fromStdString(states[state]) + ");";
      QString style_sheet = "background-color: rgba(255, 255, 255, 0);";
      label->setAttribute(Qt::WA_TranslucentBackground);
      label->setFixedSize(p.width(), p.height());
      button->setStyleSheet(style_sheet);
      button->setFixedSize(p.width(), p.height());
    }
  }
  std::string GetState() { return nowstate; }
signals:
  void clicked(SceneButton &);
};

#endif