#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "game_objects.hpp"

// Put sprite rects and other things here, paths, x defaults, etc
// order of organization: gui globals, player globals, map globals, enums, structs, classes, map collisions, map loaders, paths (not perfect)

//fine. ill put it here. but i wont be happy!
extern void request_map(Map_names wanted_map, Vector2 wanted_player_spawn);
extern void remove_collision_rect(Rectangle rect);
extern void remove_locked_rect(Locked_rect rect);
extern void add_ground_item(Ground_item item);
extern void add_collisions(std::initializer_list<Rectangle> rects);
extern void add_load_rects(std::initializer_list<Load_rects> rects);
extern void textbox_update_draw();
extern void set_textbox_text(int index, Dialog_chunk dialog);
extern void setup_textbox(int max_indecies);


// editable globals
extern std::vector<Load_rects> map_load_rects;
extern Texture2D map_to_load;
extern std::vector<Rectangle> collision_rects;
extern std::vector<Locked_rect> locked_rects;
extern Map_names current_map;
extern Map_names requested_map;
extern Vector2 requested_player_pos;
extern Texture2D broken_tile_tex;
extern Texture2D door_lock_tex;
extern std::vector<Vector2> broken_floor_tiles;
extern std::vector<Ground_item> ground_items;
extern float fade_frame_timer;

extern Font global_font;

extern Inventory_slot inventory_slots[28];
extern Inventory_cursor inv_cursor;

extern Music current_music;
extern std::vector<std::unique_ptr<Entity>> entities;

// GUI globals
extern Texture2D inventory_tex;
extern Texture2D inventory_cursor_tex;
extern Texture2D items_tex;
extern Texture2D health_bar_tex;
extern Texture2D hotbar_tex;
extern Texture2D textbox_tex;
extern Rectangle health_bar_left_end;
extern Rectangle health_bar_right_end;
extern Rectangle health_bar_right_middle;
extern Rectangle health_bar_middle;
extern Rectangle health_bar_left_middle;
extern Rectangle health_bar_middle_dead;
extern Rectangle health_bar_middle_left_dead;
extern Vector2 hotbar_pos;
extern bool is_inv_open;
extern bool is_textbox_open;
extern int dialog_index_state;
extern int dialog_max_indecies;

//basically, set the individual indicies of this to change the dialog
#define MAX_DIALOG_INDICIES 20
extern Dialog_chunk current_dialog[MAX_DIALOG_INDICIES]; // change this to accomadate larger things

// player globals
extern Player player;

// inited items

extern Item inv_cursor_held_item;

// inventory cursor animation
extern Rectangle inv_cursor_1;
extern Rectangle inv_cursor_2;
extern Rectangle inv_cursor_anim[2];

#define GUI_LIGHT_GRAY Color{74, 84, 98, 255}
#define GUI_DARK_GRAY Color{51, 57, 65, 255}

//edit these to change controls
#define KEY_CONTROLS_UP KEY_UP
#define KEY_CONTROLS_DOWN KEY_DOWN
#define KEY_CONTROLS_RIGHT KEY_RIGHT
#define KEY_CONTROLS_LEFT KEY_LEFT
#define KEY_ITEM_HOTBAR_1 KEY_A
#define KEY_ITEM_HOTBAR_2 KEY_S
#define KEY_ITEM_HOTBAR_3 KEY_D
#define KEY_OPEN_INVENTORY KEY_TAB
#define KEY_INTERACT KEY_X

#define HITSTOP_TIMER_DAMAGE_DIVIDER 10

#define ITEM_PICKUP_DIALOG_RECT {0, 0, 64, 16}
#define BROKEN_TILE_RECT {48, 0, 16, 16}

#define ITEM_PICKUP_X_OFFSET 8
#define ITEM_PICKUP_Y_OFFSET 8
#define ITEM_PICKUP_RECT_WIDTH 32
#define ITEM_PICKUP_RECT_HEIGHT 32

