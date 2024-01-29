#include "item.h"

Item::Item() {}

Item::Item(int _need, int _durability, std::string _description)
{
  this->need = _need;
  this->description = _description;
  this->durability = _durability;
}

Item::~Item()
{
}

int Item::Use()
{
  if (need == now)
  {
    this->durability -= 1;
    if (durability <= 0)
    {
      return EMPTY;
    }
    return DONE;
  }
  else
  {
    return NOTENOUGH;
  }
}

void Item::Add()
{
  this->now++;
}