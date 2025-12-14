#include "assets.hpp"


//non-constant asset stuff

Rectangle start_portal_1 = {0, 0, START_PORTAL_WIDTH, START_PORTAL_HEIGHT};
Rectangle start_portal_2 = {48, 0, START_PORTAL_WIDTH, START_PORTAL_HEIGHT};
Rectangle start_portal_3 = {96, 0, START_PORTAL_WIDTH, START_PORTAL_HEIGHT};
Rectangle start_portal_4 = {144, 0, START_PORTAL_WIDTH, START_PORTAL_HEIGHT};
Rectangle start_portal_animation[4] = {
    start_portal_1,
    start_portal_2, 
    start_portal_3,
    start_portal_4
};
Rectangle start_portal_emination;


// player-focused stuff
Texture2D player_tex;
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
Rectangle player_idle_up = {32, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_idle_right = {64, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_idle_left = {96, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_1 = {0, 48, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_2 = {32, 48, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_3 = {64, 48, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_4 = {96, 48, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_5 = {128, 48, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_6 = {160, 48, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_7 = {192, 48, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_8 = {224, 48, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_9 = {256, 48, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_10 = {288, 48, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_11 = {320, 48, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_down_12 = {352, 48, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_1 = {0, 96, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_2 = {32, 96, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_3 = {64, 96, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_4 = {96, 96, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_5 = {128, 96, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_6 = {160, 96, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_7 = {192, 96, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_8 = {224, 96, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_9 = {256, 96, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_10 = {288, 96, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_11 = {320, 96, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_up_12 = {352, 96, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_1 = {0, 144, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_2 = {32, 144, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_3 = {64, 144, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_4 = {96, 144, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_5 = {128, 144, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_6 = {160, 144, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_7 = {192, 144, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_right_8 = {224, 144, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_1 = {0, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_2 = {32, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_3 = {64, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_4 = {96, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_5 = {128, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_6 = {160, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_7 = {192, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
Rectangle player_walk_left_8 = {224, 192, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
