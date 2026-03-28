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
    player.collision_rect = {player.pos.x, player.pos.y, float(PLAYER_COLLISION_RECT_WIDTH), float(PLAYER_COLLISION_RECT_HEIGHT)};
    player.hitbox = {player.pos.x+PLAYER_HITBOX_X_OFFSET, player.pos.y+PLAYER_HITBOX_Y_OFFSET, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT};
    player.tex = get_texture(PLAYER_TEX_PATH);
    player.active_attack_hitbox = {};
    player.speed = PLAYER_WALK_SPEED;
    player.max_stamina = PLAYER_DEFAULT_MAX_STAMINA;
    player.current_stamina = PLAYER_DEFAULT_MAX_STAMINA;
    player.reloading_stamina = false;
    player.stamina_reload_timer = PLAYER_DEFAULT_STAMINA_RELOAD_TIME;
};

void rebuild_hitbox()
{
    player.collision_rect = {
        player.pos.x + PLAYER_COLLISION_RECT_X_OFFSET,
        player.pos.y + PLAYER_COLLISION_RECT_Y_OFFSET,
        float(PLAYER_COLLISION_RECT_WIDTH),
        float(PLAYER_COLLISION_RECT_HEIGHT)};
    player.hitbox = {
        player.pos.x+PLAYER_HITBOX_X_OFFSET, 
        player.pos.y+PLAYER_HITBOX_Y_OFFSET, 
        PLAYER_HITBOX_WIDTH, 
        PLAYER_HITBOX_HEIGHT};

    
    
}
// void change_animation_based_on_dir(int max_anim_frames, Rectangle *anim_arr, ){} //WIP

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

void damage_player_with_knockback(float damage, Vector2 damage_pos, float strength)
{
    
    if(player.can_take_damage){
        Vector2 dir = Vector2Subtract(player.pos, damage_pos);
        dir = Vector2Normalize(dir);
        player.knockback_vel = Vector2Scale(dir, strength);
        player.knockback_vel = Vector2Scale(player.knockback_vel, 0.85f);
        player.knockback_time = 0.2f; // duration in seconds
    }
    damage_player(damage);
};

void update_knockback(){
    
    Vector2 new_pos = Vector2Add(player.pos, Vector2Scale(player.knockback_vel, GetFrameTime()));

    // try X
    player.pos.x = new_pos.x;
    rebuild_hitbox();
    for(Rectangle &r : game.collision_rects){
        if (CheckCollisionRecs(player.collision_rect, r)) player.pos.x = player.pos_save.x;
    }
    // try Y
    player.pos.y = new_pos.y;
    rebuild_hitbox();
    for(Rectangle &r : game.collision_rects){
        if (CheckCollisionRecs(player.collision_rect, r)) player.pos.y = player.pos_save.y;
    }

    // decay the velocity 
    player.knockback_vel = Vector2Lerp(player.knockback_vel, {0, 0}, GetFrameTime() * 10);

    player.knockback_time -= GetFrameTime();
    
    
}

