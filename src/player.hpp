#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "config.hpp"

#include "assets.hpp"
#include "map_loader.hpp"

extern Vector2 player_pos;

extern Rectangle *current_anim_arr;
extern Rectangle player_normal_hitbox;

extern int player_pos_x_save;
extern int player_pos_y_save;


extern int max_animation_frames;
extern int current_animation_frame;
extern int animation_frame_5;


extern void init_player();

extern void vertical_collision_check();
extern void update_player();
extern void draw_player();

#endif