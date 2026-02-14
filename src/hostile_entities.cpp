#include "hostile_entities.hpp"

// should probably put this somewhere
Texture2D Enemy_forest_scourge::shared_tex = {};
bool Enemy_forest_scourge::texture_loaded = false;


void unload_enemy_textures()
{
    // add all the enemy textures that spawn more than one per map, call when loading map, in reset_loaded
    if (Enemy_forest_scourge::texture_loaded)
    {
        UnloadTexture(Enemy_forest_scourge::shared_tex);
        Enemy_forest_scourge::texture_loaded = false;
    }
}

Enemy_forest_scourge::Enemy_forest_scourge()
{
    hit_flash_timer = 0.0f;
    health = FOREST_SCOURGE_HEALTH;
    can_take_damage = true;
    iframe_timer = 0.0f;
    current_anim_arr = forest_scourge_walk_down_right;
    max_animation_frames = 7;
    current_animation_frame = 0;
    animation_frame_5 = 0;
    dead = false;
    health = FOREST_SCOURGE_HEALTH;
    direction = DOWN_RIGHT;
    wander_state = 1;
    pos = {0, 0};
    rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
    chase_detect_rect = {pos.x - FOREST_SCOURGE_CHASE_DETECT_OFFSET_X, pos.y - FOREST_SCOURGE_CHASE_DETECT_OFFSET_Y, FOREST_SCOURGE_CHASE_DETECT_WIDTH, FOREST_SCOURGE_CHASE_DETECT_HEIGHT};
    attack_detect_rect = {pos.x + FOREST_SCOURGE_ATTACK_DETECT_OFFSET_X, pos.y + FOREST_SCOURGE_ATTACK_DETECT_OFFSET_Y, FOREST_SCOURGE_ATTACK_DETECT_WIDTH, FOREST_SCOURGE_ATTACK_DETECT_HEIGHT};
    attack_hit_rect = {};
    move_mode = 1;
}

Enemy_forest_scourge::~Enemy_forest_scourge()
{
    // really put nothing here - ???
}

void Enemy_forest_scourge::load()
{
    if (!texture_loaded)
    {
        shared_tex = LoadTexture(
            "gfx/enemies/forest_scourge/forest_scourge_tex.png");
        texture_loaded = true;
    }
    if (current_map == DARK_FOREST_SOUTH)
    {
        random_index = rand() % 6;
        switch (random_index)
        {
        case 0:

            pos = FOREST_SCOURGE_DFS_POS_1;

            break;
        case 1:

            pos = FOREST_SCOURGE_DFS_POS_2;

            break;
        case 2:

            pos = FOREST_SCOURGE_DFS_POS_3;

            break;
        case 3:

            pos = FOREST_SCOURGE_DFS_POS_4;

            break;
        case 4:

            pos = FOREST_SCOURGE_DFS_POS_5;

            break;
        case 5:

            pos = FOREST_SCOURGE_DFS_POS_6;

            break;
        default:

            pos = FOREST_SCOURGE_DFS_POS_1;

            break;
        }
    }
    if (current_map == DARK_FOREST_NORTH)
    {
        random_index = rand() % 6;
        switch (random_index)
        {
        case 0:

            pos = FOREST_SCOURGE_DFN_POS_1;

            break;
        case 1:

            pos = FOREST_SCOURGE_DFN_POS_2;

            break;
        case 2:

            pos = FOREST_SCOURGE_DFN_POS_3;

            break;
        case 3:

            pos = FOREST_SCOURGE_DFN_POS_4;

            break;
        case 4:

            pos = FOREST_SCOURGE_DFN_POS_5;

            break;
        case 5:

            pos = FOREST_SCOURGE_DFN_POS_6;

            break;
        default:

            pos = FOREST_SCOURGE_DFN_POS_1;

            break;
        }
    }
    if (current_map == DARK_FOREST_CENTER)
    {
        random_index = rand() % 11;
        switch (random_index)
        {
        case 0:
            pos = FOREST_SCOURGE_DFC_POS_1;
            break;
        case 1:
            pos = FOREST_SCOURGE_DFC_POS_2;
            break;
        case 2:
            pos = FOREST_SCOURGE_DFC_POS_3;
            break;
        case 3:
            pos = FOREST_SCOURGE_DFC_POS_4;
            break;
        case 4:
            pos = FOREST_SCOURGE_DFC_POS_5;
            break;
        case 5:
            pos = FOREST_SCOURGE_DFC_POS_6;
            break;
        case 6:
            pos = FOREST_SCOURGE_DFC_POS_7;
            break;
        case 7:
            pos = FOREST_SCOURGE_DFC_POS_8;
            break;
        case 8:
            pos = FOREST_SCOURGE_DFC_POS_9;
            break;
        case 9:
            pos = FOREST_SCOURGE_DFC_POS_10;
            break;
        case 10:
            pos = FOREST_SCOURGE_DFC_POS_11;
            break;
        default:
            pos = FOREST_SCOURGE_DFC_POS_1;
            break;
        }
    }
    originial_pos = pos;
}