#define PLAYER_IFRAME_TIME 0.8f // seconds
#define ENEMY_IFRAME_TIME 0.2f // seconds
#define KNOCKBACK_DIST 20.0f
#define HIT_FLASH_TIME 0.22f

#define HOTBAR_KEY_TEXT_OFFSET_X 104
#define HOTBAR_KEY_TEXT_OFFSET_Y 1
#define DEFAULT_FONT_SIZE 17
#define HOTBAR_SLOT_1_OFFSET_X 7
#define HOTBAR_SLOT_2_OFFSET_X 37
#define HOTBAR_SLOT_3_OFFSET_X 67
#define HEALTHBAR_OFFSET_X 1
#define HEALTHBAR_OFFSET_Y 1
#define SCREEN_FADE_TIME 0.3f
#define HOTBAR_POS {208, 3}
#define TEXTBOX_POS {0, 110}
#define MAX_ONE_LINE_CHARACTERS 41
#define MAX_TWO_LINE_CHARACTERS 82
#define MAX_THREE_LINE_CHARACTERS 120
#define MAX_TEXTBOX_CHARACTERS 159


#define DEFAULT_SPRITE_WIDTH 64
#define DEFAULT_SPRITE_HEIGHT 64
#define DEFAULT_SPRITE_WIDTH_128 128
#define DEFAULT_SPRITE_HEIGHT_128 128


#define START_BULLDOZER_X 6
#define START_BULLDOZER_Y 110
#define START_BULLDOZER_WIDTH 99
#define START_BULLDOZER_HEIGHT 75
#define BULLDOZER_TRIGGER_Y 185
#define BULLDOZER_SPEED 5
#define MAX_BULLDOZER_X 190
#define BULLDOZER_CUTSCENE_TRIGGER_X 160

#define VILLAGE_WINDMILL_X 299
#define VILLAGE_WINDMILL_Y 188
#define VILLAGE_WINDMILL_WIDTH 144
#define VILLAGE_WINDMILL_HEIGHT 192
#define VILLAGE_WINDMILL_RECT_OFFSET_X 30
#define VILLAGE_WINDMILL_RECT_OFFSET_Y 132
#define VILLAGE_WINDMILL_RECT_WIDTH 80
#define VILLAGE_WINDMILL_RECT_HEIGHT 32

#define BIG_TREE_POS {31, -71}
#define BIG_TREE_RECT_W_H  208, 1
#define BIG_TREE_RECT_OFFSET_Y 865

#define BIG_TREE_RECT1_W_H  200, 55
#define BIG_TREE_RECT1_OFFSET_Y 848
#define BIG_TREE_RECT1_OFFSET_X 4

#define BIG_TREE_RECT2_W_H  56, 24
#define BIG_TREE_RECT2_OFFSET_Y 903
#define BIG_TREE_RECT2_OFFSET_X 31

#define BIG_TREE_RECT3_W_H  56, 24
#define BIG_TREE_RECT3_OFFSET_Y 903
#define BIG_TREE_RECT3_OFFSET_X 121

#define BIG_TREE_LEVELS_TREE_TRUNKS_W_H 40, 16
#define BIG_TREE_LEVELS_TREE_TRUNKS_OFFSET_X 44
#define BIG_TREE_LEVELS_TREE_TRUNKS_OFFSET_Y 96
#define BIG_TREE_LEVELS_TREE_TRUNKS_POS {96, 70}


#define START_PORTAL_X 224
#define START_PORTAL_Y 37
#define START_PORTAL_WIDTH 32
#define START_PORTAL_HEIGHT 44

#define BIG_TREE_LEVELS_TREE_TRUNKS_HEALTH 4

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

// ----------------------------------------------------------------- COLLISION RECTS AREA --------------------------------------------------------------------
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

