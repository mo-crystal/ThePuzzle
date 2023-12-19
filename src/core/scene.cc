#include "scene.h"

Scene::Scene(std::string path_p, std::string path_m)
{
  this->path_bgp = path_p;
  this->path_bgm = path_m;
}

Scene::~Scene()
{
  for (int i = 0; i < scene_buttons.size(); i++)
  {
    delete scene_buttons[i];
  }
  
}

void Scene::AddSceneButton(SceneButton* s){
  this->scene_buttons.push_back(s);
}