#include "player.hpp"

Player player;



void init_player()
{
    //make the health stuff in constants later
    player.current_health = 3.0f;
    player.max_health = 3.0f;
    player.active_damage = 0;
    player.move_mode = 1;
    player.pos.x = 0;
    player.pos.y = 0;
    player.current_anim_arr = player_idle_down_arr;
    player.max_animation_frames = 1;
    player.current_animation_frame = 0;
    player.animation_frame_5 = 0;
    player.normal_hitbox = {player.pos.x, player.pos.y, float(PLAYER_HITBOX_WIDTH), float(PLAYER_HITBOX_HEIGHT)};
    player.tex = LoadTexture(PLAYER_TEX_PATH);
    player.attack_hitbox = {};
    player.speed = PLAYER_WALK_SPEED;
    player.max_stamina = PLAYER_DEFAULT_MAX_STAMINA;
    player.current_stamina = PLAYER_DEFAULT_MAX_STAMINA;
    player.reloading_stamina = false;
    player.stamina_reload_timer = PLAYER_DEFAULT_STAMINA_RELOAD_TIME;
    player.taking_knockback = false;
};

void player_stamina_update(){
    if(player.current_stamina < 0){
        player.current_stamina = 0;
        player.reloading_stamina = true;
    }


    if(player.reloading_stamina){
        player.current_stamina += PLAYER_DEFAULT_STAMINA_REGEN;
        
    }

    else if(player.stamina_reload_timer < 0){
        player.stamina_reload_timer = 0;
        player.current_stamina += PLAYER_DEFAULT_STAMINA_REGEN;
    }
    
    if(player.current_stamina > player.max_stamina){
        player.stamina_reload_timer = PLAYER_DEFAULT_STAMINA_RELOAD_TIME;
        player.current_stamina = player.max_stamina;
        player.reloading_stamina = false;
    }
};

void damage_player_with_knockback(float damage, Vector2 damage_pos)
{
    damage_player(damage);
    player.taking_knockback = true;
    player.knockback_origin = damage_pos;
};

void update_knockback(){
    if(player.taking_knockback){
        player.move_mode = 0;
        player.pos = Vector2Lerp(player.pos, player.knockback_origin, 0.1);
        if(CheckCollisionRecs(player.normal_hitbox, {player.knockback_origin.x+PLAYER_HITBOX_X_OFFSET, player.knockback_origin.y+PLAYER_HITBOX_Y_OFFSET, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT})){
            player.taking_knockback = false;
            player.move_mode = 1;
        }
    }
    else{
        
    }
}

void damage_player(float damage)
{
    if (!player.can_take_damage)
        return;
    if (player.can_take_damage)
    {
        // implement damage taking here
        start_screen_shake(0.2, 8);
        PlaySound(sound_effects[SFX::DAMAGE_PLAYER]);
        player.current_health -= damage;
        if (player.current_health < 0)
        {
            player.current_health = 0;
        }
        player.can_take_damage = false;
        player.iframe_timer = PLAYER_IFRAME_TIME;
    }
};

void player_update_iframes()
{
    if (!player.can_take_damage)
    {
        player.iframe_timer -= GetFrameTime();
        if (player.iframe_timer <= 0.0f)
        {
            player.can_take_damage = true;
            player.iframe_timer = 0.0f;
        }
    }
}

void rebuild_hitbox()
{
    player.normal_hitbox = {
        player.pos.x + PLAYER_HITBOX_X_OFFSET,
        player.pos.y + PLAYER_HITBOX_Y_OFFSET,
        float(PLAYER_HITBOX_WIDTH),
        float(PLAYER_HITBOX_HEIGHT)};
}
// you can basically copy/paste these 3

