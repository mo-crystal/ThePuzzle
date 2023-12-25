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
  std::function<void()> onClick;
  QPushButton *button;
  QLabel *label;
  QMovie *movie;

public:
  explicit SceneButton(
      double _x, double _y, double _size_x, double _size_y, std::string _name, std::string _path, std::function<void()> _onClick, QWidget *parent = nullptr, std::function<void()> _ondefine = []() {});
  explicit SceneButton(
      double _x, double _y, std::string _name, std::string _path, std::function<void()> _onClick, QWidget *parent = nullptr, std::function<void()> _ondefine = []() {});
  ~SceneButton();
  std::string GetName() { return this->name; }
  std::string GetPath() { return this->path; }
  float GetX(){return x;}
  float GetY(){return y;}
  std::function<void()> GetOnClickFunction() const { return onClick; }
  QPushButton *GetButton() { return button; }
  QLabel *GetLabel() { return label; }


};

#endif