#include "items.hpp"






void add_item_to_inventory(Item item)
{
    if(item.type == CONSUMABLE){
        for (Inventory_slot &s : inventory_slots){
            if(s.filled_with->name == item.name){
                s.filled_with->consumable.amount++;
                return;
            }
            else{
                break;
            }
        }
    }
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
    game.item_ids[Item_names::SACRED_BARK].name = Item_names::SACRED_BARK;
    game.item_ids[Item_names::SACRED_BARK].img_rect = SACRED_BARK_SPRITE_RECT;
    game.item_ids[Item_names::SACRED_BARK].type = Item_types::QUEST_ITEM;
    game.item_ids[Item_names::SACRED_BARK].quest = SACRED_BARK_FROM_DARK_FOREST;

    game.item_ids[Item_names::STICK].name = Item_names::STICK;
    game.item_ids[Item_names::STICK].img_rect = STICK_SPRITE_RECT;
    game.item_ids[Item_names::STICK].type = Item_types::COMBAT_MELEE;
    game.item_ids[Item_names::STICK].melee.damage = STICK_DAMAGE;

    game.item_ids[Item_names::DUNGEON_KEY].name = Item_names::DUNGEON_KEY;
    game.item_ids[Item_names::DUNGEON_KEY].type = Item_types::DUNGEON;
    game.item_ids[Item_names::DUNGEON_KEY].img_rect = DUNGEON_KEY_SPRITE_RECT;

    game.item_ids[Item_names::RED_BERRIES].name = Item_names::RED_BERRIES;
    game.item_ids[Item_names::RED_BERRIES].type = Item_types::CONSUMABLE;
    game.item_ids[Item_names::RED_BERRIES].img_rect = RED_BERRIES_IMG_RECT;
    game.item_ids[Item_names::RED_BERRIES].consumable.amount = 1;
    game.item_ids[Item_names::RED_BERRIES].consumable.buff_type = Buff_types::HEAL;
    game.item_ids[Item_names::RED_BERRIES].consumable.buff_strength = 0.5;

    
    game.ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_1_STICK].pos = BIG_TREE_LEVEL_1_STICK_POS;
    game.ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_1_STICK].item = game.item_ids[Item_names::STICK];
    game.ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_1_STICK].ground_item_name = Ground_item_names::BIG_TREE_LEVEL_1_STICK;

    game.ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_5_KEY].pos = BIG_TREE_LEVEL_2_KEY_POS;
    game.ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_5_KEY].item = game.item_ids[Item_names::DUNGEON_KEY];
    game.ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_5_KEY].ground_item_name = Ground_item_names::BIG_TREE_LEVEL_5_KEY;

    game.ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_2_KEY].pos = BIG_TREE_LEVEL_2_KEY_POS;
    game.ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_2_KEY].item = game.item_ids[Item_names::DUNGEON_KEY];
    game.ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_2_KEY].ground_item_name = Ground_item_names::BIG_TREE_LEVEL_2_KEY;
}
