#include "assets.hpp"

// this file is for image and other constant rects

// 23, 24, 25
// IM SORRY. It couldnt be avoided.
Inventory_slot inventory_slots[28] = {
    {{48, 32}, 0, {}},
    {{80, 32}, 0, {}},
    {{112, 32}, 0, {}},
    {{147, 32}, 0, {}},
    {{182, 32}, 0, {}},
    {{214, 32}, 0, {}},
    {{246, 32}, 0, {}},
    {{48, 64}, 0, {}},
    {{80, 64}, 0, {}},
    {{112, 64}, 0, {}},
    {{147, 64}, 0, {}},
    {{182, 64}, 0, {}},
    {{214, 64}, 0, {}},
    {{246, 64}, 0, {}},
    {{48, 96}, 0, {}},
    {{80, 96}, 0, {}},
    {{112, 96}, 0, {}},
    {{147, 96}, 0, {}},
    {{182, 96}, 0, {}},
    {{214, 96}, 0, {}},
    {{246, 96}, 0, {}},
    {{48, 128}, 0, {}},
    {{80, 128}, 0, {}},
    {{112, 128}, 0, {}}, // hotbar Q
    {{147, 128}, 0, {}}, // hotbar E
    {{182, 128}, 0, {}}, // hotbar Z
    {{214, 128}, 0, {}},
    {{246, 128}, 0, {}},

};

Rectangle health_bar_left_end = {1, 1, 2, 6};
Rectangle health_bar_right_end = {14, 1, 2, 6};
Rectangle health_bar_right_middle = {4, 1, 1, 6};
Rectangle health_bar_middle = {6, 1, 1, 6};
Rectangle health_bar_left_middle = {8, 1, 1, 6};
Rectangle health_bar_middle_dead = {10, 1, 1, 6};
Rectangle health_bar_middle_left_dead = {12, 1, 1, 6};

Rectangle inv_cursor_1 = {0, 0, 32, 18};
Rectangle inv_cursor_2 = {0, 32, 32, 18};
Rectangle inv_cursor_anim[2] = {
    inv_cursor_1,
    inv_cursor_2};

// windmill stuff

Rectangle village_windmill_1 = {96, 0, VILLAGE_WINDMILL_WIDTH, VILLAGE_WINDMILL_HEIGHT};
Rectangle village_windmill_2 = {240, 0, VILLAGE_WINDMILL_WIDTH, VILLAGE_WINDMILL_HEIGHT};
Rectangle village_windmill_3 = {384, 0, VILLAGE_WINDMILL_WIDTH, VILLAGE_WINDMILL_HEIGHT};
Rectangle village_windmill_4 = {528, 0, VILLAGE_WINDMILL_WIDTH, VILLAGE_WINDMILL_HEIGHT};
Rectangle village_windmill_animation[4] = {
    village_windmill_1,
    village_windmill_2,
    village_windmill_3,
    village_windmill_4};

// map stuff

int map_inited = 0;

// non-constant asset stuff
Rectangle start_bulldozer_animation[3] = {
    start_bulldozer_1,
    start_bulldozer_2,
    start_bulldozer_3};
Rectangle start_bulldozer_1 = {128, 0, START_BULLDOZER_WIDTH, START_BULLDOZER_HEIGHT};
Rectangle start_bulldozer_2 = {240, 0, START_BULLDOZER_WIDTH, START_BULLDOZER_HEIGHT};
Rectangle start_bulldozer_3 = {352, 0, START_BULLDOZER_WIDTH, START_BULLDOZER_HEIGHT};

Rectangle start_portal_1 = {0, 0, START_PORTAL_WIDTH, START_PORTAL_HEIGHT};
Rectangle start_portal_2 = {48, 0, START_PORTAL_WIDTH, START_PORTAL_HEIGHT};
Rectangle start_portal_3 = {96, 0, START_PORTAL_WIDTH, START_PORTAL_HEIGHT};
Rectangle start_portal_4 = {144, 0, START_PORTAL_WIDTH, START_PORTAL_HEIGHT};
Rectangle start_portal_animation[4] = {
    start_portal_1,
    start_portal_2,
    start_portal_3,
    start_portal_4};
Rectangle start_portal_emination;

