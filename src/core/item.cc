#include "item.h"

Item::Item()
{
}

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
      return 1;
    }
    return 0;
  }
  else
  {
    return -1;
  }
}