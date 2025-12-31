#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "game_objects.hpp"

// Put sprite rects and other things here, paths, x defaults, etc
// order of organization: gui globals, player globals, map globals, enums, structs, classes, map collisions, map loaders, paths (not perfect)

//fine. ill put it here. but i wont be happy!
extern void request_map(Map_names wanted_map, Vector2 wanted_player_spawn);

// editable globals
extern std::vector<Load_rects> map_load_rects;
extern Texture2D map_to_load;
extern std::vector<Rectangle> collision_rects;
extern int current_map;
extern Map_names requested_map;
extern Vector2 requested_player_pos;
extern Inventory_slot inventory_slots[28];
extern Inventory_cursor inv_cursor;

extern Music current_music;
extern std::vector<std::unique_ptr<Entity>> entities;

// GUI globals
extern Texture2D inventory_tex;
extern Texture2D inventory_cursor_tex;
extern Texture2D items_tex;
extern Vector2 inventory_pos;
extern std::vector<Item> player_inventory;
extern bool is_inv_open;

// player globals
extern Player player;

// inited items
extern Item Stick;
extern Item null_item;
extern Item inv_cursor_held_item;

// inventory cursor animation
extern Rectangle inv_cursor_1;
extern Rectangle inv_cursor_2;
extern Rectangle inv_cursor_anim[2];

// Player-focused image rect arrays
extern Rectangle player_idle_up_arr[1];
extern Rectangle player_idle_down_arr[1];
extern Rectangle player_idle_right_arr[1];
extern Rectangle player_idle_left_arr[1];
extern Rectangle player_walk_down[12];
extern Rectangle player_walk_up[12];
extern Rectangle player_walk_right[8];
extern Rectangle player_walk_left[8];
// Player-focused image rects

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

// player attack rects

extern Rectangle player_sword_slash_down_1;
extern Rectangle player_sword_slash_down_2;
extern Rectangle player_sword_slash_down_3;
extern Rectangle player_sword_slash_down_4;
extern Rectangle player_sword_slash_down_5;
extern Rectangle player_sword_slash_up_1;
extern Rectangle player_sword_slash_up_2;
extern Rectangle player_sword_slash_up_3;
extern Rectangle player_sword_slash_up_4;
extern Rectangle player_sword_slash_up_5;
extern Rectangle player_sword_slash_right_1;
extern Rectangle player_sword_slash_right_2;
extern Rectangle player_sword_slash_right_3;
extern Rectangle player_sword_slash_right_4;
extern Rectangle player_sword_slash_right_5;
extern Rectangle player_sword_slash_left_1;
extern Rectangle player_sword_slash_left_2;
extern Rectangle player_sword_slash_left_3;
extern Rectangle player_sword_slash_left_4;
extern Rectangle player_sword_slash_left_5;
extern Rectangle player_sword_slash_down_arr[5];
extern Rectangle player_sword_slash_up_arr[5];
extern Rectangle player_sword_slash_right_arr[5];
extern Rectangle player_sword_slash_left_arr[5];

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

// Dark Forest North stuff
#define MAP_3_RECT_1 {32, 0, 928, 85}
#define MAP_3_RECT_2 {0, 85, 32, 300}
#define MAP_3_RECT_3 {112, 176, 818, 117}
#define MAP_3_RECT_4 {928, 293, 32, 300}
#define MAP_3_RECT_5 {33, 385, 815, 116}
#define MAP_3_RECT_6 {0, 501, 32, 139}
#define MAP_3_RECT_7 {112, 593, 816, 47}

// dark forest south stuff
#define MAP_4_RECT_1 {0, 0, 272, 133}
#define MAP_4_RECT_2 {352, 0, 16, 133}
#define MAP_4_RECT_3 {368, 0, 240, 21}
#define MAP_4_RECT_4 {608, 0, 32, 433}
#define MAP_4_RECT_5 {352, 433, 288, 68}
#define MAP_4_RECT_6 {352, 501, 64, 176}
#define MAP_4_RECT_7 {497, 592, 63, 277}
#define MAP_4_RECT_8 {176, 769, 320, 100}
#define MAP_4_RECT_9 {176, 225, 80, 544}
#define MAP_4_RECT_10 {256, 225, 256, 116}
#define MAP_4_RECT_11 {449, 112, 63, 113}
#define MAP_4_RECT_12 {0, 225, 96, 644}

// loader rects for other maps
// NAME the LOAD RECTS PLEASE!!!!!!!
#define MAP_2_DARK_FOREST_NORTH_LOAD {8, 105, 1, 62}
#define MAP_2_DARK_FOREST_SOUTH_LOAD {284, 639, 58, 1}
#define MAP_2_VILLAGE_HOUSE_1_LOAD {383, 201, 18, 1}
#define MAP_2_VILLAGE_HOUSE_2_LOAD {223, 361, 18, 1}
#define MAP_2_WINDMILL_LOAD {358, 352, 22, 1} // <-windmill here - load rect 5
#define MAP_2_VILLAGE_HOUSE_3_LOAD {543, 361, 18, 1}
#define MAP_2_VILLAGE_HOUSE_4_LOAD {143, 553, 18, 1}
#define MAP_2_VILLAGE_HOUSE_5_LOAD {303, 553, 18, 1}
#define MAP_2_VILLAGE_HOUSE_6_LOAD {463, 553, 18, 1}
#define MAP_2_VILLAGE_HOUSE_7_LOAD {623, 553, 18, 1}