void hotbar_slot_stuff(int slot){
    if (inventory_slots[slot].filled_with)
    {
        // implement item 1 usage here
        if (inventory_slots[slot].filled_with->type == COMBAT_MELEE)
        {
            player.current_stamina -= PLAYER_SWORD_SWING_STAMINA_DEGEN;
            float pitch_rand = (rand() % 10)+1;
            pitch_rand /= 10;
            SetSoundPitch(sound_effects[SFX::PLAYER_SWING_SWORD], pitch_rand+1);
            PlaySound(sound_effects[SFX::PLAYER_SWING_SWORD]); 
            // std::cout << player.facing << "\n";
            if (player.facing == DOWN)
            {
                player.current_anim_arr = player_sword_slash_down_arr;
                player.attack_hitbox = {player.pos.x + 16, player.pos.y + 32, 32, 32};
                player.active_damage = inventory_slots[slot].filled_with->melee.damage;
            }
            if (player.facing == UP)
            {
                player.current_anim_arr = player_sword_slash_up_arr;
                player.attack_hitbox = {player.pos.x + 16, player.pos.y, 32, 32};
                player.active_damage = inventory_slots[slot].filled_with->melee.damage;
            }
            if (player.facing == LEFT)
            {
                player.current_anim_arr = player_sword_slash_left_arr;
                player.attack_hitbox = {player.pos.x, player.pos.y, 32, 64};
                player.active_damage = inventory_slots[slot].filled_with->melee.damage;
            }
            if (player.facing == RIGHT)
            {
                player.current_anim_arr = player_sword_slash_right_arr;
                player.attack_hitbox = {player.pos.x+32, player.pos.y, 32, 64};
                player.active_damage = inventory_slots[slot].filled_with->melee.damage;
            }
            player.current_animation_frame = 0;
            player.max_animation_frames = 5;
            player.move_mode = 2;
            
        }
        if (inventory_slots[slot].filled_with->type == COMBAT_RANGED)
        {
        }
        if (inventory_slots[slot].filled_with->type == SHEILD)
        {
        }
        if (inventory_slots[slot].filled_with->type == QUEST_ITEM)
        {
        }
        if (inventory_slots[slot].filled_with->type == CONSUMABLE)
        {
        }
        if (inventory_slots[slot].filled_with->type == DUNGEON)
        {
        }
    }
    else
    {
    }
}