//dark forest center stuff
#define MAP_5_RECT_1 {0, 0, 32, 960}
#define MAP_5_RECT_2 {32, 640, 256, 133}
#define MAP_5_RECT_3 {112, 0, 48, 549}
#define MAP_5_RECT_4 {240, 128, 48, 645}
#define MAP_5_RECT_5 {288, 656, 112, 117}
#define MAP_5_RECT_6 {480, 656, 80, 304}
#define MAP_5_RECT_7 {336, 864, 144, 96}
#define MAP_5_RECT_8 {368, 0, 80, 565}
#define MAP_5_RECT_9 {448, 432, 192, 133}
#define MAP_5_RECT_10 {640, 432, 112, 277}
#define MAP_5_RECT_11 {160, 0, 208, 37}
#define MAP_5_RECT_12 {448, 0, 448, 37}
#define MAP_5_RECT_13 {896, 0, 64, 133}
#define MAP_5_RECT_14 {528, 128, 288, 212}
#define MAP_5_RECT_15 {816, 224, 16, 116}
#define MAP_5_RECT_16 {832, 224, 128, 645}
#define MAP_5_RECT_17 {640, 799, 192, 70}


// wall rects for houses
#define VILLAGE_HOUSE_RECT_1 {56, 48, 176, 20}  // wall
#define VILLAGE_HOUSE_RECT_2 {228, 68, 4, 88}   // wall
#define VILLAGE_HOUSE_RECT_3 {56, 68, 4, 88}    // wall
#define VILLAGE_HOUSE_RECT_4 {60, 156, 75, 20}  // wall
#define VILLAGE_HOUSE_RECT_5 {153, 156, 75, 20} // wall

// village house 1 stuff
#define VILLAGE_HOUSE_1_RECT_6 {60, 68, 78, 37}
#define VILLAGE_HOUSE_1_RECT_7 {191, 68, 37, 45}

#define INSIDE_WINDMILL_RECT_1 {128, 44, 32, 37}
#define INSIDE_WINDMILL_RECT_2 {127, 207, 7, 33}
#define INSIDE_WINDMILL_RECT_3 {160, 57, 37, 25}
#define INSIDE_WINDMILL_RECT_4 {196, 82, 28, 9}
#define INSIDE_WINDMILL_RECT_5 {91, 57, 37, 25}
#define INSIDE_WINDMILL_RECT_6 {64, 82, 28, 9}
#define INSIDE_WINDMILL_RECT_7 {48, 82, 11, 39}
#define INSIDE_WINDMILL_RECT_8 {229, 82, 11, 39}
#define INSIDE_WINDMILL_RECT_9 {233, 121, 11, 46}
#define INSIDE_WINDMILL_RECT_10 {44, 121, 11, 46}
#define INSIDE_WINDMILL_RECT_11 {229, 167, 11, 39}
#define INSIDE_WINDMILL_RECT_12 {48, 167, 11, 39}
#define INSIDE_WINDMILL_RECT_13 {63, 191, 19, 43}
#define INSIDE_WINDMILL_RECT_14 {206, 191, 19, 43}
#define INSIDE_WINDMILL_RECT_15 {187, 195, 19, 43}
#define INSIDE_WINDMILL_RECT_16 {82, 195, 19, 43}
#define INSIDE_WINDMILL_RECT_17 {103, 200, 19, 43}
#define INSIDE_WINDMILL_RECT_18 {166, 200, 19, 43}
#define INSIDE_WINDMILL_RECT_19 {154, 205, 19, 43}
#define INSIDE_WINDMILL_RECT_20 {115, 205, 19, 43}


// village house 2 stuff (finish later, get other things done now)
//(leave blank for now)

