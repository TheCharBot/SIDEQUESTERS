#include "items.hpp"

Item Stick;
Item Sacred_bark;
Item Dungeon_key;
Ground_item Big_tree_level_1_stick;

void init_stick_big_tree_level_1(){
    Big_tree_level_1_stick.pos = BIG_TREE_LEVEL_1_STICK_POS;
    Big_tree_level_1_stick.item = Stick;
    Big_tree_level_1_stick.interact_range = {Big_tree_level_1_stick.pos.x, Big_tree_level_1_stick.pos.y, 32, 32};
    Big_tree_level_1_stick.name = BIG_TREE_LEVEL_1_STICK;
}

void init_dungeon_key(){
    Dungeon_key.name = DUNGEON_KEY;
    Dungeon_key.type = DUNGEON;
}

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
    Sacred_bark.img_rect = SACRED_BARK_SPRITE_RECT;
    Sacred_bark.type = QUEST_ITEM;
    Sacred_bark.quest = SACRED_BARK_FROM_DARK_FOREST;
}

void add_item_to_inventory(Item item, int slot_index)
{
    player_inventory.push_back(item); //probably not idk
    inventory_slots[slot_index].filled_with = item;
}

void init_items()
{
    init_dungeon_key();
    init_sacred_bark();
    init_stick();
    init_stick_big_tree_level_1();
}