void Enemy_forest_scourge::update()
{

    if (health <= 0)
    {
        dead = true;
    }
    animation_frame_5++;
    if (animation_frame_5 >= ANIMATION_INTERVAL)
    {
        current_animation_frame++;
        if (current_animation_frame >= max_animation_frames)
        {
            current_animation_frame = 0;
        }
        animation_frame_5 = 0;
    }
    if (hit_flash_timer > 0.0f)
        hit_flash_timer -= GetFrameTime();
    rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
    chase_detect_rect = {pos.x - FOREST_SCOURGE_CHASE_DETECT_OFFSET_X, pos.y - FOREST_SCOURGE_CHASE_DETECT_OFFSET_Y, FOREST_SCOURGE_CHASE_DETECT_WIDTH, FOREST_SCOURGE_CHASE_DETECT_HEIGHT};
    attack_detect_rect = {pos.x + FOREST_SCOURGE_ATTACK_DETECT_OFFSET_X, pos.y + FOREST_SCOURGE_ATTACK_DETECT_OFFSET_Y, FOREST_SCOURGE_ATTACK_DETECT_WIDTH, FOREST_SCOURGE_ATTACK_DETECT_HEIGHT};
    pos.x = Clamp(pos.x, 0, map_to_load.width - DEFAULT_SPRITE_WIDTH);
    pos.y = Clamp(pos.y, 0, map_to_load.height - DEFAULT_SPRITE_HEIGHT);

    if (!can_take_damage)
    {
        iframe_timer -= GetFrameTime();
        if (iframe_timer <= 0.0f)
        {
            can_take_damage = true;
            iframe_timer = 0.0f;
        }
    }

    decide_action();
}

void Enemy_forest_scourge::draw()
{
    DrawTexturePro(shared_tex, current_anim_arr[current_animation_frame], {pos.x, pos.y, float(DEFAULT_SPRITE_WIDTH), float(DEFAULT_SPRITE_HEIGHT)}, {0, 0}, 0, hit_flash_timer > 0.0f ? RED : WHITE);
}

void Enemy_forest_scourge::take_damage(float damage, Vector2 hit_source_pos)
{
    if (!can_take_damage)
        return;
    if (can_take_damage)
    {
        // implement knockback
        start_hitstop(player.active_damage);
        health -= damage;
        hit_flash_timer = HIT_FLASH_TIME;
        if (health < 0)
        {
            health = 0;
        }
        can_take_damage = false;
        iframe_timer = ENEMY_IFRAME_TIME;
        start_hitstop(player.active_damage);
        Vector2 dir = Vector2Normalize(
            Vector2Subtract(pos, hit_source_pos));

        pos = Vector2Add(pos, Vector2Scale(dir, KNOCKBACK_DIST));
    }
}

