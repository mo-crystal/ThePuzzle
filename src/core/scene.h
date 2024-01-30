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
  bool sceneVisable = 0;

public:
  Scene(std::string path_p, std::string path_m);
  ~Scene();
  void AddSceneButton(SceneButton *s);
  std::string GetSceneBGP() { return this->path_bgp; }
  void SceneDisappear();
  void SceneShow();
  bool CheckState(std::string name, std::string state);
  void SetState(std::string name, std::string state);
  void SetVisible(std::string name, bool state);
  void SetValid(std::string name, bool state);
};

#endif