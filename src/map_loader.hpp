#ifndef MAP_HPP
#define MAP_HPP

#include "config.hpp"

#include "assets.hpp"
#include "entities.hpp"


extern void init_map();
extern void reset_player(Vector2 spawn);
extern void load_map(int map);
extern void update_map();
extern void draw_map();

#endif