void Enemy_forest_scourge::wander()
{
    wander_timer -= GetFrameTime();

    // If timer expired OR direction is zero, pick a new direction
    if (wander_timer <= 0.0f || (wander_dir.x == 0 && wander_dir.y == 0))
    {
        int dir = rand() % 4;

        switch (dir)
        {
        case 0: wander_dir = { -1,  0 }; break; // left
        case 1: wander_dir = {  1,  0 }; break; // right
        case 2: wander_dir = {  0,  1 }; break; // down
        case 3: wander_dir = {  0, -1 }; break; // up
        }

        wander_timer = (float)(rand() % 200 + 200) / 100.0f; 
        // 2.0 to 4.0 seconds
    }

    Vector2 pos_save = pos;

    // Move
    pos.x += wander_dir.x * FOREST_SCOURGE_SPEED;
    pos.y += wander_dir.y * FOREST_SCOURGE_SPEED;

    // Update hitbox
    Rectangle test_rect = {
        pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X,
        pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y,
        FOREST_SCOURGE_HITBOX_WIDTH,
        FOREST_SCOURGE_HITBOX_HEIGHT
    };

    // Check collision
    for (Rectangle &r : collision_rects)
    {
        if (CheckCollisionRecs(test_rect, r))
        {
            pos = pos_save;

            // force new direction immediately
            wander_timer = 0.0f;
            return;
        }
    }

    // Clamp using hitbox
    float minX = -FOREST_SCOURGE_HITBOX_OFFSET_X;
    float maxX = map_to_load.width
                 - FOREST_SCOURGE_HITBOX_WIDTH
                 - FOREST_SCOURGE_HITBOX_OFFSET_X;

    float minY = -FOREST_SCOURGE_HITBOX_OFFSET_Y;
    float maxY = map_to_load.height
                 - FOREST_SCOURGE_HITBOX_HEIGHT
                 - FOREST_SCOURGE_HITBOX_OFFSET_Y;

    pos.x = Clamp(pos.x, minX, maxX);
    pos.y = Clamp(pos.y, minY, maxY);

    // Set animation based on vertical direction
    if (wander_dir.y < 0)
        current_anim_arr = forest_scourge_walk_up_left;
    else
        current_anim_arr = forest_scourge_walk_down_right;

    max_animation_frames = 7;
}

void Enemy_forest_scourge::chase()
{
     wander_state = 0;

    // Calculate direction vector to player
    Vector2 to_player = Vector2Subtract(player.pos, pos);
    float distance = Vector2Length(to_player);

    Vector2 move = {0.0f, 0.0f};

    if (distance > 0.0f)
    {
        // Normalize and scale by speed and frame time
        Vector2 dir = Vector2Scale(to_player, 1.0f / distance);
        move = Vector2Scale(dir, FOREST_SCOURGE_CHASE_SPEED * GetFrameTime());
    }

    // Save old position for collision rollback
    Vector2 old_pos = pos;

    // --- Move X axis and check collisions ---
    pos.x += move.x;
    rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y,
            FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};

    for (const Rectangle &r : collision_rects)
    {
        if (CheckCollisionRecs(rect, r))
        {
            pos.x = old_pos.x; // rollback
            break;
        }
    }

    // --- Move Y axis and check collisions ---
    pos.y += move.y;
    rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y,
            FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};

    for (const Rectangle &r : collision_rects)
    {
        if (CheckCollisionRecs(rect, r))
        {
            pos.y = old_pos.y; // rollback
            break;
        }
    }

    // Clamp to map boundaries
    pos.x = Clamp(pos.x, -FOREST_SCOURGE_HITBOX_OFFSET_X, map_to_load.width - FOREST_SCOURGE_HITBOX_WIDTH - FOREST_SCOURGE_HITBOX_OFFSET_X);
    pos.y = Clamp(pos.y, -FOREST_SCOURGE_HITBOX_OFFSET_Y, map_to_load.height - FOREST_SCOURGE_HITBOX_HEIGHT - FOREST_SCOURGE_HITBOX_OFFSET_Y);

    // --- Set animation based on direction ---
    if (fabs(move.x) > fabs(move.y))
    {
        // Horizontal movement dominates
        if (move.x > 0)
            current_anim_arr = forest_scourge_walk_down_right;
        else
            current_anim_arr = forest_scourge_walk_up_left;
    }
    else
    {
        // Vertical movement dominates
        if (move.y > 0)
            current_anim_arr = forest_scourge_walk_down_right;
        else
            current_anim_arr = forest_scourge_walk_up_left;
    }

    max_animation_frames = 7;
}

