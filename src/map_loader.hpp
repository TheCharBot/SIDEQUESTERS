#ifndef MAP_HPP
#define MAP_HPP


#include "entities.hpp"
#include "hostile_entities.hpp"

extern void init_map();
extern void add_collisions(std::initializer_list<Rectangle> rects);
extern void add_load_rects(std::initializer_list<Load_rects> rects);

extern void reset_player(Vector2 spawn);
extern void load_map(Map_names map, Vector2 new_player_pos);
extern void update_map();
extern void draw_map();

#endif