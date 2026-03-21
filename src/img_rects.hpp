#ifndef IMG_RECTS_HPP
#define IMG_RECTS_HPP

#include "config.hpp"

#define DEFAULT_SPRITE_WIDTH 64
#define DEFAULT_SPRITE_HEIGHT 64
#define DEFAULT_SPRITE_WIDTH_128 128
#define DEFAULT_SPRITE_HEIGHT_128 128

#define START_BULLDOZER_WIDTH 99
#define START_BULLDOZER_HEIGHT 75

#define VILLAGE_WINDMILL_WIDTH 144
#define VILLAGE_WINDMILL_HEIGHT 192

#define START_PORTAL_WIDTH 32
#define START_PORTAL_HEIGHT 44

extern Rectangle inv_cursor_1;
extern Rectangle inv_cursor_2;
extern Rectangle inv_cursor_anim[2];
extern Rectangle health_bar_left_end;
extern Rectangle health_bar_right_end;
extern Rectangle health_bar_right_middle;
extern Rectangle health_bar_middle;
extern Rectangle health_bar_left_middle;
extern Rectangle health_bar_middle_dead;
extern Rectangle health_bar_middle_left_dead;

// Player-focused image rect arrays
extern Rectangle player_idle_up_arr[1];
extern Rectangle player_idle_down_arr[1];
extern Rectangle player_idle_right_arr[1];
extern Rectangle player_idle_left_arr[1];
extern Rectangle player_walk_down[12];
extern Rectangle player_walk_up[12];
extern Rectangle player_walk_right[8];
extern Rectangle player_walk_left[8];



extern Rectangle player_sword_slash_down_arr[5];
extern Rectangle player_sword_slash_up_arr[5];
extern Rectangle player_sword_slash_right_arr[5];
extern Rectangle player_sword_slash_left_arr[5];

extern Rectangle player_sprint_right[8];
extern Rectangle player_sprint_left[8];
extern Rectangle player_sprint_up[6];
extern Rectangle player_sprint_down[6];

extern Rectangle player_dash_right[8];
extern Rectangle player_dash_left[8];
extern Rectangle player_dash_up[6];
extern Rectangle player_dash_down[6];


extern Rectangle start_portal_animation[4];


// bulldozer image and rects



extern Rectangle start_bulldozer_animation[3];


// windmill stuff


extern Rectangle village_windmill_animation[4];


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


//TODO: ORGANIZE!!!!!!!!


//The Regrown stuff


extern Rectangle the_regrown_default_sprite_arr[1]; //annoying placeholder thingy (i hate pointers)
extern Rectangle the_regrown_entrance_arr[8];
extern Rectangle the_regrown_idle_arr[4];
extern Rectangle the_regrown_attack_right_arr[5];
extern Rectangle the_regrown_attack_left_arr[5];
extern Rectangle the_regrown_ground_shake_arr[6];
extern Rectangle the_regrown_die_arr[14];





extern Rectangle village_questgiver_idle[1];
extern Rectangle village_questgiver_point[3];

extern Rectangle start_menu_text_rect;
extern Rectangle start_menu_emination;
extern Rectangle start_menu_options_rect;
extern Rectangle start_menu_select_right;
extern Rectangle start_menu_select_left;
extern Rectangle start_menu_saves_select_screen;
extern Rectangle start_menu_saves_select_screen_selecter;
extern Rectangle start_menu_credits_screen;
extern Rectangle start_menu_achievements_screen;
extern Rectangle start_menu_options_screen;

#endif