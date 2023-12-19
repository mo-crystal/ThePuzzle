#include "item.h"

Item::Item()
{
}

Item::Item(int _ID, std::string _name, int _maxStack, std::string _path, std::map<int, int> tmp_recipe, double _durability, double buildingtime)
{
  this->ID = _ID;
  this->name = _name;
  this->path = _path;
}

Item::~Item()
{
}