void update_player()
{
    if(player.attack_hitbox.x > 0 || player.attack_hitbox.y > 0 || player.attack_hitbox.width > 0 || player.attack_hitbox.height > 0){
        player.attack_hitbox = {0, 0, 0, 0};
    }
    // dont move at all - mostly for cutscenes
    update_knockback();
    if (player.move_mode == 0)
    {
        player.current_animation_frame = 0;
        player.max_animation_frames = 1;
        if (player.facing == DOWN){
            player.current_anim_arr = player_idle_down_arr;
            game.wanted_cam_pos.y = player.pos.y - ((WINDOW_HEIGHT) / 2) + (DEFAULT_SPRITE_HEIGHT/2);
            game.wanted_cam_pos.x = player.pos.x - ((WINDOW_WIDTH) / 2) + (DEFAULT_SPRITE_WIDTH/2);
        }
            
        if (player.facing == UP){
            player.current_anim_arr = player_idle_up_arr;
            game.wanted_cam_pos.y = player.pos.y - ((WINDOW_HEIGHT) / 2) + (DEFAULT_SPRITE_HEIGHT/2);
            game.wanted_cam_pos.x = player.pos.x - ((WINDOW_WIDTH) / 2) + (DEFAULT_SPRITE_WIDTH/2);
        }
        
        if (player.facing == LEFT){
            player.current_anim_arr = player_idle_left_arr;
            game.wanted_cam_pos.x = player.pos.x - ((WINDOW_WIDTH) / 2) + (DEFAULT_SPRITE_WIDTH/2);
            game.wanted_cam_pos.y = player.pos.y - ((WINDOW_HEIGHT) / 2) + (DEFAULT_SPRITE_HEIGHT/2);
        }
        
        
        if (player.facing == RIGHT){
            player.current_anim_arr = player_idle_right_arr;
            game.wanted_cam_pos.x = player.pos.x - ((WINDOW_WIDTH) / 2) + (DEFAULT_SPRITE_WIDTH/2);
            game.wanted_cam_pos.y = player.pos.y - ((WINDOW_HEIGHT) / 2) + (DEFAULT_SPRITE_HEIGHT/2);
        }
            
        rebuild_hitbox();
    }
    // full collision movement
    if (player.move_mode == 1)
    {
        player.pos_x_save = player.pos.x;
        player.pos_y_save = player.pos.y;

        player.movement = {0, 0};

        // movement calculations with a seperate vector
        if (IsKeyDown(KEY_CONTROLS_UP))
            player.movement.y -= 1;
        if (IsKeyDown(KEY_CONTROLS_DOWN))
            player.movement.y += 1;
        if (IsKeyDown(KEY_CONTROLS_LEFT))
            player.movement.x -= 1;
        if (IsKeyDown(KEY_CONTROLS_RIGHT))
            player.movement.x += 1;

        // animation array calculations
        if(player.movement.x != 0 || player.movement.y != 0){
            if(!IsSoundPlaying(sound_effects[SFX::PLAYER_FOOTSTEPS])){
                // std::cout <<"wow sound is playing!";
                float pitch_rand = (rand() % 10)/10.0f;
                // pitch_rand /= 100;
                SetSoundPitch(sound_effects[SFX::PLAYER_FOOTSTEPS], pitch_rand);
                PlaySound(sound_effects[SFX::PLAYER_FOOTSTEPS]); //do something bout this later. make it so sfx knows its playing
            }
        }
        if(!IsKeyDown(KEY_SPRINT) || player.reloading_stamina){
            player.stamina_reload_timer -= 2;
            if (player.movement.y < 0)
            {
                player.facing = UP;
                player.speed = PLAYER_WALK_SPEED;
                player.current_anim_arr = player_walk_up;
                if (player.max_animation_frames != 12)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 12;
                }
                
                
            }
            else if (player.movement.y > 0)
            {
                player.facing = DOWN;
                player.speed = PLAYER_WALK_SPEED;
                player.current_anim_arr = player_walk_down;
                if (player.max_animation_frames != 12)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 12;
                }
                
            }
            else if (player.movement.x > 0)
            {
                player.facing = RIGHT;
                player.speed = PLAYER_WALK_SPEED;
                player.current_anim_arr = player_walk_right;
                if (player.max_animation_frames != 8)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 8;
                }
                
            }
            else if (player.movement.x < 0)
            {
                player.facing = LEFT;
                player.speed = PLAYER_WALK_SPEED;
                player.current_anim_arr = player_walk_left;
                if (player.max_animation_frames != 8)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 8;
                }
                
            }
        }
        else if(IsKeyDown(KEY_SPRINT) && !player.reloading_stamina){
            player.stamina_reload_timer = PLAYER_DEFAULT_STAMINA_RELOAD_TIME;
            if (player.movement.y < 0)
            {
                player.current_stamina -= PLAYER_DEFAULT_STAMINA_DEGEN;
                player.facing = UP;
                player.speed = PLAYER_SPRINT_SPEED;
                player.current_anim_arr = player_sprint_up;
                if (player.max_animation_frames != 6)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 6;
                }
                
                
            }
            else if (player.movement.y > 0)
            {
                player.current_stamina -= PLAYER_DEFAULT_STAMINA_DEGEN;
                player.facing = DOWN;
                player.speed = PLAYER_SPRINT_SPEED;
                player.current_anim_arr = player_sprint_down;
                if (player.max_animation_frames != 6)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 6;
                }
                
            }
            else if (player.movement.x > 0)
            {
                player.current_stamina -= PLAYER_DEFAULT_STAMINA_DEGEN;
                player.facing = RIGHT;
                player.speed = PLAYER_SPRINT_SPEED;
                player.current_anim_arr = player_sprint_right;
                if (player.max_animation_frames != 8)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 8;
                }
                
            }
            else if (player.movement.x < 0)
            {
                player.current_stamina -= PLAYER_DEFAULT_STAMINA_DEGEN;
                player.facing = LEFT;
                player.speed = PLAYER_SPRINT_SPEED;
                player.current_anim_arr = player_sprint_left;
                if (player.max_animation_frames != 8)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 8;
                }
                
            }
        }

        // idle animation calculations
        if (player.movement.x == 0 && player.movement.y == 0)
        {
            if (player.facing == UP)
            {
                player.current_anim_arr = player_idle_up_arr;
                if (player.max_animation_frames != 1)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 1;
                }
                
            }
            if (player.facing == DOWN)
            {
                player.current_anim_arr = player_idle_down_arr;
                if (player.max_animation_frames != 1)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 1;
                }
                
            }
            if (player.facing == RIGHT)
            {
                player.current_anim_arr = player_idle_right_arr;
                if (player.max_animation_frames != 1)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 1;
                }
                
            }
            if (player.facing == LEFT)
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

            player.pos.x += player.movement.x * player.speed;

            // player hitbox rebuild
            rebuild_hitbox();
            // horizontal collision check
            for (const Rectangle &r : game.collision_rects)
            {
                if (CheckCollisionRecs(player.normal_hitbox, r))
                {
                    player.pos.x = player.pos_x_save;
                    break;
                }
            }
            for (const Locked_rect &l : game.locked_rects)
            {
                if (CheckCollisionRecs(player.normal_hitbox, l.rect) && player.dungeon_keys <= 0)
                {
                    player.pos.x = player.pos_x_save;
                    if(player.dungeon_keys > 0){
                        player.dungeon_keys--;
                        remove_locked_rect(l);
                        player.unlocked_doors.push_back(l.name);
                    }
                    break;
                    
                }
                
            }
            player.pos.y += player.movement.y * player.speed;
            // player hitbox rebuild
            rebuild_hitbox();
            // vertical collision check
            for (const Rectangle &r : game.collision_rects)
            {
                if (CheckCollisionRecs(player.normal_hitbox, r))
                {
                    player.pos.y = player.pos_y_save;
                    break;
                }
            }
            for (const Locked_rect &l : game.locked_rects)
            {
                if (CheckCollisionRecs(player.normal_hitbox, l.rect))
                {
                    player.pos.y = player.pos_y_save;
                    if(player.dungeon_keys > 0){
                        PlaySound(sound_effects[SFX::UNLOCK_DOOR]);
                        player.dungeon_keys--;
                        remove_locked_rect(l);
                        player.unlocked_doors.push_back(l.name);
                    }
                    break;
                    
                }
                
            }
            // making sure the player is at least inside the screen
            // i dont know why there is an 8 there - ???
            player.pos.x = Clamp(player.pos.x, -23, (game.map_to_load.width) - (DEFAULT_SPRITE_WIDTH - 40));
            player.pos.y = Clamp(player.pos.y, -16, (game.map_to_load.height) - (DEFAULT_SPRITE_HEIGHT - 12));
        }
        
        if (IsKeyPressed(KEY_ITEM_HOTBAR_1))
        {
            hotbar_slot_stuff(23);
        }
        else if (IsKeyPressed(KEY_ITEM_HOTBAR_2))
        {
            hotbar_slot_stuff(24);
        }
        else if (IsKeyPressed(KEY_ITEM_HOTBAR_3))
        {
            hotbar_slot_stuff(25);
        }
        
    }

    // dont move and keep animation - for attacking
    // actually unexpectedly works!
    if (player.move_mode == 2)
    {
        rebuild_hitbox();
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
    rebuild_hitbox();
    for(Ground_item &g : game.ground_items){
        
        
        if(CheckCollisionRecs(player.normal_hitbox, {g.pos.x-ITEM_PICKUP_X_OFFSET, g.pos.y-ITEM_PICKUP_X_OFFSET, ITEM_PICKUP_RECT_WIDTH, ITEM_PICKUP_RECT_HEIGHT})){
            PlaySound(sound_effects[SFX::PICKUP_ITEM]);
            g.picked_up = true;
            player.picked_up_items.push_back(g.ground_item_name);
            if(g.item.name == DUNGEON_KEY){
                
                player.dungeon_keys++;
                continue;
            }
            add_item_to_inventory(g.item);
        }
    }
    

    for (Load_rects &r : game.map_load_rects)
    {
        
        if (CheckCollisionRecs(player.normal_hitbox, r.rect))
        {
            //make way for it to not load if the map loads w/ u on top of it like zelda
           
                game.requested_player_pos = r.spawnpoint;
                game.requested_map = Map_names(r.map_to_load_struct);
            
        }
    }
    
    player_stamina_update();
    
    
    // item use for 3 slots
    
    player_update_iframes();
    
    if (player.current_health <= 0)
    {
        // implement game over screen or something here
        CloseWindow();
        std::cout << "YOU LOSE!\n";
    }
    // animation thingy

    // std::cout << player.pos.x << "  " << player.pos.y << "\n";
}

void draw_player()
{
    DrawTexturePro(player.tex, player.current_anim_arr[player.current_animation_frame], {player.pos.x, player.pos.y, float(DEFAULT_SPRITE_WIDTH), float(DEFAULT_SPRITE_HEIGHT)}, {0, 0}, 0, WHITE); 
    // DrawRectangle(player.attack_hitbox.x*scale, player.attack_hitbox.y*scale, player.attack_hitbox.width*scale, player.attack_hitbox.height*scale, RED);
};
