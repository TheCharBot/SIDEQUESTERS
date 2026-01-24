#ifndef GAME_OBJECTS_HPP
#define GAME_OBJECTS_HPP

#include "config.hpp"

// structs, classes, etc for the game, not any data, just data structures

// map globals

// also items
enum Direction{
    DOWN_RIGHT,
    UP_RIGHT,
    DOWN_LEFT,
    UP_LEFT
};

enum Wander_directions{
    UP_DOWN,
    LEFT_RIGHT,
    RANDOM
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
    BIG_TREE_LEVEL_1,
    BIG_TREE_LEVEL_2,
    BIG_TREE_LEVEL_3,
    BIG_TREE_LEVEL_4,
    BIG_TREE_LEVEL_5,
    BIG_TREE_LEVEL_6,
    BIG_TREE_LEVEL_7,
    BIG_TREE_LEVEL_8,
    BIG_TREE_LEVEL_9,
    BIG_TREE_LEVEL_10,

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

// figure out good way to document quests - this works for now though
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
        Quests quest;
    };
};

struct Boss_keys{ // add bosses to this to change which ones have been defeated or not
    bool the_regrown_defeated = false;
};

struct VFX{ // put vfx things here
    float shake_time = 0.0f;
    float shake_duration = 0.0f;
    float shake_magnitude = 0.0f;
    float hitstop_time = 0.0f;
    float hitstop_duration = 0.0f;
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
    float current_health;
    float max_health;
    bool can_take_damage = true;
    float iframe_timer = 0.0f;
    Rectangle attack_hitbox;
    int active_damage;
    Boss_keys defeated_bosses;

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

struct Ground_item{
    Vector2 pos{};
    Rectangle rect;
    Item item;
    bool picked_up = false;
    Rectangle interact_range;
    bool can_be_picked_up = false;
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
extern Item Stick;
extern Item Sacred_bark;


#endif
