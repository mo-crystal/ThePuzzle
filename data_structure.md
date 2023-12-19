箱子问题

## Basic

**abstract::static_obj** 地图上的静态物体，例如树、房子 ok

```
int id;
bool destroyable;
block* location;
std::string name;
std::vector<image*> pic; // image 暂定
std::map<int, int> contain; // contain[x] = y, x 为 item.id, y 为 该物品掉落的数量
```

**abstract::chest** ok

```
std::map<int, int> chest; // 箱子，用法同上
int check_size; // 为 0 则不是 chest
```

**abstract::creature** ok

```
int id;
double x, y;
std::string name;
std::map<std::string, std::vector<image*>> action;
int max_health;
int now_health;
```

**abstract::item** 可拾取物品 ok

```
int id;
std::string name;
image* pic;
int max_count;
```

## World

**block** 一个方格 ok

```
long x, y; // 坐标
static_obj* contain;
chunk* location;
int abundance;
```

**chunk0** 一个区块，= 16*16 blocks ok

```
long x, y;
block* contain[16][16];
unsigned char r, g, b;
int owner; // player id
bool is_foundation;
```

**chunki(i 1~4)**

```
long x, y;
chunk(i-1)* contain[16][16];
unsigned char r, g, b;
```

## Game Obj

**tree: static_obj** 树，可以破坏 ok

```
int max_health;
int now_health;
```

**stone: static_obj** 石头，可以破坏

```
int max_health;
int now_health;
```

**miner: static_obj** 矿机，可以破坏，是箱子，容量 8 格

```
int max_health;
int now_health;
int mine_type;
```

**foundation: static_obj** 基地，不可破坏，是箱子，容量为 128

**tree_farm: static_obj** 林场，种树用，可以破坏，是箱子，容量 8 格

**foundation_bp: item** ok

```
id: 1
```

**stone: item**

```
id: 2
```

**wood: item**

```
id: 3
```

**iron: item**

```
id: 4
```

**miner_bp: item**

```
id: 5
```

**tree_farm_bp: item**

```
id: 6
```

## Player

**player: creature**

```
int uid;
std::string username;
int coin;
```
