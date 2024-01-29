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
  int durability = 1;
  int need = 1;
  int now = 1;
  std::string description = "";

public:
  Item();
  Item(int _need, int _durability, std::string _description);
  ~Item();
  int GetDurability() { return this->durability; }
  std::string GetDescription() { return this->description; }
  int Use();
};
#endif