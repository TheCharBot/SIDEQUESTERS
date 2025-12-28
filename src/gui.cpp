#include "gui.hpp"


Texture2D inventory_tex;
Texture2D items_tex;
Vector2 inventory_pos = {0, 0};
std::vector<Item> player_inventory = {};

bool is_inv_open;

void gui_init()
{
    
    player_inventory.push_back(Stick);
    inventory_tex = LoadTexture(INVENTORY_PATH);
    items_tex = LoadTexture(ITEM_SHEET_PATH);
}

void gui_update()
{
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
        DrawTextureEx(inventory_tex, inventory_pos, 0, scale, WHITE);
        for(Item &i : player_inventory){
            
            DrawTexturePro(items_tex, i.img_rect, {inventory_slots[i.inventory_index].pos.x*scale, inventory_slots[i.inventory_index].pos.y*scale, i.img_rect.width*scale, i.img_rect.height*scale}, {0, 0}, 0, WHITE);
        }
    }
}
