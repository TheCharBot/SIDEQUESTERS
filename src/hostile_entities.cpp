#include "hostile_entities.hpp"

//should probably put this somewhere
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
    pos.x = Clamp(pos.x, 0, map_to_load.width-DEFAULT_SPRITE_WIDTH);
    pos.y = Clamp(pos.y, 0, map_to_load.height-DEFAULT_SPRITE_WIDTH);

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
        health -= damage;
        hit_flash_timer = HIT_FLASH_TIME;
        if (health < 0)
        {
            health = 0;
        }
        can_take_damage = false;
        iframe_timer = ENEMY_IFRAME_TIME;
        Vector2 dir = Vector2Normalize(
            Vector2Subtract(pos, hit_source_pos));

        pos = Vector2Add(pos, Vector2Scale(dir, KNOCKBACK_DIST));
    }
}

void Enemy_forest_scourge::wander()
{

    // implement by randomly alternating between left and right and up and down movement
    //  just randomizing a ton of stuff in a very random way
    // and then keeping it inside the screen
    if (wander_state == 1)
    {
        current_anim_arr = forest_scourge_walk_down_right;
        if (pos.x >= originial_pos.x - 100)
        {

            pos.x -= FOREST_SCOURGE_SPEED;
            rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
            for (Rectangle &r : collision_rects)
            {
                if (CheckCollisionRecs(rect, r))
                {
                    pos.x += FOREST_SCOURGE_SPEED * 2;
                    wander_state = (rand() % 4) + 1;
                }
            }
        }
        else
        {
            wander_state = (rand() % 4) + 1;
        }
    }
    if (wander_state == 2)
    {
        current_anim_arr = forest_scourge_walk_down_right;
        max_animation_frames = 7;
        if (pos.x <= originial_pos.x + 100)
        {

            pos.x += FOREST_SCOURGE_SPEED;
            rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
            for (Rectangle &r : collision_rects)
            {
                if (CheckCollisionRecs(rect, r))
                {
                    pos.x -= FOREST_SCOURGE_SPEED * 2;
                    wander_state = (rand() % 4) + 1;
                }
            }
        }
        else
        {
            wander_state = (rand() % 4) + 1;
        }
    }
    if (wander_state == 3)
    {
        current_anim_arr = forest_scourge_walk_down_right;
        max_animation_frames = 7;
        if (pos.y <= originial_pos.y + 100)
        {

            pos.y += FOREST_SCOURGE_SPEED;
            rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
            for (Rectangle &r : collision_rects)
            {
                if (CheckCollisionRecs(rect, r))
                {
                    pos.y -= FOREST_SCOURGE_SPEED * 2;
                    wander_state = (rand() % 4) + 1;
                }
            }
        }
        else
        {
            wander_state = (rand() % 4) + 1;
        }
    }
    if (wander_state == 4)
    {
        current_anim_arr = forest_scourge_walk_up_left;
        max_animation_frames = 7;
        if (pos.y >= originial_pos.y - 100)
        {

            pos.y -= FOREST_SCOURGE_SPEED;
            rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
            for (Rectangle &r : collision_rects)
            {
                if (CheckCollisionRecs(rect, r))
                {
                    pos.y += FOREST_SCOURGE_SPEED * 2;
                    wander_state = (rand() % 4) + 1;
                }
            }
        }
        else
        {
            wander_state = (rand() % 4) + 1;
        }
    }
    if (pos.x <= 0)
    {
        wander_state = (rand() % 4) + 1;
    }
    if (pos.x >= map_to_load.width)
    {
        wander_state = (rand() % 4) + 1;
    }
    if (pos.y <= 0)
    {
        wander_state = (rand() % 4) + 1;
    }
    if (pos.y >= map_to_load.height)
    {
        wander_state = (rand() % 4) + 1;
    }
}