// next time, do load spawnpoints like this: in the format "destination spawnpoint from origin"
#define DARK_FOREST_NORTH_SPAWNPOINT_FROM_VILLAGE {904, 90}
#define DARK_FOREST_SOUTH_SPAWNPOINT_FROM_VILLAGE {280, -10}
#define VILLAGE_SPAWNPOINT_FROM_DARK_FOREST_NORTH {-4, 90}
#define VILLAGE_SPAWNPOINT_FROM_DARK_FOREST_SOUTH {280, 559}

// constant village house load rects for my sanity
#define VILLAGE_HOUSE_OUTSIDE_LOAD_RECT {136, 175, 16, 1}
#define PLAYER_VILLAGE_HOUSE_START_POS {113, 123}
#define VILLAGE_HOUSE_1_OUTSIDE_SPAWNPOINT {361, 165}
#define VILLAGE_HOUSE_2_OUTSIDE_SPAWNPOINT {201, 325}
#define VILLAGE_HOUSE_3_OUTSIDE_SPAWNPOINT {521, 325}
#define VILLAGE_HOUSE_4_OUTSIDE_SPAWNPOINT {121, 517}
#define VILLAGE_HOUSE_5_OUTSIDE_SPAWNPOINT {281, 517}
#define VILLAGE_HOUSE_6_OUTSIDE_SPAWNPOINT {441, 517}
#define VILLAGE_HOUSE_7_OUTSIDE_SPAWNPOINT {601, 517}
#define VILLAGE_WINDMILL_OUTSIDE_SPAWNPOINT {338, 320}

// wall rects for houses
#define VILLAGE_HOUSE_RECT_1 {56, 48, 176, 20}  // wall
#define VILLAGE_HOUSE_RECT_2 {228, 68, 4, 88}   // wall
#define VILLAGE_HOUSE_RECT_3 {56, 68, 4, 88}    // wall
#define VILLAGE_HOUSE_RECT_4 {60, 156, 75, 20}  // wall
#define VILLAGE_HOUSE_RECT_5 {153, 156, 75, 20} // wall

// village house 1 stuff
#define VILLAGE_HOUSE_1_RECT_6 {60, 68, 78, 37}
#define VILLAGE_HOUSE_1_RECT_7 {191, 68, 37, 45}

// village house 2 stuff (finish later, get other things done now)
//(leave blank for now)

// more dark forest north stuff
// actually, make load rects look like this, in the format of "origin to destination"
#define DARK_FOREST_NORTH_TO_VILLAGE {945, 109, 1, 89}
#define DARK_FOREST_NORTH_TO_DARK_FOREST_CENTER {32, 639, 80, 1}

// dark forest south stuffs
#define DARK_FOREST_SOUTH_TO_VILLAGE {281, 26, 60, 1}

// music stuff

// constants defines (not rects)
#define PLAYER_SPRITE_WIDTH 64
#define PLAYER_SPRITE_HEIGHT 64
#define PLAYER_HITBOX_WIDTH 13
#define PLAYER_HITBOX_HEIGHT 10
#define PLAYER_HITBOX_X_OFFSET 25
#define PLAYER_HITBOX_Y_OFFSET 42
#define PLAYER_SPEED 2
#define PLAYER_START_MAP_POS_X 209
#define PLAYER_START_MAP_POS_Y 196
#define PLAYER_VILLAGE_MAP_POS_X 267
#define PLAYER_VILLAGE_MAP_POS_Y 128

#define ITEM_SPRITE_WIDTH 16
#define ITEM_SPRITE_HEIGHT 16

// start portal image and rects

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

// bulldozer image and rects

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

// windmill stuff
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