void damage_player(float damage)
{
    if (!player.can_take_damage)
        return;
    if (player.can_take_damage)
    {
        // implement damage taking here
        start_screen_shake(0.2, 8);
        PlaySound(game.sfx_manager[SFX_ids::DAMAGE_PLAYER]);
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


// you can basically copy/paste these 3

void item_combat_melee_stuff(Item* item, int slot){
    player.current_stamina -= PLAYER_SWORD_SWING_STAMINA_DEGEN;
    float pitch_rand = (rand() % 10)+1;
    pitch_rand /= 10;
    SetSoundPitch(game.sfx_manager[SFX_ids::PLAYER_SWING_SWORD], pitch_rand+1);
    PlaySound(game.sfx_manager[SFX_ids::PLAYER_SWING_SWORD]); 
    // std::cout << player.facing << "\n";
    switch(player.facing){
        case DOWN:
        {
            player.current_anim_arr = player_sword_slash_down_arr;
            player.active_attack_hitbox = {player.pos.x + 16, player.pos.y + 32, 32, 32};
            player.active_damage = item->melee.damage;
            break;
        }
        case UP:
        {
            player.current_anim_arr = player_sword_slash_up_arr;
            player.active_attack_hitbox = {player.pos.x + 16, player.pos.y, 32, 32};
            player.active_damage = item->melee.damage;
            break;
        }
        case LEFT:
        {
            player.current_anim_arr = player_sword_slash_left_arr;
            player.active_attack_hitbox = {player.pos.x, player.pos.y, 32, 64};
            player.active_damage = item->melee.damage;
            break;
        }
        case RIGHT:
        {
            player.current_anim_arr = player_sword_slash_right_arr;
            player.active_attack_hitbox = {player.pos.x+32, player.pos.y, 32, 64};
            player.active_damage = item->melee.damage;
            break;
        }
        default:{
            player.current_anim_arr = player_sword_slash_down_arr;
            player.active_attack_hitbox = {player.pos.x + 16, player.pos.y + 32, 32, 32};
            player.active_damage = item->melee.damage;
            break;
        }
    }
    player.current_animation_frame = 0;
    player.max_animation_frames = 5;
    player.move_mode = 2;
}
void item_combat_ranged_stuff(Item* item, int slot){
    
}
void item_shield_stuff(Item* item, int slot){
    
}
void item_quest_item_stuff(Item* item, int slot){
    
}
void item_consumable_stuff(Item* item, int slot){
    switch(item->consumable.buff_type){
        case HEAL:
            if(player.current_health < player.max_health){
                player.current_health+=item->consumable.buff_strength;
                switch(player.facing){
                    case UP: 
                        player.current_anim_arr = player_consume_up;
                        break;
                    case DOWN:
                        player.current_anim_arr = player_consume_down;
                        break;
                    case RIGHT:
                        player.current_anim_arr = player_consume_right;
                        break;
                    case LEFT:
                        player.current_anim_arr = player_consume_left;
                        break;
                }
                player.max_animation_frames = 8;
                player.current_animation_frame = 0;
                player.move_mode = 2;
                item->consumable.amount--;
                if(item->consumable.amount==0){
                    inventory_slots[slot].filled_with = {};
                }
            }
            
            break;
        default:
            break;
    }
}
void item_dungeon_stuff(Item* item, int slot){
    
}

void use_item_in_slot(int slot){
    
    if (!inventory_slots[slot].filled_with) return;
    
    auto& item = *inventory_slots[slot].filled_with;
    // implement item 1 usage here
    switch(item.type){
        case COMBAT_MELEE: {
            item_combat_melee_stuff(&item, slot);
            break;
        }
        case COMBAT_RANGED: {
            item_combat_ranged_stuff(&item, slot);
            break;
        }
        case SHIELD: {
            item_shield_stuff(&item, slot);
            break;
        }
        case QUEST_ITEM: {
            item_quest_item_stuff(&item, slot);
            break;
        }
        case CONSUMABLE: {
            item_consumable_stuff(&item, slot);
            
            break;
        }
        case DUNGEON: {
            item_dungeon_stuff(&item, slot);
            break;
        }
        default: 
            break;
    }
    
    
}

void frozen_player_movement(){
    player.current_animation_frame = 0;
    player.max_animation_frames = 1;
    switch(player.facing){
        case DOWN: {
            player.current_anim_arr = player_idle_down_arr;
            game.wanted_cam_pos.y = player.pos.y - ((WINDOW_HEIGHT) / 2) + (DEFAULT_SPRITE_HEIGHT/2);
            game.wanted_cam_pos.x = player.pos.x - ((WINDOW_WIDTH) / 2) + (DEFAULT_SPRITE_WIDTH/2);
            break;
        }
            
        case UP: {
            player.current_anim_arr = player_idle_up_arr;
            game.wanted_cam_pos.y = player.pos.y - ((WINDOW_HEIGHT) / 2) + (DEFAULT_SPRITE_HEIGHT/2);
            game.wanted_cam_pos.x = player.pos.x - ((WINDOW_WIDTH) / 2) + (DEFAULT_SPRITE_WIDTH/2);
            break;
        }
        
        case LEFT: {
            player.current_anim_arr = player_idle_left_arr;
            game.wanted_cam_pos.x = player.pos.x - ((WINDOW_WIDTH) / 2) + (DEFAULT_SPRITE_WIDTH/2);
            game.wanted_cam_pos.y = player.pos.y - ((WINDOW_HEIGHT) / 2) + (DEFAULT_SPRITE_HEIGHT/2);
            break;
        }
        
        
        case RIGHT: {
            player.current_anim_arr = player_idle_right_arr;
            game.wanted_cam_pos.x = player.pos.x - ((WINDOW_WIDTH) / 2) + (DEFAULT_SPRITE_WIDTH/2);
            game.wanted_cam_pos.y = player.pos.y - ((WINDOW_HEIGHT) / 2) + (DEFAULT_SPRITE_HEIGHT/2);
            break;
        }
    }
        
    rebuild_hitbox();
}



void default_player_movement(){
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

    player.movement = Vector2Normalize(player.movement);
    // animation array calculations
    
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
        switch(player.facing){
            case UP:
            {
                player.current_anim_arr = player_idle_up_arr;
                if (player.max_animation_frames != 1)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 1;
                }
                break;
            }
            case DOWN:
            {
                player.current_anim_arr = player_idle_down_arr;
                if (player.max_animation_frames != 1)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 1;
                }
                break;
            }
            case RIGHT:
            {
                player.current_anim_arr = player_idle_right_arr;
                if (player.max_animation_frames != 1)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 1;
                }
                break;
                
            }
            case LEFT:
            {
                player.current_anim_arr = player_idle_left_arr;
                if (player.max_animation_frames != 1)
                {
                    player.current_animation_frame = 0;
                    player.max_animation_frames = 1;
                }
                break;
            }
        }
    }

    // normalize diagonal movement
    if (player.movement.x != 0 || player.movement.y != 0)
    {
        if(!IsSoundPlaying(game.sfx_manager[SFX_ids::PLAYER_FOOTSTEPS])){
            // std::cout <<"wow sound is playing!";
            float pitch_rand = (rand() % 10)/10.0f;
            // pitch_rand /= 100;
            SetSoundPitch(game.sfx_manager[SFX_ids::PLAYER_FOOTSTEPS], pitch_rand);
            PlaySound(game.sfx_manager[SFX_ids::PLAYER_FOOTSTEPS]); //do something bout this later. make it so sfx knows its playing
        }

        player.pos.x += player.movement.x * player.speed;

        // player hitbox rebuild
        rebuild_hitbox();
        // horizontal collision check
        for (const Rectangle &r : game.collision_rects)
        {
            if (!CheckCollisionRecs(player.collision_rect, r)) continue;
            
            player.pos.x = player.pos_save.x;
            // break;
        }
        for (const Locked_rect &l : game.locked_rects)
        {
            if (!CheckCollisionRecs(player.collision_rect, l.rect)) continue;
            
            player.pos.x = player.pos_save.x;
            if(player.dungeon_keys > 0){
                PlaySound(game.sfx_manager[SFX_ids::UNLOCK_DOOR]);
                player.dungeon_keys--;
                remove_locked_rect(l);
                player.unlocked_doors.push_back(l.name);
            }
            // break;
            
            
            
        }
        player.pos.y += player.movement.y * player.speed;
        // player hitbox rebuild
        rebuild_hitbox();
        // vertical collision check
        for (const Rectangle &r : game.collision_rects)
        {
            if (!CheckCollisionRecs(player.collision_rect, r)) continue;
            
            player.pos.y = player.pos_save.y;
                // break;
            
        }
        for (const Locked_rect &l : game.locked_rects)
        {
            if (!CheckCollisionRecs(player.collision_rect, l.rect)) continue;
            
            player.pos.y = player.pos_save.y;
            if(player.dungeon_keys > 0){
                PlaySound(game.sfx_manager[SFX_ids::UNLOCK_DOOR]);
                player.dungeon_keys--;
                remove_locked_rect(l);
                player.unlocked_doors.push_back(l.name);
            }
            
                
            
            
        }
        // making sure the player is at least inside the screen
        // i dont know why there is an 8 there - ???
        player.pos.x = Clamp(player.pos.x, -23, (game.map_to_load.width) - (DEFAULT_SPRITE_WIDTH - 40));
        player.pos.y = Clamp(player.pos.y, -16, (game.map_to_load.height) - (DEFAULT_SPRITE_HEIGHT - 12));
    }
    
    if (IsKeyPressed(KEY_ITEM_HOTBAR_1))
    {
        use_item_in_slot(23);
    }
    else if (IsKeyPressed(KEY_ITEM_HOTBAR_2))
    {
        use_item_in_slot(24);
    }
    else if (IsKeyPressed(KEY_ITEM_HOTBAR_3))
    {
        use_item_in_slot(25);
    }
}

