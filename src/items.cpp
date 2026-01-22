#include "items.hpp"

Item Stick;
Item Sacred_bark;

void init_stick()
{
    Stick.img_rect = STICK_SPRITE_RECT;
    Stick.type = COMBAT_MELEE;
    Stick.melee.damage = STICK_DAMAGE;
    Stick.melee.speed = STICK_SPEED;
    // uninitialized hitbox
    Stick.melee.hitbox = {};
}

void init_sacred_bark()
{
    Sacred_bark.name = SACRED_BARK;
    Sacred_bark.img_rect = {32, 0, 16, 16};//TODO:MACROS
    Sacred_bark.type = QUEST_ITEM;
    Sacred_bark.quest = SACRED_BARK_FROM_DARK_FOREST;
}

void add_item_to_inventory(Item item, int slot_index)
{
    player_inventory.push_back(item);
    inventory_slots[slot_index].filled_with = item;
}

void init_items()
{
    init_sacred_bark();
    init_stick();
}