//big tree level constant rects
#define BIG_TREE_LEVEL_RECT_1 {112, 16, 96, 16}
#define BIG_TREE_LEVEL_RECT_2 {208, 32, 32, 16}
#define BIG_TREE_LEVEL_RECT_3 {240, 48, 32, 16}
#define BIG_TREE_LEVEL_RECT_4 {272, 64, 16, 32}
#define BIG_TREE_LEVEL_RECT_5 {288, 96, 16, 32}
#define BIG_TREE_LEVEL_RECT_6 {304, 128, 16, 80}
#define BIG_TREE_LEVEL_RECT_7 {288, 208, 16, 32}
#define BIG_TREE_LEVEL_RECT_8 {272, 240, 16, 80}
#define BIG_TREE_LEVEL_RECT_9 {240, 272, 32, 16}
#define BIG_TREE_LEVEL_RECT_10 {208, 288, 32, 16}
#define BIG_TREE_LEVEL_RECT_11 {112, 304, 96, 16} // not for level 1
#define BIG_TREE_LEVEL_RECT_12 {80, 288, 32, 16}
#define BIG_TREE_LEVEL_RECT_13 {48, 272, 32, 16}
#define BIG_TREE_LEVEL_RECT_14 {32, 240, 16, 32}
#define BIG_TREE_LEVEL_RECT_15 {16, 208, 16, 32}
#define BIG_TREE_LEVEL_RECT_16 {0, 128, 16, 80}
#define BIG_TREE_LEVEL_RECT_17 {16, 96, 16, 32}
#define BIG_TREE_LEVEL_RECT_18 {32, 64, 16, 32}
#define BIG_TREE_LEVEL_RECT_19 {48, 48, 32, 16}
#define BIG_TREE_LEVEL_RECT_20 {80, 32, 32, 16}
#define BIG_TREE_LEVEL_RECT_21 {96, 304, 16, 16}
#define BIG_TREE_LEVEL_RECT_22 {208, 304, 16, 16}

//big tree level-specific rects
#define BIG_TREE_LEVEL_1_RECT_1 {}
#define BIG_TREE_STAIRS_TOP_UP_RECT {173, 32, 33, 14}

#define BIG_TREE_STAIRS_BOTTOM_UP_RECT_1 {194, 259, 13, 10}
#define BIG_TREE_STAIRS_BOTTOM_UP_RECT_2 {184, 269, 23, 9}
#define BIG_TREE_STAIRS_BOTTOM_UP_RECT_3 {173, 278, 34, 25}



// ----------------------------------------------------------------- LOAD RECTS AREA --------------------------------------------------------------------
// loader rects for other maps
// NAME the LOAD RECTS PLEASE!!!!!!!
#define MAP_2_DARK_FOREST_NORTH_LOAD {8, 105, 1, 62}
#define MAP_2_DARK_FOREST_SOUTH_LOAD {284, 639, 58, 1}
#define MAP_2_VILLAGE_HOUSE_1_LOAD {383, 201, 18, 1}
#define MAP_2_VILLAGE_HOUSE_2_LOAD {223, 361, 18, 1}
#define MAP_2_WINDMILL_LOAD {358, 353, 22, 1} // <-windmill here - load rect 5
#define MAP_2_VILLAGE_HOUSE_3_LOAD {543, 361, 18, 1}
#define MAP_2_VILLAGE_HOUSE_4_LOAD {143, 553, 18, 1}
#define MAP_2_VILLAGE_HOUSE_5_LOAD {303, 553, 18, 1}
#define MAP_2_VILLAGE_HOUSE_6_LOAD {463, 553, 18, 1}
#define MAP_2_VILLAGE_HOUSE_7_LOAD {623, 553, 18, 1}
#define VILLAGE_HOUSE_OUTSIDE_LOAD_RECT {136, 175, 16, 1}
#define WINDMILL_INSIDE_TO_VILLAGE {133, 239, 22, 1}

#define DARK_FOREST_NORTH_TO_VILLAGE {945, 109, 1, 89}
#define DARK_FOREST_NORTH_TO_DARK_FOREST_CENTER {32, 639, 80, 1}

// dark forest south stuffs
#define DARK_FOREST_SOUTH_TO_VILLAGE {281, 26, 60, 1}
#define DARK_FOREST_SOUTH_TO_DARK_FOREST_CENTER_1 {5, 155, 1, 57}
#define DARK_FOREST_SOUTH_TO_DARK_FOREST_CENTER_2 {5, 893, 1, 54}

