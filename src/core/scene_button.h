#ifndef SCENE_BUTTON_H
#define SCENE_BUTTON_H

#include <iostream>
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

signals:
  void clicked(SceneButton &);
};

#endif