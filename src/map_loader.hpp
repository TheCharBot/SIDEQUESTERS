#ifndef MAP_HPP
#define MAP_HPP

#include "config.hpp"

#include "assets.hpp"
#include "entities.hpp"


extern void init_map();
extern void request_map(Map_names wanted_map, Vector2 wanted_player_spawn);
extern void reset_player(Vector2 spawn);
extern void load_map(Map_names map, Vector2 new_player_pos);
extern void update_map();
extern void draw_map();

#endif