//dark forest center things
#define DARK_FOREST_CENTER_TO_DARK_FOREST_NORTH {43, 40, 58, 1}
#define DARK_FOREST_CENTER_TO_DARK_FOREST_SOUTH_1 {959, 155, 1, 59}
#define DARK_FOREST_CENTER_TO_DARK_FOREST_SOUTH_2 {959, 893, 1, 53}
#define DARK_FOREST_CENTER_TO_BIG_TREE_LEVEL_1 {119, 841, 32, 1}

#define BIG_TREE_LEVEL_1_TO_DARK_FOREST_CENTER {112, 319, 96, 1}

//do this w/ the stairs, make them all the same position so you dont go insane
#define BIG_TREE_STAIRS_TOP_UP_LOAD_RECT {172, 23, 1, 25}
#define BIG_TREE_STAIRS_TOP_DOWN_LOAD_RECT {185, 34, 21, 13}

#define BIG_TREE_STAIRS_BOTTOM_UP_LOAD_RECT {172, 278, 1, 25}
#define BIG_TREE_STAIRS_BOTTOM_DOWN_LOAD_RECT {185, 289, 21, 13}


// ----------------------------------------------------------------- SPAWNPOINTS AREA --------------------------------------------------------------------
// next time, do load spawnpoints like this: in the format "destination spawnpoint from origin"
//there is definently a better way to do this. whatever
#define DARK_FOREST_NORTH_SPAWNPOINT_FROM_VILLAGE {904, 90}
#define DARK_FOREST_SOUTH_SPAWNPOINT_FROM_VILLAGE {280, -10}
#define VILLAGE_SPAWNPOINT_FROM_DARK_FOREST_NORTH {-4, 90}
#define VILLAGE_SPAWNPOINT_FROM_DARK_FOREST_SOUTH {280, 559}
#define DARK_FOREST_CENTER_SPAWNPOINT_FROM_DARK_FOREST_NORTH {40, 0}
#define DARK_FOREST_CENTER_SPAWNPOINT_FROM_DARK_FOREST_SOUTH_1 {907, 140}
#define DARK_FOREST_CENTER_SPAWNPOINT_FROM_DARK_FOREST_SOUTH_2 {907, 876}
#define DARK_FOREST_NORTH_SPAWNPOINT_FROM_DARK_FOREST_CENTER {40, 580}
#define DARK_FOREST_SOUTH_1_SPAWNPOINT_FROM_DARK_FOREST_CENTER {-13, 140}
#define DARK_FOREST_SOUTH_2_SPAWNPOINT_FROM_DARK_FOREST_CENTER {-13, 876}

#define DARK_FOREST_CENTER_SPAWNPOINT_FROM_BIG_TREE_LEVEL_1 {103, 810}

// constant village house load rects for my sanity

#define PLAYER_VILLAGE_HOUSE_START_POS {113, 123}
#define VILLAGE_WINDMILL_INSIDE_SPAWNPOINT_FROM_VILLAGE {112, 181}
#define VILLAGE_HOUSE_1_OUTSIDE_SPAWNPOINT {361, 165}
#define VILLAGE_HOUSE_2_OUTSIDE_SPAWNPOINT {201, 325}
#define VILLAGE_HOUSE_3_OUTSIDE_SPAWNPOINT {521, 325}
#define VILLAGE_HOUSE_4_OUTSIDE_SPAWNPOINT {121, 517}
#define VILLAGE_HOUSE_5_OUTSIDE_SPAWNPOINT {281, 517}
#define VILLAGE_HOUSE_6_OUTSIDE_SPAWNPOINT {441, 517}
#define VILLAGE_HOUSE_7_OUTSIDE_SPAWNPOINT {601, 517}
#define VILLAGE_WINDMILL_OUTSIDE_SPAWNPOINT {338, 320}

//big tree level 1
#define BIG_TREE_LEVEL_1_SPAWNPOINT_FROM_DARK_FOREST_CENTER {128, 267}
#define BIG_TREE_DEFAULT_TOP_SPAWNPOINT {169, 13} //use as default for top spawnpoints

//big tree level 2
#define BIG_TREE_DEFAULT_BOTTOM_SPAWNPOINT {185, 234} //use as default for bottom spawnpoints


