#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <map>
#include <iostream>

#define NOTENOUGH -1
#define EMPTY 0
#define DONE 1

#define DEFAULT_MAX_STACK 64


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
  int Getnow() { return this->now; }
  int GetRemain() { return this->need - this->now >= 0 ? this->need - this->now : 0; }
  std::string GetDescription() { return this->description; }
  int Use();
  void Add();
};
#endif