//forest scourge stuff
#define DEFAULT_SPRITE_WIDTH 64
#define DEFAULT_SPRITE_HEIGHT 64
#define FOREST_SCOURGE_HITBOX_OFFSET_X 28
#define FOREST_SCOURGE_HITBOX_OFFSET_Y 31
#define FOREST_SCOURGE_HITBOX_WIDTH 27
#define FOREST_SCOURGE_HITBOX_HEIGHT 31
//idle arrays
extern Rectangle forest_scourge_idle_down_right[3];
extern Rectangle forest_scourge_idle_up_right[3];
extern Rectangle forest_scourge_idle_down_left[3];
extern Rectangle forest_scourge_idle_up_left[3];
//walking arrays
extern Rectangle forest_scourge_walk_down_right[7];
extern Rectangle forest_scourge_walk_down_left[7];
extern Rectangle forest_scourge_walk_up_right[7];
extern Rectangle forest_scourge_walk_up_left[7];
//attacking arrays
extern Rectangle forest_scourge_attack_down_right[5];
extern Rectangle forest_scourge_attack_down_left[5];
extern Rectangle forest_scourge_attack_up_right[5];
extern Rectangle forest_scourge_attack_up_left[5];
//idle animations - before it sees the player
extern Rectangle forest_scourge_idle_down_right_1;
extern Rectangle forest_scourge_idle_down_right_2;
extern Rectangle forest_scourge_idle_down_right_3;
extern Rectangle forest_scourge_idle_up_right_1;
extern Rectangle forest_scourge_idle_up_right_2;
extern Rectangle forest_scourge_idle_up_right_3;
extern Rectangle forest_scourge_idle_down_left_1;
extern Rectangle forest_scourge_idle_down_left_2;
extern Rectangle forest_scourge_idle_down_left_3;
extern Rectangle forest_scourge_idle_up_left_1;
extern Rectangle forest_scourge_idle_up_left_2;
extern Rectangle forest_scourge_idle_up_left_3;
//walk animations - scuffed, but it works for now
extern Rectangle forest_scourge_walk_down_right_1;
extern Rectangle forest_scourge_walk_down_right_2;
extern Rectangle forest_scourge_walk_down_right_3;
extern Rectangle forest_scourge_walk_down_right_4;
extern Rectangle forest_scourge_walk_down_right_5;
extern Rectangle forest_scourge_walk_down_right_6;
extern Rectangle forest_scourge_walk_down_right_7;
extern Rectangle forest_scourge_walk_down_left_1;
extern Rectangle forest_scourge_walk_down_left_2;
extern Rectangle forest_scourge_walk_down_left_3;
extern Rectangle forest_scourge_walk_down_left_4;
extern Rectangle forest_scourge_walk_down_left_5;
extern Rectangle forest_scourge_walk_down_left_6;
extern Rectangle forest_scourge_walk_down_left_7;
extern Rectangle forest_scourge_walk_up_right_1;
extern Rectangle forest_scourge_walk_up_right_2;
extern Rectangle forest_scourge_walk_up_right_3;
extern Rectangle forest_scourge_walk_up_right_4;
extern Rectangle forest_scourge_walk_up_right_5;
extern Rectangle forest_scourge_walk_up_right_6;
extern Rectangle forest_scourge_walk_up_right_7;
extern Rectangle forest_scourge_walk_up_left_1;
extern Rectangle forest_scourge_walk_up_left_2;
extern Rectangle forest_scourge_walk_up_left_3;
extern Rectangle forest_scourge_walk_up_left_4;
extern Rectangle forest_scourge_walk_up_left_5;
extern Rectangle forest_scourge_walk_up_left_6;
extern Rectangle forest_scourge_walk_up_left_7;
//attack animations (im now thinking that i should make a better way of storing all of these)
extern Rectangle forest_scourge_attack_down_right_1;
extern Rectangle forest_scourge_attack_down_right_2;
extern Rectangle forest_scourge_attack_down_right_3;
extern Rectangle forest_scourge_attack_down_right_4;
extern Rectangle forest_scourge_attack_down_right_5;
extern Rectangle forest_scourge_attack_down_left_1;
extern Rectangle forest_scourge_attack_down_left_2;
extern Rectangle forest_scourge_attack_down_left_3;
extern Rectangle forest_scourge_attack_down_left_4;
extern Rectangle forest_scourge_attack_down_left_5;
extern Rectangle forest_scourge_attack_up_right_1;
extern Rectangle forest_scourge_attack_up_right_2;
extern Rectangle forest_scourge_attack_up_right_3;
extern Rectangle forest_scourge_attack_up_right_4;
extern Rectangle forest_scourge_attack_up_right_5;
extern Rectangle forest_scourge_attack_up_left_1;
extern Rectangle forest_scourge_attack_up_left_2;
extern Rectangle forest_scourge_attack_up_left_3;
extern Rectangle forest_scourge_attack_up_left_4;
extern Rectangle forest_scourge_attack_up_left_5;

// paths to things
// map paths
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

// music paths
#define START_MUSIC_PATH "sfx/start/Start_cliffs.mp3"
#define VILLAGE_MUSIC_PATH "sfx/village/Village.mp3"
#define VILLAGE_HOUSE_MUSIC_PATH "sfx/village/Inside VIllage House.mp3"
// entities and misc assets paths
#define PORTAL_TEX_PATH "gfx/assets/start_portal/start_portal_tex.png"
#define BULLDOZER_TEX_PATH "gfx/assets/bulldozer/bulldozer_tex.png"
#define VILLAGE_WINDMILL_PATH "gfx/assets/windmill/windmill_tex.png"
// player texture path
#define PLAYER_TEX_PATH "gfx/player/player_tex.png"
// gui and items sheet paths
#define INVENTORY_PATH "gfx/gui/inventory_tex.png"
#define ITEM_SHEET_PATH "gfx/items_tex.png"
#define INV_CURSOR_PATH "gfx/gui/inventory_cursor.png"

#endif