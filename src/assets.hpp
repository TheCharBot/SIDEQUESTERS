#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "config.hpp"

// Put sprite rects and other things here, paths, x defaults, etc

enum Map_names{
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

class Entity {
public:
    Vector2 pos{};
    Rectangle img_rect;
    Rectangle rect;
    int max_animation_frames;
    int current_animation_frame;
    int animation_frame_5;
    

    virtual ~Entity() = default;
    //load for loading texture data, dont load in constructor
    virtual void load() {}
    virtual void update() = 0;
    virtual void draw() = 0;
};

class Interactable_element : public Entity{
    public:
    Vector2 pos{};
    Rectangle img_rect;
    Rectangle rect;
    int max_animation_frames;
    int current_animation_frame;
    int animation_frame_5;
    
    

    virtual ~Interactable_element() = default;
    //load for loading texture data, dont load in constructor
    virtual void load() {}
    virtual void update() = 0;
    virtual void draw() = 0;
};
extern std::vector<std::unique_ptr<Entity>> entities;
// Map-focused stuff
struct Load_rects{
    Rectangle rect;
    int map_to_load_struct;
    Vector2 spawnpoint;
};


extern std::vector<Load_rects> map_load_rects;
extern Texture2D map_to_load;
extern std::vector<Rectangle> collision_rects;
extern int current_map;
extern Map_names requested_map;
extern Vector2 requested_player_pos;

#define MAP_1_RECT_1 {0, 0, 480, 135}
#define MAP_1_RECT_2 {0, 185, 198, 135}
#define MAP_1_RECT_3 {198, 265, 282, 55}
#define MAP_1_RECT_4 {282, 185, 198, 80}

#define MAP_2_RECT_1 {130, 0, 535, 65}
#define MAP_2_RECT_2 {666, 0, 134, 97}
#define MAP_2_RECT_3 {733, 97, 67, 543}
#define MAP_2_RECT_4 {336, 99, 112, 101}
#define MAP_2_RECT_5 {176, 259, 112, 101}
#define MAP_2_RECT_6 {496, 259, 112, 101}
#define MAP_2_RECT_7 {96, 451, 112, 101}
#define MAP_2_RECT_8 {256, 451, 112, 101}
#define MAP_2_RECT_9 {416, 451, 112, 101}
#define MAP_2_RECT_10 {576, 451, 112, 101}
#define MAP_2_RECT_11 {512, 114, 16, 13}
#define MAP_2_RECT_12 {560, 130, 16, 13}
#define MAP_2_RECT_13 {528, 146, 16, 13}
#define MAP_2_RECT_14 {592, 146, 16, 13}
#define MAP_2_RECT_15 {605, 77, 21, 20}
#define MAP_2_RECT_16 {449, 118, 15, 74}
#define MAP_2_RECT_17 {466, 145, 7, 41}
#define MAP_2_RECT_18 {418, 327, 13, 24}
#define MAP_2_RECT_19 {434, 311, 13, 24}
#define MAP_2_RECT_20 {450, 327, 13, 24}
#define MAP_2_RECT_21 {129, 96, 110, 44}

//Dark Forest North stuff
#define MAP_3_RECT_1 {32, 0, 928, 85}
#define MAP_3_RECT_2 {0, 85, 32, 300}
#define MAP_3_RECT_3 {112, 176, 818, 117}
#define MAP_3_RECT_4 {928, 293, 32, 300}
#define MAP_3_RECT_5 {33, 385, 815, 116}
#define MAP_3_RECT_6 {0, 501, 32, 139}
#define MAP_3_RECT_7 {112, 593, 816, 47}

//loader rects for other maps
//NAME the LOAD RECTS PLEASE!!!!!!!
#define MAP_2_DARK_FOREST_NORTH_LOAD {8, 105, 1, 62}
#define MAP_2_DARK_FOREST_SOUTH_LOAD {0, 629, 734, 1}
#define MAP_2_VILLAGE_HOUSE_1_LOAD {383, 201, 18, 1}
#define MAP_2_VILLAGE_HOUSE_2_LOAD {223, 361, 18, 1}
#define MAP_2_WINDMILL_LOAD {358, 352, 22, 1} // <-windmill here - load rect 5
#define MAP_2_VILLAGE_HOUSE_3_LOAD {543, 361, 18, 1}
#define MAP_2_VILLAGE_HOUSE_4_LOAD {143, 553, 18, 1}
#define MAP_2_VILLAGE_HOUSE_5_LOAD {303, 553, 18, 1}
#define MAP_2_VILLAGE_HOUSE_6_LOAD {463, 553, 18, 1}
#define MAP_2_VILLAGE_HOUSE_7_LOAD {623, 553, 18, 1}

//next time, do load points like this: in the format "destination spawnpoint from origin"
#define DARK_FOREST_NORTH_SPAWNPOINT_FROM_VILLAGE {925, 106}

//constant village house load rects for my sanity
#define VILLAGE_HOUSE_OUTSIDE_LOAD_RECT {136, 175, 16, 1}
#define PLAYER_VILLAGE_HOUSE_START_POS {134, 125}
#define VILLAGE_HOUSE_1_OUTSIDE_SPAWNPOINT {383, 167}
#define VILLAGE_HOUSE_2_OUTSIDE_SPAWNPOINT {223, 327}
#define VILLAGE_HOUSE_3_OUTSIDE_SPAWNPOINT {543, 327}
#define VILLAGE_HOUSE_4_OUTSIDE_SPAWNPOINT {143, 519}
#define VILLAGE_HOUSE_5_OUTSIDE_SPAWNPOINT {303, 519}
#define VILLAGE_HOUSE_6_OUTSIDE_SPAWNPOINT {463, 519}
#define VILLAGE_HOUSE_7_OUTSIDE_SPAWNPOINT {623, 519}
#define VILLAGE_WINDMILL_OUTSIDE_SPAWNPOINT {358, 319}

//wall rects for houses
#define VILLAGE_HOUSE_RECT_1 {56, 48, 176, 20}//wall
#define VILLAGE_HOUSE_RECT_2 {228, 68, 4, 88}//wall
#define VILLAGE_HOUSE_RECT_3 {56, 68, 4, 88}//wall
#define VILLAGE_HOUSE_RECT_4 {60, 156, 75, 20}//wall
#define VILLAGE_HOUSE_RECT_5 {153, 156, 75, 20}//wall

//village house 1 stuff
#define VILLAGE_HOUSE_1_RECT_6 {60, 68, 78, 37}
#define VILLAGE_HOUSE_1_RECT_7 {191, 68, 37, 45}

//village house 2 stuff (finish later, get other things done now)
//(leave blank for now)

//more dark forest north stuff
//actually, make load rects look like this, in the format of "origin to destination"
#define DARK_FOREST_NORTH_TO_VILLAGE {945, 87, 1, 89}
#define DARK_FOREST_NORTH_TO_CENTER {32, 639, 80, 1}
#define VILLAGE_SPAWNPOINT_FROM_DARK_FOREST_NORTH {18, 106}


//music stuff
extern Music current_music;


// Player-focused stuff
struct Player{
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
    int draw_order;
};

extern Player player;

#define PLAYER_SPRITE_WIDTH 32
#define PLAYER_SPRITE_HEIGHT 48
#define PLAYER_HITBOX_WIDTH 13
#define PLAYER_HITBOX_HEIGHT 10
#define PLAYER_HITBOX_X_OFFSET 6
#define PLAYER_HITBOX_Y_OFFSET 38
#define PLAYER_SPEED 2
#define PLAYER_START_MAP_POS_X 224
#define PLAYER_START_MAP_POS_Y 208
#define PLAYER_VILLAGE_MAP_POS_X 267
#define PLAYER_VILLAGE_MAP_POS_Y 128

//Player-focused image rect arrays
extern Rectangle player_idle_up_arr[1];
extern Rectangle player_idle_down_arr[1];
extern Rectangle player_idle_right_arr[1];
extern Rectangle player_idle_left_arr[1];
extern Rectangle player_walk_down[12];
extern Rectangle player_walk_up[12];
extern Rectangle player_walk_right[8];
extern Rectangle player_walk_left[8];
//Player-focused image rects

extern Rectangle player_idle_down;
extern Rectangle player_idle_up;
extern Rectangle player_idle_right;
extern Rectangle player_idle_left;
extern Rectangle player_walk_down_1;
extern Rectangle player_walk_down_2;
extern Rectangle player_walk_down_3;
extern Rectangle player_walk_down_4;
extern Rectangle player_walk_down_5;
extern Rectangle player_walk_down_6;
extern Rectangle player_walk_down_7;
extern Rectangle player_walk_down_8;
extern Rectangle player_walk_down_9;
extern Rectangle player_walk_down_10;
extern Rectangle player_walk_down_11;
extern Rectangle player_walk_down_12;
extern Rectangle player_walk_up_1;
extern Rectangle player_walk_up_2;
extern Rectangle player_walk_up_3;
extern Rectangle player_walk_up_4;
extern Rectangle player_walk_up_5;
extern Rectangle player_walk_up_6;
extern Rectangle player_walk_up_7;
extern Rectangle player_walk_up_8;
extern Rectangle player_walk_up_9;
extern Rectangle player_walk_up_10;
extern Rectangle player_walk_up_11;
extern Rectangle player_walk_up_12;
extern Rectangle player_walk_right_1;
extern Rectangle player_walk_right_2;
extern Rectangle player_walk_right_3;
extern Rectangle player_walk_right_4;
extern Rectangle player_walk_right_5;
extern Rectangle player_walk_right_6;
extern Rectangle player_walk_right_7;
extern Rectangle player_walk_right_8;
extern Rectangle player_walk_left_1;
extern Rectangle player_walk_left_2;
extern Rectangle player_walk_left_3;
extern Rectangle player_walk_left_4;
extern Rectangle player_walk_left_5;
extern Rectangle player_walk_left_6;
extern Rectangle player_walk_left_7;
extern Rectangle player_walk_left_8;

//start portal image and rects

#define START_PORTAL_X 224
#define START_PORTAL_Y 37
#define START_PORTAL_WIDTH 32
#define START_PORTAL_HEIGHT 44

extern Rectangle start_portal_animation[4];
extern Rectangle start_portal_1;
extern Rectangle start_portal_2;
extern Rectangle start_portal_3;
extern Rectangle start_portal_4;
extern Rectangle start_portal_emination;

//bulldozer image and rects

#define START_BULLDOZER_X 6
#define START_BULLDOZER_Y 110
#define START_BULLDOZER_WIDTH 99
#define START_BULLDOZER_HEIGHT 75
#define BULLDOZER_TRIGGER_Y 185
#define BULLDOZER_SPEED 5
#define MAX_BULLDOZER_X 190
#define BULLDOZER_CUTSCENE_TRIGGER_X 160

extern Rectangle start_bulldozer_animation[3];
extern Rectangle start_bulldozer_1;
extern Rectangle start_bulldozer_2;
extern Rectangle start_bulldozer_3;

//windmill stuff
#define VILLAGE_WINDMILL_X 299
#define VILLAGE_WINDMILL_Y 188
#define VILLAGE_WINDMILL_WIDTH 144
#define VILLAGE_WINDMILL_HEIGHT 192
#define VILLAGE_WINDMILL_RECT_OFFSET_X 30
#define VILLAGE_WINDMILL_RECT_OFFSET_Y 132
#define VILLAGE_WINDMILL_RECT_WIDTH 80
#define VILLAGE_WINDMILL_RECT_HEIGHT 32

extern Rectangle village_windmill_animation[4];
extern Rectangle village_windmill_1;
extern Rectangle village_windmill_2;
extern Rectangle village_windmill_3;
extern Rectangle village_windmill_4;

//paths to things
//map paths
#define WRONG_MAP_TEX_PATH "gfx/maps/wrong_map.png"

#define STARTING_MAP_TEX_PATH "gfx/maps/map_1_start.png"

#define VILLAGE_MAP_PATH "gfx/maps/map_2_village.png"
#define VILLAGE_HOUSE_1_PATH "gfx/maps/inside_village_houses/inside_village_house_1.png"
#define VILLAGE_HOUSE_2_PATH "gfx/maps/inside_village_houses/inside_village_house_2.png"
#define VILLAGE_HOUSE_3_PATH "gfx/maps/inside_village_houses/inside_village_house_3.png"
#define VILLAGE_HOUSE_4_PATH "gfx/maps/inside_village_houses/inside_village_house_4.png"
#define VILLAGE_WINDMILL_INSIDE_PATH "gfx/maps/inside_village_houses/inside_village_windmill.png"
#define VILLAGE_HOUSE_5_PATH "gfx/maps/inside_village_houses/inside_village_house_5.png"
#define VILLAGE_HOUSE_6_PATH "gfx/maps/inside_village_houses/inside_village_house_6.png"
#define VILLAGE_HOUSE_7_PATH "gfx/maps/inside_village_houses/inside_village_house_7.png"

#define DARK_FOREST_NORTH_PATH "gfx/maps/map_3_dark_forest_north.png"
#define DARK_FOREST_SOUTH_PATH "gfx/maps/map_4_dark_forest_south.png"
#define DARK_FOREST_CENTER_PATH "gfx/maps/map_5_dark_forest_center.png"


//music paths
#define START_MUSIC_PATH "sfx/start/Start_cliffs.mp3"
#define VILLAGE_MUSIC_PATH "sfx/village/Village.mp3"
#define VILLAGE_HOUSE_MUSIC_PATH "sfx/village/Inside VIllage House.mp3"
//entities and misc assets paths
#define PORTAL_TEX_PATH "gfx/assets/start_portal/start_portal_tex.png"
#define BULLDOZER_TEX_PATH "gfx/assets/bulldozer/bulldozer_tex.png"
#define VILLAGE_WINDMILL_PATH "gfx/assets/windmill/windmill_tex.png"
//player texture path
#define PLAYER_TEX_PATH "gfx/player/player_tex.png"

#endif