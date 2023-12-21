#ifndef SCENE_BUTTON_H
#define SCENE_BUTTON_H

#include <iostream>
#include <functional>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QMovie>
#include <QMessageBox>

class SceneButton
{
private:
  double x, y;
  double size_x, size_y;
  std::string path = "";
  std::function<void()> onClick;
  QPushButton *button;
  QLabel *label;
  QMovie *movie;

public:
  SceneButton(double _x, double _y, double _size_x, double _size_y, std::string _path, std::function<void()> _onClick, QWidget *parent);
  SceneButton(double _x, double _y, std::string _path, std::function<void()> _onClick, QWidget *parent);
  ~SceneButton();
  std::string GetPath() { return this->path; }
  std::function<void()> GetOnClickFunction() const { return onClick; }
  QPushButton *GetButton() { return button; }
  QLabel *GetLabel() { return label; }
};

#endif