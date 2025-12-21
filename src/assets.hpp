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

    virtual void load() {}
    virtual void update() = 0;
    virtual void draw() = 0;
};
extern std::vector<std::unique_ptr<Entity>> entities;
// Map-focused stuff
extern Texture2D map_to_load;
extern std::vector<Rectangle> collision_rects;
extern std::vector<Rectangle> map_load_rects;
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
#define WRONG_MAP_TEX_PATH "gfx/maps/wrong_map.png"


struct Drawable{
    float y;
    std::function<void()> draw_function;
};

extern std::vector<Drawable> draw_list;

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
extern Texture2D start_portal_tex;
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
extern Texture2D start_bulldozer_tex;
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

#endif