// music stuff

// ----------------------------------------------------------------- LOCKED  RECTS AREA --------------------------------------------------------------------
//document like "map_name" then "lock_rect"
#define BIG_TREE_LEVELS_BOTTOM_UP_LOCK_RECT {172, 259, 35, 44}

//----------------------------------------------------------------- OTHER CONSTANTS AREA (entities, player, etc) -----------------------------------------------------------------

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



extern Rectangle start_portal_animation[4];
extern Rectangle start_portal_1;
extern Rectangle start_portal_2;
extern Rectangle start_portal_3;
extern Rectangle start_portal_4;
extern Rectangle start_portal_emination;

// bulldozer image and rects



extern Rectangle start_bulldozer_animation[3];
extern Rectangle start_bulldozer_1;
extern Rectangle start_bulldozer_2;
extern Rectangle start_bulldozer_3;

// windmill stuff


extern Rectangle village_windmill_animation[4];
extern Rectangle village_windmill_1;
extern Rectangle village_windmill_2;
extern Rectangle village_windmill_3;
extern Rectangle village_windmill_4;

//tree trunk in big tree level stuff
extern Rectangle Big_tree_levels_tree_trunk_middle;
extern Rectangle Big_tree_levels_tree_trunk_top;
extern Rectangle Big_tree_levels_tree_trunk_bottom;




//forest scourge stuff
//idle arrays
extern Rectangle forest_scourge_idle_down_right[3];
extern Rectangle forest_scourge_idle_up_right[3];
extern Rectangle forest_scourge_idle_down_left[3];
extern Rectangle forest_scourge_idle_up_left[3];
//walking arrays
extern Rectangle forest_scourge_walk_down_right[7];
extern Rectangle forest_scourge_walk_up_left[7];
//attacking arrays
extern Rectangle forest_scourge_attack_down_right[6];
extern Rectangle forest_scourge_attack_up_left[6];

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
//really, the game only uses up left and down right, the rest is kinda pointless, none of the little guys are left handed, sorry
extern Rectangle forest_scourge_walk_down_right_1;
extern Rectangle forest_scourge_walk_down_right_2;
extern Rectangle forest_scourge_walk_down_right_3;
extern Rectangle forest_scourge_walk_down_right_4;
extern Rectangle forest_scourge_walk_down_right_5;
extern Rectangle forest_scourge_walk_down_right_6;
extern Rectangle forest_scourge_walk_down_right_7;
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
extern Rectangle forest_scourge_attack_down_right_6;
extern Rectangle forest_scourge_attack_up_left_1;
extern Rectangle forest_scourge_attack_up_left_2;
extern Rectangle forest_scourge_attack_up_left_3;
extern Rectangle forest_scourge_attack_up_left_4;
extern Rectangle forest_scourge_attack_up_left_5;
extern Rectangle forest_scourge_attack_up_left_6;

//TODO: ORGANIZE!!!!!!!!


//The Regrown stuff


extern Rectangle the_regrown_default_sprite_arr[1]; //annoying placeholder thingy (i hate pointers)
extern Rectangle the_regrown_entrance_arr[8];
extern Rectangle the_regrown_idle_arr[4];
extern Rectangle the_regrown_attack_right_arr[5];
extern Rectangle the_regrown_attack_left_arr[5];
extern Rectangle the_regrown_ground_shake_arr[6];
extern Rectangle the_regrown_die_arr[14];

extern Rectangle the_regrown_default_sprite; // placeholder thingy

extern Rectangle the_regrown_entrance_1;
extern Rectangle the_regrown_entrance_2;
extern Rectangle the_regrown_entrance_3;
extern Rectangle the_regrown_entrance_4;
extern Rectangle the_regrown_entrance_5;
extern Rectangle the_regrown_entrance_6;
extern Rectangle the_regrown_entrance_7;
extern Rectangle the_regrown_entrance_8;

extern Rectangle the_regrown_idle_1;
extern Rectangle the_regrown_idle_2;
extern Rectangle the_regrown_idle_3;
extern Rectangle the_regrown_idle_4;

