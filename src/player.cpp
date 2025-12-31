#include "player.hpp"

Player player;

enum Facing
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};
Facing facing;

void init_player()
{

    player.move_mode = 1;
    player.pos.x = PLAYER_START_MAP_POS_X;
    player.pos.y = PLAYER_START_MAP_POS_Y;
    player.max_animation_frames = 12;
    player.current_animation_frame = 0;
    player.animation_frame_5 = 0;
    player.normal_hitbox = {player.pos.x, player.pos.y, float(PLAYER_HITBOX_WIDTH), float(PLAYER_HITBOX_HEIGHT)};
    player.tex = LoadTexture(PLAYER_TEX_PATH);
};

void update_player()
{
    // dont move at all - mostly for cutscenes
    if (player.move_mode == 0)
    {
        player.normal_hitbox = {
            player.pos.x + PLAYER_HITBOX_X_OFFSET,
            player.pos.y + PLAYER_HITBOX_Y_OFFSET,
            float(PLAYER_HITBOX_WIDTH),
            float(PLAYER_HITBOX_HEIGHT)};
    }
    // full collision movement
    if (player.move_mode == 1)
    {
        player.pos_x_save = player.pos.x;
        player.pos_y_save = player.pos.y;

        player.movement = {0, 0};

        // movement calculations with a seperate vector
        if (IsKeyDown(KEY_W))
            player.movement.y -= 1;
        if (IsKeyDown(KEY_S))
            player.movement.y += 1;
        if (IsKeyDown(KEY_A))
            player.movement.x -= 1;
        if (IsKeyDown(KEY_D))
            player.movement.x += 1;

        // animation array calculations
        if (player.movement.y < 0)
        {
            facing = UP;
            player.current_anim_arr = player_walk_up;
            if (player.max_animation_frames != 12)
            {
                player.current_animation_frame = 0;
                player.max_animation_frames = 12;
            }
        }
        else if (player.movement.y > 0)
        {
            facing = DOWN;
            player.current_anim_arr = player_walk_down;
            if (player.max_animation_frames != 12)
            {
                player.current_animation_frame = 0;
                player.max_animation_frames = 12;
            }
        }
        else if (player.movement.x > 0)
        {
            facing = RIGHT;
            player.current_anim_arr = player_walk_right;
            if (player.max_animation_frames != 8)
            {
                player.current_animation_frame = 0;
                player.max_animation_frames = 8;
            }
        }
        else if (player.movement.x < 0)
        {
            facing = LEFT;
            player.current_anim_arr = player_walk_left;
            if (player.max_animation_frames != 8)
            {
                player.current_animation_frame = 0;
                player.max_animation_frames = 8;
            }
        }

        // idle animation calculations
        if (player.movement.x == 0 && player.movement.y == 0)
        {
            if (facing == UP)
            {
                player.current_anim_arr = player_idle_up_arr;
                if (player.max_animation_frames != 1)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 1;
                }
            }
            if (facing == DOWN)
            {
                player.current_anim_arr = player_idle_down_arr;
                if (player.max_animation_frames != 1)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 1;
                }
            }
            if (facing == RIGHT)
            {
                player.current_anim_arr = player_idle_right_arr;
                if (player.max_animation_frames != 1)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 1;
                }
            }
            if (facing == LEFT)
            {
                player.current_anim_arr = player_idle_left_arr;
                if (player.max_animation_frames != 1)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 1;
                }
            }
        }

        // normalize diagonal movement
        if (player.movement.x != 0 || player.movement.y != 0)
        {
            player.movement = Vector2Normalize(player.movement);

            player.pos.x += player.movement.x * PLAYER_SPEED;

            // player hitbox rebuild
            player.normal_hitbox = {
                player.pos.x + PLAYER_HITBOX_X_OFFSET,
                player.pos.y + PLAYER_HITBOX_Y_OFFSET,
                float(PLAYER_HITBOX_WIDTH),
                float(PLAYER_HITBOX_HEIGHT)};
            // horizontal collision check
            for (const Rectangle &r : collision_rects)
            {
                if (CheckCollisionRecs(player.normal_hitbox, r))
                {
                    player.pos.x = player.pos_x_save;
                    break;
                }
            }
            player.pos.y += player.movement.y * PLAYER_SPEED;
            // player hitbox rebuild
            player.normal_hitbox = {
                player.pos.x + PLAYER_HITBOX_X_OFFSET,
                player.pos.y + PLAYER_HITBOX_Y_OFFSET,
                float(PLAYER_HITBOX_WIDTH),
                float(PLAYER_HITBOX_HEIGHT)};
            // vertical collision check
            for (const Rectangle &r : collision_rects)
            {
                if (CheckCollisionRecs(player.normal_hitbox, r))
                {
                    player.pos.y = player.pos_y_save;
                    break;
                }
            }

            // making sure the player is at least inside the screen
            // i dont know why there is an 8 there - ???
            player.pos.x = Clamp(player.pos.x, -23, (map_to_load.width) - (PLAYER_SPRITE_WIDTH - 40));
            player.pos.y = Clamp(player.pos.y, -16, (map_to_load.height) - (PLAYER_SPRITE_HEIGHT - 12));
        }
    }

    // dont move and keep animation - for attacking
    // actually unexpectedly works!
    if (player.move_mode == 2)
    {
        player.normal_hitbox = {
            player.pos.x + PLAYER_HITBOX_X_OFFSET,
            player.pos.y + PLAYER_HITBOX_Y_OFFSET,
            float(PLAYER_HITBOX_WIDTH),
            float(PLAYER_HITBOX_HEIGHT)};
        if (player.current_animation_frame >= player.max_animation_frames - 1)
        {
            player.move_mode = 1;

            // player.current_animation_frame = 0;
        }
    }

    player.animation_frame_5++;
    if (player.animation_frame_5 >= ANIMATION_INTERVAL)
    {
        player.current_animation_frame++;
        if (player.current_animation_frame >= player.max_animation_frames)
        {
            player.current_animation_frame = 0;
        }
        player.animation_frame_5 = 0;
    }
    player.normal_hitbox = {
        player.pos.x + PLAYER_HITBOX_X_OFFSET,
        player.pos.y + PLAYER_HITBOX_Y_OFFSET,
        float(PLAYER_HITBOX_WIDTH),
        float(PLAYER_HITBOX_HEIGHT)};
    for (int i = 0; i < int(map_load_rects.size()); i++)
    {

        if (CheckCollisionRecs(player.normal_hitbox, map_load_rects[i].rect))
        {
            requested_player_pos = map_load_rects[i].spawnpoint;
            requested_map = Map_names(map_load_rects[i].map_to_load_struct);
        }
    }

    // item use for 3 slots
    if (!is_inv_open)
    {
        if (IsKeyPressed(KEY_Q))
        {

            if (inventory_slots[23].filled_with)
            {
                // implement item 1 usage here
                if (inventory_slots[23].filled_with->type == COMBAT_MELEE)
                {
                    // TODO: implement item use!

                    if (facing == DOWN)
                    {
                        player.current_anim_arr = player_sword_slash_down_arr;
                    }
                    if (facing == UP)
                    {
                        player.current_anim_arr = player_sword_slash_up_arr;
                    }
                    if (facing == LEFT)
                    {
                        player.current_anim_arr = player_sword_slash_left_arr;
                    }
                    if (facing == RIGHT)
                    {
                        player.current_anim_arr = player_sword_slash_right_arr;
                    }
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 5;
                    player.move_mode = 2;
                }
                if (inventory_slots[23].filled_with->type == COMBAT_RANGED)
                {
                }
                if (inventory_slots[25].filled_with->type == SHEILD)
                {
                }
                if (inventory_slots[23].filled_with->type == QUEST_ITEM)
                {
                }
                if (inventory_slots[23].filled_with->type == CONSUMABLE)
                {
                }
                if (inventory_slots[23].filled_with->type == DUNGEON)
                {
                }
            }
            else
            {
            }
        }
        else if (IsKeyPressed(KEY_E))
        {
            if (inventory_slots[24].filled_with)
            {
                // implement item 2 usage here
                if (inventory_slots[24].filled_with->type == COMBAT_MELEE)
                {
                    

                    if (facing == DOWN)
                    {
                        player.current_anim_arr = player_sword_slash_down_arr;
                    }
                    if (facing == UP)
                    {
                        player.current_anim_arr = player_sword_slash_up_arr;
                    }
                    if (facing == LEFT)
                    {
                        player.current_anim_arr = player_sword_slash_left_arr;
                    }
                    if (facing == RIGHT)
                    {
                        player.current_anim_arr = player_sword_slash_right_arr;
                    }
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 5;
                    player.move_mode = 2;
                }
                if (inventory_slots[24].filled_with->type == COMBAT_RANGED)
                {
                }
                if (inventory_slots[25].filled_with->type == SHEILD)
                {
                }
                if (inventory_slots[24].filled_with->type == QUEST_ITEM)
                {
                }
                if (inventory_slots[24].filled_with->type == CONSUMABLE)
                {
                }
                if (inventory_slots[24].filled_with->type == DUNGEON)
                {
                }
            }
            else
            {
            }
        }
        else if (IsKeyPressed(KEY_Z))
        {
            if (inventory_slots[25].filled_with)
            {
                // implement item 3 usage here
                if (inventory_slots[25].filled_with->type == COMBAT_MELEE)
                {
                    

                    if (facing == DOWN)
                    {
                        player.current_anim_arr = player_sword_slash_down_arr;
                    }
                    if (facing == UP)
                    {
                        player.current_anim_arr = player_sword_slash_up_arr;
                    }
                    if (facing == LEFT)
                    {
                        player.current_anim_arr = player_sword_slash_left_arr;
                    }
                    if (facing == RIGHT)
                    {
                        player.current_anim_arr = player_sword_slash_right_arr;
                    }
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 5;
                    player.move_mode = 2;
                }
                if (inventory_slots[25].filled_with->type == COMBAT_RANGED)
                {
                }
                if (inventory_slots[25].filled_with->type == SHEILD)
                {
                }
                if (inventory_slots[25].filled_with->type == QUEST_ITEM)
                {
                }
                if (inventory_slots[25].filled_with->type == CONSUMABLE)
                {
                }
                if (inventory_slots[25].filled_with->type == DUNGEON)
                {
                }
            }
            else
            {
            }
        }
    }

    // animation thingy

    // std::cout << player.pos.x << "  " << player.pos.y << "\n";
}

void draw_player()
{
    DrawTexturePro(player.tex, player.current_anim_arr[player.current_animation_frame], {player.pos.x * scale, player.pos.y * scale, float(PLAYER_SPRITE_WIDTH * scale), float(PLAYER_SPRITE_HEIGHT * scale)}, {0, 0}, 0, WHITE);
};
