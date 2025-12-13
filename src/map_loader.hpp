#ifndef MAP_HPP
#define MAP_HPP

#include "config.hpp"

#include "assets.hpp"

extern Texture2D map_to_load;

extern Rectangle temp_rect;

extern Vector2 map_pos;

extern std::vector<Rectangle> map_surface_rects;
extern std::vector<Rectangle> map_load_rects;

extern void init_map();
extern void load_map(int map);
extern void update_map();
extern void draw_map();

#endif