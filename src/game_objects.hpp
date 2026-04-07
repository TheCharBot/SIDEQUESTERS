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
    NPC_DAN_VILLAGE_STORY_TEXT,
    NPC_DAN_VILLAGE_FOUND_ITEM_TEXT,
    NPC_BOB_STORY_TEXT,
    NPC_CLARENCE_STORY_TEXT,
    NPC_CHAD_STORY_TEXT,
    NPC_FALLEN_HERO_STORY_TEXT,
};

enum Item_types
{

    COMBAT_MELEE,
    COMBAT_RANGED,
    SHIELD,
    QUEST_ITEM,
    CONSUMABLE,
    DUNGEON
};

enum Buff_types
{
    CURRENCY,
    HEAL,

};

enum class Item_names
{

    STICK,
    WEAK_BOW,
    WEAK_SWORD,
    SACRED_BARK,
    DUNGEON_KEY,
    RED_BERRIES,

};

enum Entity_names{ //stuff for identification - suprisingly helpful!
    //world entity names
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
    VILLAGE_WINDMILL_GRINDER,
    BERRY_BUSH,
    GROUND_POT,
    //hostile entity names
    THE_REGROWN,
    FOREST_SCOURGE,
    //NPC entity names
    NPC_DAN_VILLAGE,
    NPC_BOB_VILLAGE,
    NPC_CLARENCE_VILLAGE,
    NPC_CHAD_VILLAGE,
    NPC_FALLEN_HERO_VILLAGE,
};




enum Ground_item_names{
    BIG_TREE_LEVEL_1_STICK,
    BIG_TREE_LEVEL_2_KEY,
    BIG_TREE_LEVEL_5_KEY,
    BERRY_BUSH_DROP,

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

enum class SFX_ids {
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





enum Game_states{ //add endings and other menu things
    START_MENU,
    SAVE_SLOTS,
    CREDITS,
    ACHIEVEMENTS,
    OPTIONS,
    GAMEPLAY,
    PLAYER_GAME_OVER,
    END_QUESTED,
};


// figure out good way to document quests - this works for now though
enum Quest_names
{
    SACRED_BARK_FROM_DARK_FOREST,

};

// Map-focused stuff
struct Load_rects
{
    Rectangle rect = {};
    int map_to_load_struct = 0;
    Vector2 spawnpoint = {};
};

struct Dialog_chunk{
    std::string text = {};
    Dialog_effects effect = {};
};

struct Melee_weapon_item
{
    int damage = 0;
    double speed = 0;
};

struct Range_weapon_item
{
    int damage = 0;
    double speed = 0;
    double range = 0;
    Rectangle hitbox = {};

    Rectangle projectile_img_rect = {};
};

struct Consumable_item
{
    Buff_types buff_type = {};
    float buff_strength = 0;
    int amount = 0;
};


struct Dungeon_item
{
};

struct Custom_item_function{
    void func(){};
};

struct Item
{
    Item_names name = {};
    Rectangle img_rect = {};
    Item_types type = {};
    
    Melee_weapon_item melee;
    Range_weapon_item ranged;
    Consumable_item consumable;
    Quest_names quest;
    Custom_item_function custom_func;
    
};



struct Locked_rect{
    
    Rectangle rect = {};
    Locked_door_names name = {};
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
    bool is_textbox_open = false;
    Entity_names current_speaker = {};
    Dialog_chunk current_dialog[MAX_DIALOG_INDICIES];
};


// Player-focused stuff




struct Inventory_slot
{
    Vector2 pos = {};
    int amount_in_slot = 0;
    std::optional<Item> filled_with = {};
};

struct Inventory_cursor
{
    int inv_slot_index = 0;
    std::optional<Item> held_item = {};
    int current_anim_frame = 0;
    int max_anim_frames = 0;
    int anim_frame_5 = 0;
};

struct Ground_item{
    Vector2 pos = {};
    Rectangle rect = {};
    Item item = {};
    bool picked_up = false;
    Ground_item_names ground_item_name = {};
};

class Entity
{
public:
    Entity_names name = {};
    Vector2 pos = {};
    Rectangle img_rect = {};
    Rectangle rect = {};
    Rectangle *current_anim_arr = {};
    int max_animation_frames = 0;
    int current_animation_frame = 0;
    int animation_frame_5 = 0;
    int move_mode = 0;

