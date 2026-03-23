#include "items.hpp"


Ground_item Big_tree_level_1_stick;
Ground_item Big_tree_level_2_key; 
Ground_item Big_tree_level_5_key; 

std::unordered_map<Item_names, Item> item_ids;
std::unordered_map<Ground_item_names, Ground_item> ground_item_ids;



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
    item_ids[Item_names::SACRED_BARK].name = Item_names::SACRED_BARK;
    item_ids[Item_names::SACRED_BARK].img_rect = SACRED_BARK_SPRITE_RECT;
    item_ids[Item_names::SACRED_BARK].type = QUEST_ITEM;
    item_ids[Item_names::SACRED_BARK].quest = SACRED_BARK_FROM_DARK_FOREST;

    item_ids[Item_names::STICK].img_rect = STICK_SPRITE_RECT;
    item_ids[Item_names::STICK].type = COMBAT_MELEE;
    item_ids[Item_names::STICK].melee.damage = STICK_DAMAGE;

    item_ids[Item_names::DUNGEON_KEY].name = Item_names::DUNGEON_KEY;
    item_ids[Item_names::DUNGEON_KEY].type = DUNGEON;
    item_ids[Item_names::DUNGEON_KEY].img_rect = DUNGEON_KEY_SPRITE_RECT;
    
    ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_1_STICK].pos = BIG_TREE_LEVEL_1_STICK_POS;
    ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_1_STICK].item = item_ids[Item_names::STICK];
    ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_1_STICK].ground_item_name = BIG_TREE_LEVEL_1_STICK;

    ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_5_KEY].pos = BIG_TREE_LEVEL_2_KEY_POS;
    ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_5_KEY].item = item_ids[Item_names::DUNGEON_KEY];
    ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_5_KEY].ground_item_name = BIG_TREE_LEVEL_5_KEY;

    ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_2_KEY].pos = BIG_TREE_LEVEL_2_KEY_POS;
    ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_2_KEY].item = item_ids[Item_names::DUNGEON_KEY];
    ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_2_KEY].ground_item_name = BIG_TREE_LEVEL_2_KEY;
}
