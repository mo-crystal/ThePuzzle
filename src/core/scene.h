#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>

#include "scene_button.h"

class Scene
{
private:
  std::string path_bgp = "";
  std::string path_bgm = "";
  std::vector<SceneButton *> scene_buttons;

public:
  Scene(std::string path_p, std::string path_m);
  ~Scene();
  void AddSceneButton(SceneButton *s);
};

#endif