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

void Scene::AddSceneButton(SceneButton *s)
{
  this->scene_buttons.push_back(s);
  s->GetButton()->setVisible(sceneVisable);
  s->GetLabel()->setVisible(sceneVisable);
}

void Scene::SceneDisappear()
{
  sceneVisable = 0;
  for (int i = 0; i < scene_buttons.size(); i++)
  {
    scene_buttons[i]->GetButton()->setVisible(0);
    scene_buttons[i]->GetLabel()->setVisible(0);
  }
}

void Scene::SceneShow()
{
  sceneVisable = 1;
  for (int i = 0; i < scene_buttons.size(); i++)
  {
    scene_buttons[i]->GetButton()->setVisible(1);
    scene_buttons[i]->GetLabel()->setVisible(1);
  }
}