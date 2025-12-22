#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "config.hpp"

// Put sprite rects and other things here, paths, x defaults, etc

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
extern std::vector<std::unique_ptr<Entity>> entities;
// Map-focused stuff
struct Load_rects{
    Rectangle rect;
    int map_to_load_struct;
};
extern std::vector<Load_rects> map_load_rects;
extern Texture2D map_to_load;
extern std::vector<Rectangle> collision_rects;
extern int current_map;
extern int requested_map;
#define STARTING_MAP_TEX_PATH "gfx/maps/map_1_start.png"
#define MAP_1_RECT_1 {0, 0, 480, 135}
#define MAP_1_RECT_2 {0, 185, 198, 135}
#define MAP_1_RECT_3 {198, 265, 282, 55}
#define MAP_1_RECT_4 {282, 185, 198, 80}
#define VILLAGE_MAP_PATH "gfx/maps/map_2_village.png"
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
#define MAP_2_LOAD_RECT_1 {10, 0, 1, 640}
#define MAP_2_LOAD_RECT_2 {0, 629, 734, 1}
#define WRONG_MAP_TEX_PATH "gfx/maps/wrong_map.png"





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
#define PLAYER_TEX_PATH "gfx/player/player_tex.png"
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
#define PORTAL_TEX_PATH "gfx/assets/start_portal/start_portal_tex.png"
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
#define BULLDOZER_TEX_PATH "gfx/assets/bulldozer/bulldozer_tex.png"
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
#define VILLAGE_WINDMILL_PATH "gfx/assets/windmill/windmill_tex.png"
extern Rectangle village_windmill_animation[4];
extern Rectangle village_windmill_1;
extern Rectangle village_windmill_2;
extern Rectangle village_windmill_3;
extern Rectangle village_windmill_4;


#endif