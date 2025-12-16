#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "config.hpp"

// Put sprite rects and other things here, paths, x defaults, etc

// Map-focused textures and paths
extern Texture2D starting_map;
#define STARTING_MAP_TEX_PATH "gfx/maps/map_1.png"
extern Texture2D wrong_map;
#define WRONG_MAP_TEX_PATH "gfx/maps/wrong_map.png"
#define MAP_1_RECT_1_X 0
#define MAP_1_RECT_1_Y 0
#define MAP_1_RECT_1_WIDTH 480
#define MAP_1_RECT_1_HEIGHT 135
#define MAP_1_RECT_2_X 0
#define MAP_1_RECT_2_Y 185
#define MAP_1_RECT_2_WIDTH 198
#define MAP_1_RECT_2_HEIGHT 135
#define MAP_1_RECT_3_X 198
#define MAP_1_RECT_3_Y 265
#define MAP_1_RECT_3_WIDTH 282
#define MAP_1_RECT_3_HEIGHT 55
#define MAP_1_RECT_4_X 282
#define MAP_1_RECT_4_Y 185
#define MAP_1_RECT_4_WIDTH 198
#define MAP_1_RECT_4_HEIGHT 80


// Player-focused textures and paths
extern Texture2D player_tex;
#define PLAYER_TEX_PATH "gfx/player/player_tex.png"
#define PLAYER_SPRITE_WIDTH 32
#define PLAYER_SPRITE_HEIGHT 48
#define PLAYER_HITBOX_WIDTH 13
#define PLAYER_HITBOX_HEIGHT 10
#define PLAYER_HITBOX_X_OFFSET 6
#define PLAYER_HITBOX_Y_OFFSET 38
#define PLAYER_SPEED 2

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
#define START_BULLDOZER_WIDTH 112
#define START_BULLDOZER_HEIGHT 80
#define BULLDOZER_TRIGGER_Y 185
#define BULLDOZER_TEX_PATH "gfx/assets/bulldozer/bulldozer_tex.png"
extern Rectangle start_bulldozer_animation[3];
extern Rectangle start_bulldozer_1;
extern Rectangle start_bulldozer_2;
extern Rectangle start_bulldozer_3;

#endif