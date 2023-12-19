#include "animation.h"
Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::AddState(std::string state_name, std::vector<std::string> paths)
{
  if (this->state.find(state_name) == this->state.end())
  {
    this->state.insert(std::pair<std::string, std::vector<std::string>>(state_name, paths));
    if (this->nowState == "")
    {
      this->nowFrame = 0;
      this->nowState = state_name;
    }
  }
}

void Animation::AddState(std::string state_name, std::string path, int start, int end)
{
  if (this->state.find(state_name) == this->state.end())
  {
    std::vector<std::string> result;
    for (int i = start; i <= end; i++)
    {
      std::string replaced = path;
      size_t pos = replaced.find("%%");
      while (pos != std::string::npos)
      {
        replaced.replace(pos, 2, std::to_string(i));
        pos = replaced.find("%%", pos + 1);
      }
      result.push_back(replaced);
    }
    this->state.insert(std::pair<std::string, std::vector<std::string>>(state_name, result));
    if (this->nowState == "")
    {
      this->nowFrame = 0;
      this->nowState = state_name;
    }
  }
}

void Animation::NextFrame()
{
  if (this->state.find(nowState) != this->state.end())
  {
    this->nowFrame = (this->nowFrame + 1) % state[this->nowState].size();
  }
}

void Animation::SetState(std::string _state)
{
  if (this->state.find(_state) != this->state.end())
  {
    if (this->nowState == _state)
    {
      return;
    }
    this->nowFrame = 0;
    this->nowState = _state;
  }
}