    bool dead = false;
    virtual ~Entity() = default;
    // load for loading texture data, dont load in constructor
    virtual void load() {}
    virtual void update() {};
    virtual void draw() {};
    
};

struct Game_save{
    Vector2 player_posSV = {};
    Map_names current_mapSV = {};
    std::vector<Ground_item_names> picked_up_itemsSV = {};
    std::vector<Locked_door_names> unlocked_doorsSV = {};
    std::vector<Entity_names> defeated_entitiesSV = {};
    std::vector<Dialog_names> finished_dialogSV = {};
    Inventory_slot inventory_slotsSV[28] = {};
    int player_dungeon_keysSV = 0;
    float player_current_healthSV = 0;
    float player_max_healthSV = 0;
    int player_move_modeSV = 0;
};


struct GUI_data{
    Font global_font = {};
    
    Inventory_cursor inv_cursor = {};
    std::vector<Dialog_names> finished_dialog = {};
    Vector2 hotbar_pos = {};
    bool is_inv_open = 0;
    Textbox_dat global_textbox = {};
    Item inv_cursor_held_item = {};
    Vector2 textbox_pos = {};
    bool start_menu_unloaded = 0;
    Vector2 start_menu_logo_pos = {};
    Vector2 start_menu_enimation_pos = {};
    Vector2 start_menu_options_pos = {};
    Vector2 start_menu_select_right_pos = {};
    Vector2 start_menu_select_offset = {};
    Vector2 start_menu_select_left_pos = {};
    Vector2 start_menu_save_selecter_pos = {};
    int start_menu_sel_mode = 0;
    
};



struct Game_data{
    std::vector<Load_rects> map_load_rects = {};
    Texture2D map_to_load = {};
    std::vector<Rectangle> collision_rects = {};
    std::vector<Locked_rect> locked_rects = {};
    Map_names current_map = {};
    Map_names requested_map = {};
    Vector2 requested_player_pos = {};
    Texture2D broken_tile_tex = {};
    Texture2D door_lock_tex = {};
    std::vector<Vector2> broken_floor_tiles = {};
    std::vector<Ground_item> ground_items = {};
    float fade_frame_timer = 0;
    Music current_music = {};
    std::vector<std::unique_ptr<Entity>> entities = {};
    Game_states state = {};
    int save_slot = 0;
    int new_scale = 0;
    std::unordered_map<std::string, Texture2D> texture_cache = {};
    std::unordered_map<SFX_ids, Sound> sfx_manager = {};
    std::unordered_map<Item_names, Item> item_ids = {};
    std::unordered_map<Ground_item_names, Ground_item> ground_item_ids = {};
    // Game_save start_save_index[3];//???
};

// #pragma pack(push, 1)
struct Config_dat
{
    float scale = 0;

    int KEY_CONTROLS_UP = 0;
    int KEY_CONTROLS_DOWN = 0;
    int KEY_CONTROLS_RIGHT = 0;
    int KEY_CONTROLS_LEFT = 0;

    int KEY_ITEM_HOTBAR_1 = 0;
    int KEY_ITEM_HOTBAR_2 = 0;
    int KEY_ITEM_HOTBAR_3 = 0;

    int KEY_OPEN_INVENTORY = 0;
    int KEY_INTERACT = 0;
    int KEY_SPEEDUP = 0;
    int KEY_SAVE = 0;

    int KEY_SPRINT = 0;
};
// #pragma pack(pop)

struct Player
{
    Vector2 pos = {};
    Vector2 pos_save = {};
    Vector2 movement = {};
    Rectangle *current_anim_arr = {};
    Rectangle collision_rect = {};
    Rectangle hitbox = {};

    
    int move_mode = 0;
    int max_animation_frames = 0;
    int current_animation_frame = 0;
    int animation_frame_5 = 0;

    Texture2D tex = {};

    float current_health = 0;
    float max_health = 0;

    int speed = 0;
    double current_stamina = 0;
    double max_stamina = 0;
    bool reloading_stamina = 0;
    int stamina_reload_timer = 0;

    bool can_take_damage = true;
    float iframe_timer = 0.0f;
    Rectangle active_attack_hitbox = {};
    int active_damage = 0;

    std::vector<Ground_item_names> picked_up_items = {};
    std::vector<Locked_door_names> unlocked_doors = {};
    std::vector<Entity_names> defeated_entities = {};
    int dungeon_keys = 0;
    
    Facing facing = {};

    
    float knockback_time = 0;
    Vector2 knockback_vel = {};

    enum Behavior_mode{
        IDLE,
        WALKING,
        SPRINTING,
        USING_ITEM,
    };

    Behavior_mode behavior_mode = IDLE;
    
};

extern Game_data game;
extern GUI_data gui;
extern Player player;



//then entity classes







// extern std::unordered_map<Tex_ids, Texture2D> tex_manager;

// extern std::unordered_map<Item_names, Item> item_ids; //maybe later

//globally define items here




#endif
