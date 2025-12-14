#include "player.hpp"

Vector2 player_pos;
Vector2 player_movement;

Rectangle *current_anim_arr = player_walk_down;
Rectangle player_normal_hitbox;

int player_pos_x_save;
int player_pos_y_save;


int player_max_animation_frames = 12;
int player_current_animation_frame = 0;

int player_animation_frame_5 = 0;

enum Facing{UP, DOWN, RIGHT, LEFT};
Facing facing;

void init_player()
{

    player_pos.x = (WINDOW_WIDTH * scale) / 2;
    player_pos.y = (WINDOW_HEIGHT * scale) / 2 + 40;
    player_normal_hitbox = {player_pos.x, player_pos.y, float(PLAYER_HITBOX_WIDTH * scale), float(PLAYER_HITBOX_HEIGHT * scale)};
    player_tex = LoadTexture(PLAYER_TEX_PATH);
};

void update_player()
{
    player_pos_x_save = player_pos.x;
    player_pos_y_save = player_pos.y;

    player_movement = {0, 0};

    //movement calculations with a seperate vector
    if (IsKeyDown(KEY_W)) player_movement.y -= 1;
    if (IsKeyDown(KEY_S)) player_movement.y += 1;
    if (IsKeyDown(KEY_A)) player_movement.x -= 1;
    if (IsKeyDown(KEY_D)) player_movement.x += 1;

    //animation array calculations
    if (player_movement.y < 0)
    {
        facing = UP;
        current_anim_arr = player_walk_up;
        if(player_max_animation_frames != 12){
            player_current_animation_frame = 0;
            player_max_animation_frames = 12;
        }
    }
    else if (player_movement.y > 0)
    {
        facing = DOWN;
        current_anim_arr = player_walk_down;
        if(player_max_animation_frames != 12){
            player_current_animation_frame = 0;
            player_max_animation_frames = 12;
        }
    }
    else if (player_movement.x > 0)
    {
        facing = RIGHT;
        current_anim_arr = player_walk_right;
        if(player_max_animation_frames != 8){
            player_current_animation_frame = 0;
            player_max_animation_frames = 8;
        }
    }
    else if (player_movement.x < 0)
    {
        facing = LEFT;
        current_anim_arr = player_walk_left;
        if(player_max_animation_frames != 8){
            player_current_animation_frame = 0;
            player_max_animation_frames = 8;
        }
    }

    //idle animation calculations
    if(player_movement.x == 0 && player_movement.y == 0){
        if(facing == UP){
            current_anim_arr = player_idle_up_arr;
            if(player_max_animation_frames != 1){
                player_current_animation_frame = 0;
                player_max_animation_frames = 1;
            }
        }
        if(facing == DOWN){
            current_anim_arr = player_idle_down_arr;
            if(player_max_animation_frames != 1){
                player_current_animation_frame = 0;
                player_max_animation_frames = 1;
            }
        }
        if(facing == RIGHT){
            current_anim_arr = player_idle_right_arr;
            if(player_max_animation_frames != 1){
                player_current_animation_frame = 0;
                player_max_animation_frames = 1;
            }
        }
        if(facing == LEFT){
            current_anim_arr = player_idle_left_arr;
            if(player_max_animation_frames != 1){
                player_current_animation_frame = 0;
                player_max_animation_frames = 1;
            }
        }
    }

    // normalize diagonal movement
    if (player_movement.x != 0 || player_movement.y != 0)
    {
        player_movement = Vector2Normalize(player_movement);

        player_pos.x += player_movement.x * PLAYER_SPEED * scale;
        
        //player hitbox rebuild
        player_normal_hitbox = {
            player_pos.x + PLAYER_HITBOX_X_OFFSET * scale,
            player_pos.y + PLAYER_HITBOX_Y_OFFSET * scale,
            float(PLAYER_HITBOX_WIDTH * scale),
            float(PLAYER_HITBOX_HEIGHT * scale)
        };
        // horizontal collision check
        for (const Rectangle &r : map_surface_rects)
        {
            if (CheckCollisionRecs(player_normal_hitbox, r))
            {
                player_pos.x = player_pos_x_save;
                break;
            }
        }
        player_pos.y += player_movement.y * PLAYER_SPEED * scale;
        //player hitbox rebuild
        player_normal_hitbox = {
            player_pos.x + PLAYER_HITBOX_X_OFFSET * scale,
            player_pos.y + PLAYER_HITBOX_Y_OFFSET * scale,
            float(PLAYER_HITBOX_WIDTH * scale),
            float(PLAYER_HITBOX_HEIGHT * scale)
        };
        // vertical collision check
        for (const Rectangle &r : map_surface_rects)
        {
            if (CheckCollisionRecs(player_normal_hitbox, r))
            {
                player_pos.y = player_pos_y_save;
                break;
            }
        }

        //making sure the player is at least inside the screen
        player_pos.x = Clamp(player_pos.x, 0, (map_to_load.width * scale) - (PLAYER_SPRITE_WIDTH * scale));
        player_pos.y = Clamp(player_pos.y, 0, (map_to_load.height * scale) - (PLAYER_SPRITE_HEIGHT * scale));


    }
    
    
    
    //animation thingy
    player_animation_frame_5++;
        if(player_animation_frame_5 >= ANIMATION_INTERVAL){
            player_current_animation_frame++;
            if(player_current_animation_frame >= player_max_animation_frames){
                player_current_animation_frame = 0;
            }
            player_animation_frame_5 = 0;
        }
    
    // std::cout << player_pos.x << "  " << player_pos.y << "\n";
}

void draw_player()
{  
    DrawTexturePro(player_tex, current_anim_arr[player_current_animation_frame], {player_pos.x, player_pos.y, float(PLAYER_SPRITE_WIDTH * scale), float(PLAYER_SPRITE_HEIGHT * scale)}, {0, 0}, 0, WHITE);
};