#include "gui.hpp"


Texture2D inventory_tex;
Vector2 inventory_pos;
std::vector<Item> inventory;
bool is_inv_open;

void gui_init()
{
    inventory_tex = LoadTexture("gfx/gui/inventory.png");
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
}