// player-focused stuff

//(i know i can use pointers but they scary)
Rectangle player_idle_up_arr[1] = {
    player_idle_up};
Rectangle player_idle_down_arr[1] = {
    player_idle_down};
Rectangle player_idle_right_arr[1] = {
    player_idle_right};
Rectangle player_idle_left_arr[1] = {
    player_idle_left};
// player-focused rects, in player_tex
Rectangle player_walk_down[12] = {
    player_walk_down_1,
    player_walk_down_2,
    player_walk_down_3,
    player_walk_down_4,
    player_walk_down_5,
    player_walk_down_6,
    player_walk_down_7,
    player_walk_down_8,
    player_walk_down_9,
    player_walk_down_10,
    player_walk_down_11,
    player_walk_down_12};
Rectangle player_walk_up[12] = {
    player_walk_up_1,
    player_walk_up_2,
    player_walk_up_3,
    player_walk_up_4,
    player_walk_up_5,
    player_walk_up_6,
    player_walk_up_7,
    player_walk_up_8,
    player_walk_up_9,
    player_walk_up_10,
    player_walk_up_11,
    player_walk_up_12};
Rectangle player_walk_right[8] = {
    player_walk_right_1,
    player_walk_right_2,
    player_walk_right_3,
    player_walk_right_4,
    player_walk_right_5,
    player_walk_right_6,
    player_walk_right_7,
    player_walk_right_8,
};
Rectangle player_walk_left[8] = {
    player_walk_left_1,
    player_walk_left_2,
    player_walk_left_3,
    player_walk_left_4,
    player_walk_left_5,
    player_walk_left_6,
    player_walk_left_7,
    player_walk_left_8,
};
Rectangle player_idle_down = {0, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_idle_up = {64, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_idle_right = {128, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_idle_left = {192, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_1 = {0, 64, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_2 = {64, 64, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_3 = {128, 64, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_4 = {192, 64, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_5 = {256, 64, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_6 = {320, 64, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_7 = {384, 64, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_8 = {448, 64, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_9 = {512, 64, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_10 = {576, 64, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_11 = {640, 64, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_12 = {704, 64, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_1 = {0, 128, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_2 = {64, 128, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_3 = {128, 128, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_4 = {192, 128, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_5 = {256, 128, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_6 = {320, 128, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_7 = {384, 128, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_8 = {448, 128, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_9 = {512, 128, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_10 = {576, 128, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_11 = {640, 128, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_12 = {704, 128, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_1 = {0, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_2 = {64, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_3 = {128, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_4 = {192, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_5 = {256, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_6 = {320, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_7 = {384, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_8 = {448, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_1 = {0, 256, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_2 = {64, 256, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_3 = {128, 256, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_4 = {192, 256, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_5 = {256, 256, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_6 = {320, 256, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_7 = {384, 256, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_8 = {448, 256, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};

Rectangle player_sword_slash_down_1 = {0, 320, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_down_2 = {64, 320, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_down_3 = {128, 320, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_down_4 = {192, 320, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_down_5 = {256, 320, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_up_1 = {0, 384, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_up_2 = {64, 384, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_up_3 = {128, 384, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_up_4 = {192, 384, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_up_5 = {256, 384, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_right_1 = {0, 448, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_right_2 = {64, 448, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_right_3 = {128, 448, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_right_4 = {192, 448, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_right_5 = {256, 448, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_left_1 = {0, 512, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_left_2 = {64, 512, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_left_3 = {128, 512, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_left_4 = {192, 512, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_sword_slash_left_5 = {256, 512, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};

Rectangle player_sword_slash_down_arr[5] = {
    player_sword_slash_down_1,
    player_sword_slash_down_2,
    player_sword_slash_down_3,
    player_sword_slash_down_4,
    player_sword_slash_down_5,
};
Rectangle player_sword_slash_up_arr[5] = {
    player_sword_slash_up_1,
    player_sword_slash_up_2,
    player_sword_slash_up_3,
    player_sword_slash_up_4,
    player_sword_slash_up_5,
};
Rectangle player_sword_slash_right_arr[5] = {
    player_sword_slash_right_1,
    player_sword_slash_right_2,
    player_sword_slash_right_3,
    player_sword_slash_right_4,
    player_sword_slash_right_5,
};
Rectangle player_sword_slash_left_arr[5] = {
    player_sword_slash_left_1,
    player_sword_slash_left_2,
    player_sword_slash_left_3,
    player_sword_slash_left_4,
    player_sword_slash_left_5,
};




//forest scourge stuff
Rectangle forest_scourge_idle_down_right[3] = {
    forest_scourge_idle_down_right_1,
    forest_scourge_idle_down_right_2,
    forest_scourge_idle_down_right_3
};
Rectangle forest_scourge_idle_up_right[3] = {
    forest_scourge_idle_up_right_1,
    forest_scourge_idle_up_right_2,
    forest_scourge_idle_up_right_3
};
Rectangle forest_scourge_idle_down_left[3] = {
    forest_scourge_idle_down_left_1,
    forest_scourge_idle_down_left_2,
    forest_scourge_idle_down_left_3
};
Rectangle forest_scourge_idle_up_left[3] = {
    forest_scourge_idle_up_left_1,
    forest_scourge_idle_up_left_2,
    forest_scourge_idle_up_left_3
};
Rectangle forest_scourge_walk_down_right[7] = {
    forest_scourge_walk_down_right_1,
    forest_scourge_walk_down_right_2,
    forest_scourge_walk_down_right_3,
    forest_scourge_walk_down_right_4,
    forest_scourge_walk_down_right_5,
    forest_scourge_walk_down_right_6,
    forest_scourge_walk_down_right_7
};


Rectangle forest_scourge_walk_up_left[7] = {
    forest_scourge_walk_up_left_1,
    forest_scourge_walk_up_left_2,
    forest_scourge_walk_up_left_3,
    forest_scourge_walk_up_left_4,
    forest_scourge_walk_up_left_5,
    forest_scourge_walk_up_left_6,
    forest_scourge_walk_up_left_7
};
//forest scourge attacking arrays
Rectangle forest_scourge_attack_down_right[6] = {
    forest_scourge_attack_down_right_1,
    forest_scourge_attack_down_right_2,
    forest_scourge_attack_down_right_3,
    forest_scourge_attack_down_right_4,
    forest_scourge_attack_down_right_5,
    forest_scourge_attack_down_right_6
};

Rectangle forest_scourge_attack_up_left[6] = {
    forest_scourge_attack_up_left_1,
    forest_scourge_attack_up_left_2,
    forest_scourge_attack_up_left_3,
    forest_scourge_attack_up_left_4,
    forest_scourge_attack_up_left_5,
    forest_scourge_attack_up_left_6
};


Rectangle forest_scourge_idle_down_right_1 = {0, 0, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_idle_down_right_2 = {64, 0, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_idle_down_right_3 = {128, 0, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_idle_up_right_1 = {192, 0, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_idle_up_right_2 = {256, 0, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_idle_up_right_3 = {320, 0, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_idle_down_left_1 = {0, 64, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_idle_down_left_2 = {64, 64, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_idle_down_left_3 = {128, 64, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_idle_up_left_1 = {192, 64, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_idle_up_left_2 = {256, 64, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_idle_up_left_3 = {320, 64, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
//forest scourge walk animations
Rectangle forest_scourge_walk_down_right_1 = {0, 128, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_walk_down_right_2 = {64, 128, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_walk_down_right_3 = {128, 128, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_walk_down_right_4 = {192, 128, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_walk_down_right_5 = {256, 128, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_walk_down_right_6 = {320, 128, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_walk_down_right_7 = {384, 128, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_walk_up_left_1 = {0, 320, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_walk_up_left_2 = {64, 320, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_walk_up_left_3 = {128, 320, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_walk_up_left_4 = {192, 320, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_walk_up_left_5 = {256, 320, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_walk_up_left_6 = {320, 320, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_walk_up_left_7 = {384, 320, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
//forest scourge attack animations 
Rectangle forest_scourge_attack_down_right_1 = {0, 384, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_attack_down_right_2 = {64, 384, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_attack_down_right_3 = {128, 384, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_attack_down_right_4 = {192, 384, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_attack_down_right_5 = {256, 384, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_attack_down_right_6 = {320, 384, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_attack_up_left_1 = {0, 448, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_attack_up_left_2 = {64, 448, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_attack_up_left_3 = {128, 448, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_attack_up_left_4 = {192, 448, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_attack_up_left_5 = {256, 448, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};
Rectangle forest_scourge_attack_up_left_6 = {320, 448, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT};

Rectangle the_regrown_entrance_arr[8] = {
    the_regrown_entrance_1,
    the_regrown_entrance_2,
    the_regrown_entrance_3,
    the_regrown_entrance_4,
    the_regrown_entrance_5,
    the_regrown_entrance_6,
    the_regrown_entrance_7,
    the_regrown_entrance_8
};
Rectangle the_regrown_idle_arr[4] = {
    the_regrown_idle_1, 
    the_regrown_idle_2, 
    the_regrown_idle_3, 
    the_regrown_idle_4
};
Rectangle the_regrown_attack_right_arr[5] = {
    the_regrown_attack_right_1,
    the_regrown_attack_right_2,
    the_regrown_attack_right_3,
    the_regrown_attack_right_4,
    the_regrown_attack_right_5
};
Rectangle the_regrown_attack_left_arr[5] = {
    the_regrown_attack_left_1,
    the_regrown_attack_left_2,
    the_regrown_attack_left_3,
    the_regrown_attack_left_4,
    the_regrown_attack_left_5
};
Rectangle the_regrown_ground_shake_arr[6] = {
    the_regrown_ground_shake_1,
    the_regrown_ground_shake_2,
    the_regrown_ground_shake_3,
    the_regrown_ground_shake_4,
    the_regrown_ground_shake_5,
    the_regrown_ground_shake_6
};
Rectangle the_regrown_die_arr[14] = {
    the_regrown_die_1,
    the_regrown_die_2,
    the_regrown_die_3,
    the_regrown_die_4,
    the_regrown_die_5,
    the_regrown_die_6,
    the_regrown_die_7,
    the_regrown_die_8,
    the_regrown_die_9,
    the_regrown_die_10,
    the_regrown_die_11,
    the_regrown_die_12,
    the_regrown_die_13,
    the_regrown_die_14,
};

Rectangle the_regrown_default_sprite_arr[1] = {the_regrown_default_sprite};
Rectangle the_regrown_default_sprite = {0, 0, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};

Rectangle the_regrown_entrance_1 = {0, 128, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_entrance_2 = {128, 128, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_entrance_3 = {256, 128, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_entrance_4 = {384, 128, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_entrance_5 = {512, 128, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_entrance_6 = {640, 128, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_entrance_7 = {768, 128, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_entrance_8 = {896, 128, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};

Rectangle the_regrown_idle_1 = {0, 256, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_idle_2 = {128, 256, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_idle_3 = {256, 256, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_idle_4 = {384, 256, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};

Rectangle the_regrown_attack_right_1 = {0, 384, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_attack_right_2 = {128, 384, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_attack_right_3 = {256, 384, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_attack_right_4 = {384, 384, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_attack_right_5 = {512, 384, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};

Rectangle the_regrown_attack_left_1 = {0, 512, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_attack_left_2 = {128, 512, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_attack_left_3 = {256, 512, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_attack_left_4 = {384, 512, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_attack_left_5 = {512, 512, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};

Rectangle the_regrown_ground_shake_1 = {0, 640, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_ground_shake_2 = {128, 640, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_ground_shake_3 = {256, 640, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_ground_shake_4 = {384, 640, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_ground_shake_5 = {512, 640, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_ground_shake_6 = {640, 640, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};

Rectangle the_regrown_die_1 = {0, 768, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_die_2 = {128, 768, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_die_3 = {256, 768, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_die_4 = {384, 768, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_die_5 = {512, 768, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_die_6 = {640, 768, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_die_7 = {768, 768, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_die_8 = {896, 768, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_die_9 = {1024, 768, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128}; //first 4 digit image extractor1!!!!11
Rectangle the_regrown_die_10 = {0, 896, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_die_11 = {128, 896, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_die_12 = {256, 896, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_die_13 = {384, 896, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};
Rectangle the_regrown_die_14 = {512, 896, DEFAULT_SPRITE_WIDTH_128, DEFAULT_SPRITE_HEIGHT_128};