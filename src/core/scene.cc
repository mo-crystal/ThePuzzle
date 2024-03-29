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
    if (scene_buttons[i]->IsValid() && scene_buttons[i]->IsVisible())
    {
      scene_buttons[i]->GetButton()->setVisible(1);
      scene_buttons[i]->GetLabel()->setVisible(1);
    }
  }
}

bool Scene::CheckState(std::string name, std::string state)
{
  for (int i = 0; i < scene_buttons.size(); i++)
  {
    if (scene_buttons[i]->GetName() == name)
    {
      return scene_buttons[i]->GetState() == state;
    }
  }
  return false;
}

void Scene::SetState(std::string name, std::string state)
{
  for (int i = 0; i < scene_buttons.size(); i++)
  {
    if (scene_buttons[i]->GetName() == name)
    {
      scene_buttons[i]->StateChange(state);
    }
  }
}

void Scene::SetVisible(std::string name, bool state)
{
  for (int i = 0; i < scene_buttons.size(); i++)
  {
    if (scene_buttons[i]->GetName() == name)
    {
      scene_buttons[i]->SetVisible(state);
    }
  }
}

void Scene::SetValid(std::string name, bool state)
{
  for (int i = 0; i < scene_buttons.size(); i++)
  {
    if (scene_buttons[i]->GetName() == name)
    {
      scene_buttons[i]->SetValid(state);
    }
  }
}

void Scene::Reset()
{
  for (int i = 0; i < scene_buttons.size(); i++)
  {
    scene_buttons[i]->ResetAll();
  }
}