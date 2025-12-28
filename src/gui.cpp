#include "gui.hpp"


Texture2D inventory_tex;
Texture2D inventory_cursor_tex;
Texture2D items_tex;
Vector2 inventory_pos = {0, 0};
std::vector<Item> player_inventory = {};
Inventory_cursor inv_cursor;


bool is_inv_open;

void gui_init()
{
    
    player_inventory.push_back(Stick);
    inventory_tex = LoadTexture(INVENTORY_PATH);
    items_tex = LoadTexture(ITEM_SHEET_PATH);
    inventory_cursor_tex = LoadTexture(INV_CURSOR_PATH);
}

void inv_cursor_init(){
    inv_cursor.held_item = {};
    inv_cursor.inv_slot_index = 0;
    inv_cursor.max_anim_frames = 2;
    inv_cursor.current_anim_frame = 0;
    inv_cursor.anim_frame_5 = 0;
}

void inv_cursor_update(){   
    inv_cursor.anim_frame_5++;
    if (inv_cursor.anim_frame_5 >= ANIMATION_INTERVAL+5)
    {
        inv_cursor.current_anim_frame++;
        if (inv_cursor.current_anim_frame >= inv_cursor.max_anim_frames)
        {
            inv_cursor.current_anim_frame = 0;
        }
        inv_cursor.anim_frame_5 = 0;
    }
    if(IsKeyPressed(KEY_W)){
        inv_cursor.inv_slot_index-=7;
    }
    if(IsKeyPressed(KEY_S)){
        inv_cursor.inv_slot_index+=7;
    }
    if(IsKeyPressed(KEY_D)){
        inv_cursor.inv_slot_index+=1;
    }
    if(IsKeyPressed(KEY_A)){
        inv_cursor.inv_slot_index-=1;
    }
    if(inv_cursor.inv_slot_index > 27){
        inv_cursor.inv_slot_index = 27;
    }
    if(inv_cursor.inv_slot_index < 0){
        inv_cursor.inv_slot_index = 0;
    }
    if(IsKeyPressed(KEY_Q)){
        
        inv_cursor.held_item = inventory_slots[inv_cursor.inv_slot_index].filled_with;
        
        
    }
}   

void gui_update()
{
    //maybe a performance problem but whatever
    inv_cursor_update();
    for(Item &i : player_inventory){
        inventory_slots[i.inventory_index].filled_with = i;
    }
    if(IsKeyPressed(KEY_TAB)){
        is_inv_open = !is_inv_open;
        if(is_inv_open){
            player.move_mode = 0;
            player.current_animation_frame = 0;
            
        }
        else{player.move_mode = 1;}
    }
}

void gui_draw()
{
    if(is_inv_open){
        //drawing inventory
        DrawTextureEx(inventory_tex, inventory_pos, 0, scale, WHITE);
        //drawing cursor
        DrawTexturePro(inventory_cursor_tex, inv_cursor_anim[inv_cursor.current_anim_frame], {inventory_slots[inv_cursor.inv_slot_index].pos.x*scale, inventory_slots[inv_cursor.inv_slot_index].pos.y*scale, inv_cursor_anim[inv_cursor.current_anim_frame].width*scale, inv_cursor_anim[inv_cursor.current_anim_frame].height*scale}, {0, 0}, 0, WHITE);
        //drawing held item
        DrawTexturePro(items_tex, inv_cursor.held_item.img_rect, {inventory_slots[inv_cursor.inv_slot_index].pos.x*scale, inventory_slots[inv_cursor.inv_slot_index].pos.y*scale, float(ITEM_SPRITE_WIDTH*scale), float(ITEM_SPRITE_HEIGHT*scale)}, {0, 0}, 0, WHITE);
        //drawing items
        for(Item &i : player_inventory){
            
            DrawTexturePro(items_tex, i.img_rect, {inventory_slots[i.inventory_index].pos.x*scale, inventory_slots[i.inventory_index].pos.y*scale, i.img_rect.width*scale, i.img_rect.height*scale}, {0, 0}, 0, WHITE);
        }
    }
}
