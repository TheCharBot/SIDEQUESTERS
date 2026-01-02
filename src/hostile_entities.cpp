#include "hostile_entities.hpp"

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
    attack_detect_rect = {pos.x+FOREST_SCOURGE_ATTACK_DETECT_OFFSET_X, pos.y+FOREST_SCOURGE_ATTACK_DETECT_OFFSET_Y, FOREST_SCOURGE_ATTACK_DETECT_WIDTH, FOREST_SCOURGE_ATTACK_DETECT_HEIGHT}; 
    attack_hit_rect = {};
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

            pos = {100, 150};

            break;
        case 1:

            pos = {380, 30};

            break;
        case 2:

            pos = {520, 345};

            break;
        case 3:

            pos = {280, 412};

            break;
        case 4:

            pos = {425, 685};

            break;
        case 5:

            pos = {105, 875};

            break;
        default:

            pos = {100, 150};

            break;
        }
    }
    wander_mode = UP_DOWN;
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
    rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
    chase_detect_rect = {pos.x - FOREST_SCOURGE_CHASE_DETECT_OFFSET_X, pos.y - FOREST_SCOURGE_CHASE_DETECT_OFFSET_Y, FOREST_SCOURGE_CHASE_DETECT_WIDTH, FOREST_SCOURGE_CHASE_DETECT_HEIGHT};
    attack_detect_rect = {pos.x+FOREST_SCOURGE_ATTACK_DETECT_OFFSET_X, pos.y+FOREST_SCOURGE_ATTACK_DETECT_OFFSET_Y, FOREST_SCOURGE_ATTACK_DETECT_WIDTH, FOREST_SCOURGE_ATTACK_DETECT_HEIGHT}; 
    pos.x = Clamp(pos.x, 0, map_to_load.width);
    pos.y = Clamp(pos.y, 0, map_to_load.height);

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
    DrawTexturePro(shared_tex, current_anim_arr[current_animation_frame], {pos.x * scale, pos.y * scale, float(DEFAULT_SPRITE_WIDTH * scale), float(DEFAULT_SPRITE_HEIGHT * scale)}, {0, 0}, 0, WHITE);
}

void Enemy_forest_scourge::take_damage(float damage, Vector2 hit_source_pos)
{
    if (!can_take_damage)
        return;
    if(can_take_damage){
        //implement knockback
        health -= damage;
        if(health < 0){
            health = 0;
        }
        can_take_damage = false;
        iframe_timer = PLAYER_IFRAME_TIME;
        Vector2 dir = Vector2Normalize(
        Vector2Subtract(pos, hit_source_pos)
        );

        
        
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
    float dt = GetFrameTime();

    Vector2 dir = Vector2Normalize(Vector2Subtract(player.pos, pos));
    Vector2 velocity = Vector2Scale(dir, FOREST_SCOURGE_SPEED * scale * dt * scale); // throw another * scale in there for good measure (im happy - it all works :) )

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


    if(rect.y > player.normal_hitbox.y){
        current_anim_arr = forest_scourge_walk_up_left;
        max_animation_frames = 7;
    }
    else{ current_anim_arr = forest_scourge_walk_down_right;
    max_animation_frames = 7; }
}

void Enemy_forest_scourge::attack()
{
    
    current_anim_arr = forest_scourge_attack_down_right;
    max_animation_frames = 6;
    attack_hit_rect = {pos.x+FOREST_SCOURGE_ATTACK_DETECT_OFFSET_X, pos.y+FOREST_SCOURGE_ATTACK_DETECT_OFFSET_X, FOREST_SCOURGE_ATTACK_WIDTH, FOREST_SCOURGE_ATTACK_HEIGHT};
    if(CheckCollisionRecs(attack_hit_rect, player.normal_hitbox)){
        damage_player(FOREST_SCOURGE_DAMAGE);
    }
}

void Enemy_forest_scourge::run_away()
{
    // might not implement - maybe on a more intellegent enemy?
}

void Enemy_forest_scourge::decide_action()
{
    if(CheckCollisionRecs(rect, player.attack_hitbox)){
        //make a player.active_damage thing or whatever
        take_damage(0.3f, player.pos);
    }
    if (CheckCollisionRecs(chase_detect_rect, player.normal_hitbox)){
        chase(); 
        attack_hit_rect = {};
    }
    if(CheckCollisionRecs(attack_detect_rect, player.normal_hitbox))
        attack();
    
    else{
        wander(); 
        attack_hit_rect = {};
    }
}
// dang - 330 lines for a single enemy? thats crazy