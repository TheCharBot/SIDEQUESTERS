#include "player.hpp"

Vector2 player_pos;

Rectangle *current_anim_arr;
Rectangle player_normal_hitbox;

int player_pos_x_save;
int player_pos_y_save;

void init_player()
{
    
    player_pos.x = (WINDOW_WIDTH * scale) / 2;
    player_pos.y = (WINDOW_HEIGHT * scale) / 2+120;
    player_normal_hitbox = {player_pos.x, player_pos.y, float(PLAYER_HITBOX_WIDTH*scale), float(PLAYER_HITBOX_HEIGHT*scale)};
    player_tex = LoadTexture(PLAYER_TEX_PATH);
};

void update_player()
{
    player_pos_x_save = player_pos.x;
    player_pos_y_save = player_pos.y;

    if (IsKeyDown(KEY_W))
    {
        player_pos.y -= PLAYER_SPEED * scale;
        
        current_anim_arr = player_walk_up;
        
    }
    if (IsKeyDown(KEY_S))
    {
        player_pos.y += PLAYER_SPEED * scale;
        current_anim_arr = player_walk_down;
        
        
    }
    //vertical hitbox rebuild
    player_normal_hitbox = {player_pos.x+PLAYER_HITBOX_X_OFFSET*scale, player_pos.y+PLAYER_HITBOX_Y_OFFSET*scale, float(PLAYER_HITBOX_WIDTH*scale), float(PLAYER_HITBOX_HEIGHT*scale)};
    //vertical collision check
    for (const Rectangle& r : map_surface_rects)
    {
        if (CheckCollisionRecs(player_normal_hitbox, r))
        {
            player_pos.y = player_pos_y_save;
            break;
        }
    }

    if (IsKeyDown(KEY_D))
    {
        player_pos.x += PLAYER_SPEED * scale;
        current_anim_arr = player_walk_right;
        
        
    }
    if (IsKeyDown(KEY_A))
    {
        player_pos.x -= PLAYER_SPEED * scale;
        current_anim_arr = player_walk_left;
        
    }
    //horizontal hitbox rebuild
    player_normal_hitbox = {player_pos.x+PLAYER_HITBOX_X_OFFSET*scale, player_pos.y+PLAYER_HITBOX_Y_OFFSET*scale, float(PLAYER_HITBOX_WIDTH*scale), float(PLAYER_HITBOX_HEIGHT*scale)};
    //horizontal collision check
    for (const Rectangle& r : map_surface_rects)
    {
        if (CheckCollisionRecs(player_normal_hitbox, r))
        {
            player_pos.x = player_pos_x_save;
            break;
        }
    }

    
    player_pos.x = Clamp(player_pos.x, 0, (map_to_load.width*scale) - (PLAYER_SPRITE_WIDTH * scale));
    player_pos.y = Clamp(player_pos.y, 0, (map_to_load.height*scale) - (PLAYER_SPRITE_HEIGHT * scale));
    
    // std::cout << player_pos.x << "  " << player_pos.y << "\n";
}

void draw_player()
{
    
    DrawTexturePro(player_tex, player_idle_down, {player_pos.x, player_pos.y, float(PLAYER_SPRITE_WIDTH * scale), float(PLAYER_SPRITE_HEIGHT * scale)}, {0, 0}, 0, WHITE);
    
};