void Enemy_forest_scourge::attack()
{

    current_anim_arr = forest_scourge_attack_down_right;
    max_animation_frames = 6;
    attack_hit_rect = {pos.x + FOREST_SCOURGE_ATTACK_DETECT_OFFSET_X, pos.y + FOREST_SCOURGE_ATTACK_DETECT_OFFSET_X, FOREST_SCOURGE_ATTACK_WIDTH, FOREST_SCOURGE_ATTACK_HEIGHT};
    if (CheckCollisionRecs(attack_hit_rect, player.normal_hitbox))
    {
        damage_player(FOREST_SCOURGE_DAMAGE);
    }
}

void Enemy_forest_scourge::run_away()
{
    // might not implement - maybe on a more intellegent enemy?
}

void Enemy_forest_scourge::decide_action()
{
    if (move_mode == 0)
    {
    }
    if (move_mode == 1)
    {
        if (CheckCollisionRecs(rect, player.attack_hitbox))
        {
            // make a player.active_damage thing or whatever
            take_damage(player.active_damage, player.pos);
        }
        else if (CheckCollisionRecs(chase_detect_rect, player.normal_hitbox))
        {
            chase();
            attack_hit_rect = {};
        }
        if (CheckCollisionRecs(attack_detect_rect, player.normal_hitbox))
            attack();

        else
        {
            wander();
            attack_hit_rect = {};
        }
    }
}
void Enemy_forest_scourge::randomize_wander_state()
{
    int new_state;
    do {
        new_state = rand() % 4;
    } while (new_state == wander_state);

    wander_state = new_state;
}
// dang - 400+ lines for a single enemy? thats crazy

The_Regrown::The_Regrown()
{
    if (current_map == BIG_TREE_LEVEL_10)
    {
        pos = {96, -88};
    }
    current_anim_arr = the_regrown_entrance_arr;
    max_animation_frames = 4;
    current_animation_frame = 0;
    animation_frame_5 = 0;
    health = THE_REGROWN_HEALTH;
    move_mode = 1;
    rect = {THE_REGROWN_FINAL_X + THE_REGROWN_RECT_OFFSET_X, THE_REGROWN_FINAL_Y + THE_REGROWN_RECT_OFFSET_Y, THE_REGROWN_RECT_WIDTH, THE_REGROWN_RECT_HEIGHT};
    col_rect_1 = THE_REGROWN_COLLISION_RECT_1;
    col_rect_2 = THE_REGROWN_COLLISION_RECT_2;
    col_rect_3 = THE_REGROWN_COLLISION_RECT_3;
    started_fight = false;
    can_take_damage = true;
    death_anim_started = false;
    active_damaging_rect = {};
    ground_attack_cooldown = 0;
    can_use_ground_attack = true;
    // name = THE_REGROWN;
    init_item_drop();
}

The_Regrown::~The_Regrown()
{
    if (tex.id != 0)
    {
        UnloadTexture(tex);
    }
    
}

void The_Regrown::load()
{
    tex = LoadTexture(THE_REGROWN_TEX_PATH);
}

