#include "items.hpp"

Item Stick;

void init_stick()
{
    Stick.img_rect = STICK_SPRITE_RECT;
    Stick.type = COMBAT_MELEE;
    Stick.melee.damage = STICK_DAMAGE;
    Stick.melee.speed = STICK_SPEED;
    // uninitialized hitbox
    Stick.melee.hitbox = {};
}

void add_item_to_inventory(Item item, int slot_index)
{
    player_inventory.push_back(item);
    inventory_slots[slot_index].filled_with = item;
}

void init_items()
{

    init_stick();
}
