#ifndef MAP_HPP
#define MAP_HPP


#include "entities.hpp"
#include "hostile_entities.hpp"

extern void init_map();


extern void reset_player(Vector2 spawn);

extern void load_big_tree_level_1();
extern void load_map(Map_names map, Vector2 new_player_pos);
extern void update_map();
extern void draw_map();
extern void kill_things_that_are_dead();
extern void load_requested_map();

#endif


