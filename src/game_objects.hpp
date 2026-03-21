#ifndef GAME_OBJECTS_HPP
#define GAME_OBJECTS_HPP

#include "img_rects.hpp"


#define MAX_DIALOG_INDICIES 100

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

enum Dialog_names{ //do something like "NAME" "DIALOG_PHASE", such as VILLAGE_QUESTGIVER_1_STORY_TEXT
    VILLAGE_QUESTGIVER_1_STORY_TEXT,
    VILLAGE_QUESTGIVER_1_FOUND_ITEM_TEXT,
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
    DUNGEON_KEY,

};

enum Entity_names{ //stuff for identification - suprisingly helpful!
    DEFAULT,
    START_PORTAL,
    BIG_TREE,
    VILLAGE_WINDMILL,
    START_BULLDOZER,
    BIG_TREE_LEVEL_2_TREE_TRUNK,
    BIG_TREE_LEVEL_3_TREE_TRUNK,
    BIG_TREE_LEVEL_4_TREE_TRUNK,
    BIG_TREE_LEVEL_5_TREE_TRUNK,
    BIG_TREE_LEVEL_6_TREE_TRUNK,
    BIG_TREE_LEVEL_8_TREE_TRUNK,
    BIG_TREE_LEVEL_9_TREE_TRUNK,
    THE_REGROWN,
    FOREST_SCOURGE,
    VILLAGE_QUESTGIVER_1
};




enum Ground_item_names{
    BIG_TREE_LEVEL_1_STICK,
    BIG_TREE_LEVEL_2_KEY,
    BIG_TREE_LEVEL_5_KEY,

};

enum Locked_door_names{
    BIG_TREE_LEVEL_2_TO_BIG_TREE_LEVEL_3_LOCK,
    BIG_TREE_LEVEL_6_TO_BIG_TREE_LEVEL_7_LOCK
};

enum Dialog_effects{
    NONE,
    SHAKE,
    RECOLOR,
    FADE,
};

enum class SFX {
    TEST_SOUND,
    PLAYER_SWING_SWORD,
    PLAYER_FOOTSTEPS,
    DAMAGE_PLAYER,
    INV_CURSOR_PICKUP,
    INV_CURSOR_SELECT,
    UNLOCK_DOOR,
    PICKUP_ITEM,
    THE_REGROWN_FALL,
    THE_REGROWN_GROUND_ATTACK,
    THE_REGROWN_ARM_ATTACK,
    THE_REGROWN_DIE,
    GLOB_SWING_SWORD,
};

enum class Music_names{ //put the names of the music or the names of the maps here
    DARK_FOREST,
};

enum Facing
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

enum Game_states{ //add endings and other menu things
    START_MENU,
    SAVE_SLOTS,
    CREDITS,
    ACHIEVEMENTS,
    OPTIONS,
    GAMEPLAY,
    DIED,
    END_QUESTED,
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

struct Dialog_chunk{
    std::string text;
    Dialog_effects effect;
};

struct Melee_weapon_item
{
    int damage;
    double speed;
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



struct Locked_rect{
    
    Rectangle rect;
    Locked_door_names name;
};



struct VFX{ // put vfx things here
    float shake_time = 0.0f;
    float shake_duration = 0.0f;
    float shake_magnitude = 0.0f;
    float hitstop_time = 0.0f;
    float hitstop_duration = 0.0f;
};

struct Textbox_dat{
    int dialog_index_state = 0;
    int dialog_max_indecies = 0;
    int current_dialog_character = 0;
    bool is_textbox_open;
    Entity_names current_speaker;
    Dialog_chunk current_dialog[MAX_DIALOG_INDICIES];
};


// Player-focused stuff




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
    Ground_item_names ground_item_name;
};

class Entity
{
public:
    Entity_names name;
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

struct Game_save{
    Vector2 player_posSV;
    Map_names current_mapSV;
    std::vector<Ground_item_names> picked_up_itemsSV;
    std::vector<Locked_door_names> unlocked_doorsSV;
    std::vector<Entity_names> defeated_entitiesSV;
    std::vector<Dialog_names> finished_dialogSV;
    Inventory_slot inventory_slotsSV[28];
    int player_dungeon_keysSV;
    float player_current_healthSV;
    float player_max_healthSV;
    int player_move_modeSV;
};


struct GUI_data{
    Font global_font;
    
    Inventory_cursor inv_cursor;
    std::vector<Dialog_names> finished_dialog;
    Vector2 hotbar_pos;
    bool is_inv_open;
    Textbox_dat global_textbox;
    Item inv_cursor_held_item;
    Vector2 textbox_pos;
    bool start_menu_unloaded;
    Vector2 start_menu_logo_pos;
    Vector2 start_menu_enimation_pos;
    Vector2 start_menu_options_pos;
    Vector2 start_menu_select_right_pos;
    Vector2 start_menu_select_offset;
    Vector2 start_menu_select_left_pos;
    Vector2 start_menu_save_selecter_pos;
    int start_menu_sel_mode;
    
};



struct Game_data{
    std::vector<Load_rects> map_load_rects;
    Texture2D map_to_load;
    std::vector<Rectangle> collision_rects;
    std::vector<Locked_rect> locked_rects;
    Map_names current_map;
    Map_names requested_map;
    Vector2 requested_player_pos;
    Texture2D broken_tile_tex;
    Texture2D door_lock_tex;
    std::vector<Vector2> broken_floor_tiles;
    std::vector<Ground_item> ground_items;
    float fade_frame_timer;
    Music current_music;
    std::vector<std::unique_ptr<Entity>> entities;
    Game_states state;
    int save_slot;
    int new_scale;
    Vector2 wanted_cam_pos;
    // Game_save start_save_index[3];//???
};

// #pragma pack(push, 1)
struct Config_dat
{
    float scale;

    int KEY_CONTROLS_UP;
    int KEY_CONTROLS_DOWN;
    int KEY_CONTROLS_RIGHT;
    int KEY_CONTROLS_LEFT;

    int KEY_ITEM_HOTBAR_1;
    int KEY_ITEM_HOTBAR_2;
    int KEY_ITEM_HOTBAR_3;

    int KEY_OPEN_INVENTORY;
    int KEY_INTERACT;
    int KEY_SPEEDUP;
    int KEY_SAVE;
};
// #pragma pack(pop)

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

    int speed;
    double current_stamina;
    double max_stamina;
    bool reloading_stamina;
    int stamina_reload_timer;

    bool can_take_damage = true;
    float iframe_timer = 0.0f;
    Rectangle attack_hitbox;
    int active_damage;

    std::vector<Ground_item_names> picked_up_items;
    std::vector<Locked_door_names> unlocked_doors;
    std::vector<Entity_names> defeated_entities;
    int dungeon_keys = 0;
    
    Facing facing;
    
};


extern std::unordered_map<SFX, Sound> sound_effects;
extern std::unordered_map<Music_names, Music> music_names;
// extern std::unordered_map<Item_names, Item> items; //maybe later

//globally define items here
extern Item Stick;
extern Item Sacred_bark;
extern Item Dungeon_key;
extern Ground_item Big_tree_level_1_stick;
extern Ground_item Big_tree_level_2_key;
extern Ground_item Big_tree_level_5_key; 


#endif