void Enemy_forest_scourge::chase()
{
    // look, its not perfect and never will be, but i have nothing else, so im keeping it
    // why must this be so annoying?!?!???!

    // before release, make this better
    // TODO: make better. not urgent

    float dt = GetFrameTime();

    Vector2 dir = Vector2Normalize(Vector2Subtract(player.pos, pos));
    Vector2 velocity = Vector2Scale(dir, FOREST_SCOURGE_CHASE_SPEED * dt);

    // seperate x and y movement
    // this is VERY helpful and should DEFINENTLY be saved!!! both ^ and v !!!
    //* SAVE THIS. HECK, SAVE ALL OF IT !!!!!!
    //* THIS IS VERRRRRY IMPORTANT
    //* PRETTY MUCH EVERYITHG CAN BE REUSED
    //* OH YEAH!!!!!!!
    pos.x += velocity.x;

    rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
    for (const Rectangle &r : collision_rects)
    {
        if (CheckCollisionRecs(rect, r))
        {

            pos.x -= velocity.x;
            break;
        }
    }

    pos.y += velocity.y;

    rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
    for (const Rectangle &r : collision_rects)
    {
        if (CheckCollisionRecs(rect, r))
        {
            pos.y -= velocity.y;
            break;
        }
    }

    if (rect.y < player.normal_hitbox.y)
    {
        current_anim_arr = forest_scourge_walk_up_left;
        max_animation_frames = 7;
    }
    else
    {
        current_anim_arr = forest_scourge_walk_down_right;
        max_animation_frames = 7;
    }
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
        if (CheckCollisionRecs(chase_detect_rect, player.normal_hitbox))
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
// dang - 420 lines for a single enemy? thats crazy

The_Regrown::The_Regrown()
{
    if(current_map == BIG_TREE_LEVEL_10){
        pos = THE_REGROWN_POS; 
    }
    current_anim_arr = the_regrown_idle_arr;
    max_animation_frames = 4;
    current_animation_frame = 0;
    animation_frame_5 = 0;
    health = THE_REGROWN_HEALTH;
    move_mode = 1;
    rect = {pos.x+THE_REGROWN_RECT_OFFSET_X, pos.y+THE_REGROWN_RECT_OFFSET_Y, THE_REGROWN_RECT_WIDTH, THE_REGROWN_RECT_HEIGHT};
    col_rect_1 = THE_REGROWN_COLLISION_RECT_1;
    col_rect_2 = THE_REGROWN_COLLISION_RECT_2;
    col_rect_3 = THE_REGROWN_COLLISION_RECT_3;
    loaded_rects = false;
    can_take_damage = true;
    death_anim_started = false;

}

The_Regrown::~The_Regrown()
{
    if(tex.id != 0){
        UnloadTexture(tex);
    }
     auto remove_rect = [&](const Rectangle& r)
    {
        collision_rects.erase(
            std::remove_if(
                collision_rects.begin(),
                collision_rects.end(),
                [&](const Rectangle& c){ return CheckCollisionRecs(c, r); }
            ),
            collision_rects.end()
        );
    };

    remove_rect(col_rect_1);
    remove_rect(col_rect_2);
    remove_rect(col_rect_3);
    player.defeated_bosses.the_regrown_defeated = true;
}

void The_Regrown::load()
{
    tex = LoadTexture(THE_REGROWN_TEX_PATH);
}

void The_Regrown::update()
{   
    //constant things that should be updated every frame

    if(CheckCollisionRecs(rect, player.attack_hitbox)){
        take_damage(player.active_damage);
    }
    if (hit_flash_timer > 0.0f)
            hit_flash_timer -= GetFrameTime();
    if (!can_take_damage)
    {
        iframe_timer -= GetFrameTime();
        if (iframe_timer <= 0.0f)
        {
            can_take_damage = true;
            iframe_timer = 0.0f;
        }
    }
    if(health <= 0 && !death_anim_started){
            death_anim_started = true;
            move_mode = 2;
            current_anim_arr = the_regrown_die_arr;
            max_animation_frames = 14;
            current_animation_frame = 0;
            
    }
    if(!loaded_rects){
        if(player.pos.y > 75){ // TODO: replace w/ macros again
            collision_rects.push_back(col_rect_1);
            collision_rects.push_back(col_rect_2);
            collision_rects.push_back(col_rect_3);
            loaded_rects = true;
        }
    }
    //movemode things, mostly animations
    if(move_mode == 0){}
    if(move_mode == 1){
    
        
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
        
        decide_action();
    }
    if(move_mode == 2){
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

void The_Regrown::take_damage(float damage)
{
    if (!can_take_damage)
        return;
    if (can_take_damage)
    {
        // implement knockback
        health -= damage;
        hit_flash_timer = HIT_FLASH_TIME;
        can_take_damage = false;
        iframe_timer = ENEMY_IFRAME_TIME;
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
}

void The_Regrown::left_arm_attack()
{
    move_mode = 2;
    current_anim_arr = the_regrown_attack_left_arr;
    max_animation_frames = 5;
    current_animation_frame = 0;

}

void The_Regrown::ground_shake_attack()
{
    move_mode = 2;
    current_anim_arr = the_regrown_ground_shake_arr;
    max_animation_frames = 6;
    current_animation_frame = 0;

}

void The_Regrown::decide_action()
{
    ground_shake_attack();
}

void The_Regrown::fall_down()
{
    move_mode = 2;
    current_anim_arr = the_regrown_entrance_arr;
    max_animation_frames = 8;
    current_animation_frame = 0;

}