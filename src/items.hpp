#ifndef ITEMS_HPP
#define ITEMS_HPP

#include "config.hpp"

#include "assets.hpp"
#include "item_data.hpp"

//just data usage for items
extern Item Stick;
extern Item null_item;

extern void init_stick();
extern void add_item_to_inventory(Item item, int slot_index);
extern void init_items();

#endif