extern Rectangle the_regrown_attack_right_1;
extern Rectangle the_regrown_attack_right_2;
extern Rectangle the_regrown_attack_right_3;
extern Rectangle the_regrown_attack_right_4;
extern Rectangle the_regrown_attack_right_5;
extern Rectangle the_regrown_attack_left_1;
extern Rectangle the_regrown_attack_left_2;
extern Rectangle the_regrown_attack_left_3;
extern Rectangle the_regrown_attack_left_4;
extern Rectangle the_regrown_attack_left_5;
extern Rectangle the_regrown_ground_shake_1;
extern Rectangle the_regrown_ground_shake_2;
extern Rectangle the_regrown_ground_shake_3;
extern Rectangle the_regrown_ground_shake_4;
extern Rectangle the_regrown_ground_shake_5;
extern Rectangle the_regrown_ground_shake_6;

extern Rectangle the_regrown_die_1;
extern Rectangle the_regrown_die_2;
extern Rectangle the_regrown_die_3;
extern Rectangle the_regrown_die_4;
extern Rectangle the_regrown_die_5;
extern Rectangle the_regrown_die_6;
extern Rectangle the_regrown_die_7;
extern Rectangle the_regrown_die_8;
extern Rectangle the_regrown_die_9;
extern Rectangle the_regrown_die_10;
extern Rectangle the_regrown_die_11;
extern Rectangle the_regrown_die_12;
extern Rectangle the_regrown_die_13;
extern Rectangle the_regrown_die_14;

extern Rectangle the_regrown_possible_destructable_tile_area;
extern Rectangle the_regrown_impossible_destructable_tile_area;
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

#define BIG_TREE_TEX_PATH "gfx/assets/big_tree/big_tree_tex.png"

#define BIG_TREE_LEVEL_1_PATH "gfx/maps/big_tree_levels/big_tree_level_1.png"
#define BIG_TREE_LEVEL_2_PATH "gfx/maps/big_tree_levels/big_tree_level_2.png"
#define BIG_TREE_LEVEL_3_PATH "gfx/maps/big_tree_levels/big_tree_level_3.png"
#define BIG_TREE_LEVEL_4_PATH "gfx/maps/big_tree_levels/big_tree_level_4.png"
#define BIG_TREE_LEVEL_5_PATH "gfx/maps/big_tree_levels/big_tree_level_5.png"
#define BIG_TREE_LEVEL_6_PATH "gfx/maps/big_tree_levels/big_tree_level_6.png"
#define BIG_TREE_LEVEL_7_PATH "gfx/maps/big_tree_levels/big_tree_level_7.png"
#define BIG_TREE_LEVEL_8_PATH "gfx/maps/big_tree_levels/big_tree_level_8.png"
#define BIG_TREE_LEVEL_9_PATH "gfx/maps/big_tree_levels/big_tree_level_9.png"
#define BIG_TREE_LEVEL_10_PATH "gfx/maps/big_tree_levels/big_tree_level_10.png"

#define THE_REGROWN_TEX_PATH "gfx/enemies/bosses/the_regrown/the_regrown_tex.png"
#define FOREST_SCOURGE_TEX_PATH "gfx/enemies/forest_scourge/forest_scourge_tex.png"

#define BIG_TREE_LEVELS_TREE_TRUNKS_TEX_PATH "gfx/assets/big_tree/tree_trunks/tree_trunks_tex.png"

// music paths

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
#define HEALTH_BAR_PATH "gfx/gui/health_bar_tex.png"
#define HOTBAR_TEX_PATH "gfx/gui/hotbar_tex.png"
#define GLOB_FONT_PATH "gfx/font/BlockBlueprint.ttf"
#define TEXTBOX_TEX_PATH "gfx/gui/textbox_tex.png"

#define BROKEN_TILE_TEX_PATH "gfx/assets/broken_ground/broken_ground_tex.png"
#define DOOR_LOCK_TEX_PATH "gfx/assets/door_locks/door_lock_tex.png"

#endif