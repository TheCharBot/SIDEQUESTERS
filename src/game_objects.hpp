#ifndef GAME_OBJECTS_HPP
#define GAME_OBJECTS_HPP

#include "config.hpp"

// structs, classes, etc for the game, not any data, just data structures

// map globals

// also items
enum direction{
    DOWN_RIGHT,
    UP_RIGHT,
    DOWN_LEFT,
    UP_LEFT
};

enum Map_names
{
    WRONG_MAP,
    START_MAP,
    VILLAGE_MAP,
    INSIDE_VILLAGE_HOUSE_1,
    INSIDE_VILLAGE_HOUSE_2,
    INSIDE_VILLAGE_WINDMILL,
    INSIDE_VILLAGE_HOUSE_3,
    INSIDE_VILLAGE_HOUSE_4,
    INSIDE_VILLAGE_HOUSE_5,
    INSIDE_VILLAGE_HOUSE_6,
    INSIDE_VILLAGE_HOUSE_7,
    DARK_FOREST_NORTH,
    DARK_FOREST_SOUTH,
    DARK_FOREST_CENTER,

};

enum Item_types
{

    COMBAT_MELEE,
    COMBAT_RANGED,
    SHEILD,
    QUEST_ITEM,
    CONSUMABLE,
    DUNGEON
};

enum Buff_types
{
    CURRENCY,
    HEAL,

};

enum Item_names
{

    STICK,
    WEAK_BOW,
    WEAK_SWORD,
    SACRED_BARK,

};

// figure out good way to document quests
enum Quests
{
    SACRED_BARK_FROM_DARK_FOREST,

};

// Map-focused stuff
struct Load_rects
{
    Rectangle rect;
    int map_to_load_struct;
    Vector2 spawnpoint;
};

struct Melee_weapon_item
{
    int damage;
    double speed;
    Rectangle hitbox;
};

struct Range_weapon_item
{
    int damage;
    double speed;
    double range;
    Rectangle hitbox;

    Rectangle projectile_img_rect;
};

struct Consumable
{
    Buff_types buff_type;
    int buff_strength;
    Rectangle img_rect;
};

struct Quest_item
{

    Quests quest;
};

struct Dungeon_item
{
};

struct Item
{
    Item_names name;
    Rectangle img_rect;
    Item_types type;
    union
    {
        Melee_weapon_item melee;
        Range_weapon_item ranged;
        Consumable consumable;
        Quest_item quest_requirement;
    };
};

// Player-focused stuff
struct Player
{
    Vector2 pos;
    Vector2 movement;
    Rectangle *current_anim_arr;
    Rectangle normal_hitbox;
    int pos_x_save;
    int pos_y_save;
    int move_mode;
    int max_animation_frames;
    int current_animation_frame;
    int animation_frame_5;
    Texture2D tex;
    double health = 3;
};

struct Inventory_slot
{
    Vector2 pos;
    int amount_in_slot;
    std::optional<Item> filled_with;
};

struct Inventory_cursor
{
    int inv_slot_index;
    std::optional<Item> held_item;
    int current_anim_frame;
    int max_anim_frames;
    int anim_frame_5;
};

class Entity
{
public:

    Vector2 pos{};
    Rectangle img_rect;
    Rectangle rect;
    int max_animation_frames;
    int current_animation_frame;
    int animation_frame_5;
    int move_mode;

    bool dead = false;
    virtual ~Entity() = default;
    // load for loading texture data, dont load in constructor
    virtual void load() {}
    virtual void update() {};
    virtual void draw() {};
};

class Interactable_element : public Entity
{
public:
    Vector2 pos{};
    Rectangle img_rect;
    Rectangle rect;
    int max_animation_frames;
    int current_animation_frame;
    int animation_frame_5;

    virtual ~Interactable_element() = default;
    // load for loading texture data, dont load in constructor
    virtual void load() {}
    virtual void update() = 0;
    virtual void draw() = 0;
};

#endif
