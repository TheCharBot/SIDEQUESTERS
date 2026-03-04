#include "items.hpp"

Item Stick;
Item Sacred_bark;
Item Dungeon_key;
Ground_item Big_tree_level_1_stick;
Ground_item Big_tree_level_2_key; 
Ground_item Big_tree_level_5_key; 

std::unordered_map<Item_names, Item> items;

void init_dungeon_key_big_tree_level_2(){
    Big_tree_level_2_key.pos = BIG_TREE_LEVEL_2_KEY_POS;
    Big_tree_level_2_key.item = Dungeon_key;
    Big_tree_level_2_key.ground_item_name = BIG_TREE_LEVEL_2_KEY;
}

void init_dungeon_key_big_tree_level_5(){
    Big_tree_level_5_key.pos = BIG_TREE_LEVEL_2_KEY_POS;//yep, reused!
    Big_tree_level_5_key.item = Dungeon_key;
    Big_tree_level_5_key.ground_item_name = BIG_TREE_LEVEL_5_KEY;
}

void init_stick_big_tree_level_1(){
    Big_tree_level_1_stick.pos = BIG_TREE_LEVEL_1_STICK_POS;
    Big_tree_level_1_stick.item = Stick;
    Big_tree_level_1_stick.ground_item_name = BIG_TREE_LEVEL_1_STICK;
}

void init_dungeon_key(){
    Dungeon_key.name = DUNGEON_KEY;
    Dungeon_key.type = DUNGEON;
    Dungeon_key.img_rect = DUNGEON_KEY_SPRITE_RECT;
}

void init_stick()
{
    Stick.img_rect = STICK_SPRITE_RECT;
    Stick.type = COMBAT_MELEE;
    Stick.melee.damage = STICK_DAMAGE;
    Stick.melee.speed = STICK_SPEED;
    // uninitialized hitbox
}

void init_sacred_bark()
{
    Sacred_bark.name = SACRED_BARK;
    Sacred_bark.img_rect = SACRED_BARK_SPRITE_RECT;
    Sacred_bark.type = QUEST_ITEM;
    Sacred_bark.quest = SACRED_BARK_FROM_DARK_FOREST;
}

void add_item_to_inventory(Item item)
{
    for (Inventory_slot &s : inventory_slots){
        if(s.filled_with){
            continue;
        }
        else{
            s.filled_with = item;
            break;
        }
    }
}

void init_items()
{
    // items[Item_names::STICK] = Stick;
    init_dungeon_key();
    init_sacred_bark();
    init_stick();
    init_stick_big_tree_level_1();
    init_dungeon_key_big_tree_level_2();
    init_dungeon_key_big_tree_level_5();
}