void animation_player_movement(){
    rebuild_hitbox();
    if (player.current_animation_frame >= player.max_animation_frames - 1)
    {
        player.move_mode = 1;

        // player.current_animation_frame = 0;
    }
}

void update_player()
{
    if(player.active_attack_hitbox.x > 0 || player.active_attack_hitbox.y > 0 || player.active_attack_hitbox.width > 0 || player.active_attack_hitbox.height > 0){
        player.active_attack_hitbox = {0, 0, 0, 0};
    }
    player.pos_save = player.pos;
    if (player.knockback_time > 0.0f){ 
        update_knockback(); 
        return;
    }
    switch(player.move_mode){
        case 0: // dont move at all - mostly for cutscenes
            frozen_player_movement();
            break;
        // full collision movement
        case 1:
            default_player_movement();
            break;
        // dont move and keep animation - for attacking
        // actually unexpectedly works!
        case 2:
            animation_player_movement();
            break;
        
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
        
        
        if(!CheckCollisionRecs(player.collision_rect, {g.pos.x-ITEM_PICKUP_X_OFFSET, g.pos.y-ITEM_PICKUP_X_OFFSET, ITEM_PICKUP_RECT_WIDTH, ITEM_PICKUP_RECT_HEIGHT})) continue;
        PlaySound(game.sfx_manager[SFX_ids::PICKUP_ITEM]);
        g.picked_up = true;
        player.picked_up_items.push_back(g.ground_item_name);
        if(g.item.name == Item_names::DUNGEON_KEY){
            
            player.dungeon_keys++;
            continue;
        }
        add_item_to_inventory(g.item);
        
    }
    

    for (Load_rects &r : game.map_load_rects)
    {
        
        if (!CheckCollisionRecs(player.collision_rect, r.rect)) continue;
        
            //make way for it to not load if the map loads w/ u on top of it like zelda
           
        game.requested_player_pos = r.spawnpoint;
        game.requested_map = Map_names(r.map_to_load_struct);
            
        
    }
    
    player_stamina_update();
    
    
    // item use for 3 slots
    
    player_update_iframes();
    if(player.current_health > player.max_health){
        player.current_health = player.max_health;
    }
    if (player.current_health <= 0)
    {
        // implement game over screen or something here
        game.state = Game_states::PLAYER_GAME_OVER;
        CloseWindow();
        std::cout << "YOU LOSE!\n";
    }
    // animation thingy

    // std::cout << player.pos.x << "  " << player.pos.y << "\n";
}

void draw_player()
{
    DrawTexturePro(player.tex, player.current_anim_arr[player.current_animation_frame], {player.pos.x, player.pos.y, float(DEFAULT_SPRITE_WIDTH), float(DEFAULT_SPRITE_HEIGHT)}, {0, 0}, 0, WHITE); 
    // DrawRectangle(player.hitbox.x, player.hitbox.y, player.hitbox.width, player.hitbox.height, RED);
};
