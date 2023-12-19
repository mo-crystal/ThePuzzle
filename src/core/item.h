#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <map>
#include <iostream>

#define DEFAULT_MAX_STACK 64

class Construct;

class Item
{
private:
  int ID = -1;
  std::string name = "";
  std::string path = "";

public:
  Item();
  Item(int _ID, std::string _name, int _maxStack, std::string _path, std::map<int, int> tmp_recipe, double _durability = -1.0, double buildingtime = 0);
  ~Item();
  int GetID() { return this->ID; }
  std::string GetName() { return this->name; }
  bool operator==(const Item &other) { return (this->ID == other.ID && this->name == other.name); }
  bool IsValid() { return ID >= 0; }
  std::string GetPath() { return this->path; }
};
#endif