void The_Regrown::update()
{
    // constant things that should be updated every frame
    if (!started_fight)
    {
        if (player.pos.y > THE_REGROWN_PLAYER_Y_TRIGGER)
        { 
            
            
            
            
            if(pos.y < THE_REGROWN_FINAL_Y){
                pos.y+=THE_REGROWN_FALL_SPEED;
               
                if(current_anim_arr != the_regrown_entrance_arr){
                    current_anim_arr = the_regrown_entrance_arr;
                    max_animation_frames = 8;
                }
            }
            if(pos.y >= THE_REGROWN_FINAL_Y){
                started_fight = true;
                collision_rects.push_back(col_rect_1);
                collision_rects.push_back(col_rect_2);
                collision_rects.push_back(col_rect_3);
            }
        }
        

        return;
    }
    ground_attack_cooldown -= GetFrameTime();
    if (ground_attack_cooldown < 0)
    {
        ground_attack_cooldown = 0;
        can_use_ground_attack = true;
    }
    if (hit_flash_timer > 0.0f)
        hit_flash_timer -= GetFrameTime();
    if (CheckCollisionRecs(rect, player.attack_hitbox))
    {
        take_damage(player.active_damage);
    }
    
    if (!can_take_damage)
    {
        iframe_timer -= GetFrameTime();
        if (iframe_timer <= 0.0f)
        {
            can_take_damage = true;
            iframe_timer = 0.0f;
        }
    }
    if (health <= 0 && !death_anim_started)
    {
        death_anim_started = true;
        move_mode = 2;
        current_anim_arr = the_regrown_die_arr;
        max_animation_frames = 14;
        current_animation_frame = 0;
        player.defeated_entities.push_back(name);
        ground_items.push_back(item_drop);
        item_drop = {}; //freeing up a few bytes idk
        // broken_floor_tiles.clear(); //one-time thing for this boss to make sure the player picks up the item
        remove_collision_rect(col_rect_1);
        remove_collision_rect(col_rect_2);
        remove_collision_rect(col_rect_3);
        
        // collision_rects.push_back(BIG_TREE_LEVEL_RECT_20); //I HAVE NO IDEA WHY THIS RECT GETS NUKED - BUT OKAY
        // collision_rects.push_back(BIG_TREE_LEVEL_RECT_2); //same here ^ 
    }
    
    // movemode things, mostly animations
    if (move_mode == 0)
    {
    }
    if (move_mode == 1)
    {

        animation_frame_5++;
        if (animation_frame_5 >= ANIMATION_INTERVAL)
        {
            current_animation_frame++;
            if (current_animation_frame >= max_animation_frames)
            {
                current_animation_frame = 0;
            }
            animation_frame_5 = 0;
        }
        active_damaging_rect = {};
        decide_action();
    }
    if (move_mode == 2)
    {
        animation_frame_5++;
        if (animation_frame_5 >= ANIMATION_INTERVAL)
        {
            current_animation_frame++;
            if (current_animation_frame >= max_animation_frames)
            {
                if (death_anim_started)
                {
                    dead = true;
                    return; // stop updating completely
                }
                current_animation_frame = 0;

                move_mode = 1;
            }
            animation_frame_5 = 0;
        }
    }
}

void The_Regrown::draw()
{
    DrawTexturePro(tex, current_anim_arr[current_animation_frame], {pos.x, pos.y, float(DEFAULT_SPRITE_WIDTH_128), float(DEFAULT_SPRITE_HEIGHT_128)}, {0, 0}, 0, hit_flash_timer > 0.0f ? RED : WHITE);
    
}

void The_Regrown::init_item_drop()
{
    item_drop.pos = THE_REGROWN_ITEM_DROP_POS;
    item_drop.item = Sacred_bark;
    
}

void The_Regrown::take_damage(float damage)
{
    if (!can_take_damage)
        return;
    if (can_take_damage)
    {
        
        health -= damage;
        hit_flash_timer = HIT_FLASH_TIME;
        can_take_damage = false;
        iframe_timer = ENEMY_IFRAME_TIME;
        start_hitstop(player.active_damage);
        if (health < 0)
        {
            health = 0;
        }
    }
}

void The_Regrown::right_arm_attack()
{
    move_mode = 2;
    current_anim_arr = the_regrown_attack_right_arr;
    max_animation_frames = 5;
    current_animation_frame = 0;

    active_damaging_rect = {pos.x+THE_REGROWN_RIGHT_ARM_DAMAGE_OFFSET_X, pos.y+THE_REGROWN_RIGHT_ARM_DAMAGE_OFFSET_Y, THE_REGROWN_RIGHT_ARM_DAMAGE_RECT_W_H};
    if (CheckCollisionRecs(active_damaging_rect, player.normal_hitbox))
    {
        damage_player(THE_REGROWN_ARM_DAMAGE);
    }
}

