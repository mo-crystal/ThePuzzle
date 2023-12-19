#ifndef SCENE_BUTTON_H
#define SCENE_BUTTON_H

#include <iostream>

class SceneButton
{
private:
  double x, y;
  std::string path = "";

public:
  SceneButton(double _x, double _y, std::string _path);
  ~SceneButton();
  std::string GetPath() { return this->path; }
};

#endif