void The_Regrown::left_arm_attack()
{
    move_mode = 2;
    current_anim_arr = the_regrown_attack_left_arr;
    max_animation_frames = 5;
    current_animation_frame = 0;
    active_damaging_rect = {pos.x+THE_REGROWN_LEFT_ARM_DAMAGE_OFFSET_X, pos.y+THE_REGROWN_LEFT_ARM_DAMAGE_OFFSET_X, THE_REGROWN_LEFT_ARM_DAMAGE_RECT_W_H};
    if (CheckCollisionRecs(active_damaging_rect, player.normal_hitbox))
    {
        damage_player(THE_REGROWN_ARM_DAMAGE);
    }
}

void The_Regrown::ground_shake_attack()
{
    if (can_use_ground_attack)
    {
        move_mode = 2;
        current_anim_arr = the_regrown_ground_shake_arr;
        max_animation_frames = 6;
        current_animation_frame = 0;
        can_use_ground_attack = false;
        ground_attack_cooldown = THE_REGROWN_GROUND_ATTACK_COOLDOWN;
        start_screen_shake(1.5, 5);
        break_random_floor_tiles(5);
    }
    else
    {
    }
}

void The_Regrown::decide_action()
{
    
    //  ground_shake_attack();
    idle_animation();
    if (CheckCollisionRecs({THE_REGROWN_RIGHT_ATTACK_DETECT_OFFSET_X + pos.x, THE_REGROWN_RIGHT_ATTACK_DETECT_OFFSET_Y + pos.y, THE_REGROWN_ARM_ATTACK_DETECT_WIDTH, THE_REGROWN_ARM_ATTACK_DETECT_HEIGHT}, player.normal_hitbox))
    {
        right_arm_attack();
    }
    else if (CheckCollisionRecs({THE_REGROWN_LEFT_ATTACK_DETECT_OFFSET_X + pos.x, THE_REGROWN_LEFT_ATTACK_DETECT_OFFSET_Y + pos.y, THE_REGROWN_ARM_ATTACK_DETECT_WIDTH, THE_REGROWN_ARM_ATTACK_DETECT_HEIGHT}, player.normal_hitbox))
    {
        left_arm_attack();
    }
    else
    {
        ground_shake_attack();
    }
}

void The_Regrown::fall_down()
{
    move_mode = 2;
    current_anim_arr = the_regrown_entrance_arr;
    max_animation_frames = 8;
    current_animation_frame = 0;
}

void The_Regrown::idle_animation()
{
    move_mode = 2;
    current_anim_arr = the_regrown_idle_arr;
    max_animation_frames = 4;
    current_animation_frame = 0;
}

void The_Regrown::break_random_floor_tiles(int amount) 
{
    for(int i = 0; i < amount; i++){
        int x = GetRandomValue(0, map_to_load.width/16);
        int y = GetRandomValue(0, map_to_load.height/16);
        x*=16;
        y*=16;
        if(CheckCollisionRecs({float(x), float(y), 16, 16}, the_regrown_possible_destructable_tile_area)
        && !CheckCollisionRecs({float(x), float(y), 16, 16}, player.normal_hitbox)
        && !CheckCollisionRecs({float(x), float(y), 16, 16}, the_regrown_impossible_destructable_tile_area)){
            // implement actually breaking the tiles here
            map_load_rects.push_back(Load_rects({x, y, 16, 16}, BIG_TREE_LEVEL_9, {x-23, y-37}));//TODO: figure out what this code is going to do. move to vfx? player? idk, but thats for later
            broken_floor_tiles.push_back(Vector2(x, y));
            continue;
        }
        else{
            amount++;
            continue;
        }
    }
}
