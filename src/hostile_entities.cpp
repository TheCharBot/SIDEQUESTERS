#include "hostile_entities.hpp"

Texture2D Enemy_forest_scourge::shared_tex = {};
bool Enemy_forest_scourge::texture_loaded = false;

void unload_enemy_textures()
{
    //add all the enemy textures that spawn more than one per map, call when loading map, in reset_loaded
    if (Enemy_forest_scourge::texture_loaded) {
        UnloadTexture(Enemy_forest_scourge::shared_tex);
        Enemy_forest_scourge::texture_loaded = false;
    }
}


Enemy_forest_scourge::Enemy_forest_scourge()
{

    current_anim_arr = forest_scourge_walk_down_right;
    max_animation_frames = 7;
    current_animation_frame = 0;
    animation_frame_5 = 0;
    dead = false;
    health = FOREST_SCOURGE_HEALTH;
    direction = DOWN_RIGHT;
    wander_state = 1;
    pos = {0,0};
    rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
}

Enemy_forest_scourge::~Enemy_forest_scourge()
{
    //really put nothing here - ???
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
            wander_mode = LEFT_RIGHT;
            pos = {100, 150};
            
            break;
        case 1:
            wander_mode = RANDOM;
            pos = {380, 30};
            
            break;
        case 2:
            wander_mode = UP_DOWN;
            pos = {520, 345};
            
            break;
        case 3:
            wander_mode = RANDOM;
            pos = {280, 412};
            
            break;
        case 4:
            wander_mode = UP_DOWN;
            pos = {425, 685};
            
            break;
        case 5:
            wander_mode = RANDOM;
            pos = {105, 875};
            
            break;
        default:
            wander_mode = LEFT_RIGHT;
            pos = {100, 150};
            
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
    rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
    decide_action();
}

void Enemy_forest_scourge::draw()
{
    DrawTexturePro(shared_tex, current_anim_arr[current_animation_frame], {pos.x * scale, pos.y * scale, float(DEFAULT_SPRITE_WIDTH * scale), float(DEFAULT_SPRITE_HEIGHT * scale)}, {0, 0}, 0, WHITE);
}

void Enemy_forest_scourge::wander()
{
    
    switch (wander_mode)
    {
    case UP_DOWN:
        if (wander_state == 1)
        {
            if (pos.y > originial_pos.y - 100)
            {
                
                pos.y -= FOREST_SCOURGE_SPEED;
                rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
                for(Rectangle &r : collision_rects){
                    if(CheckCollisionRecs(rect, r)){
                        wander_state = 2;
                    }
                }
            }
            else
            {
                wander_state = 2;
            }
        }
        if (wander_state == 2)
        {
            if (pos.y < originial_pos.y + 100)
            {
                
                pos.y += FOREST_SCOURGE_SPEED;
                rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
                for(Rectangle &r : collision_rects){
                    if(CheckCollisionRecs(rect, r)){
                        wander_state = 1;
                    }
                }
            }
            else
            {
                wander_state = 1;
            }
        }
        break;
    case LEFT_RIGHT:
        if (wander_state == 1)
        {
            if (pos.x >= originial_pos.x - 100)
            {
                
                pos.x -= FOREST_SCOURGE_SPEED;
                rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
                for(Rectangle &r : collision_rects){
                    if(CheckCollisionRecs(rect, r)){
                        wander_state = 2;
                    }
                }
            }
            else
            {
                wander_state = 2;
            }
        }
        if (wander_state == 2)
        {
            if (pos.x <= originial_pos.x + 100)
            {
                
                pos.x += FOREST_SCOURGE_SPEED;
                rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
                for(Rectangle &r : collision_rects){
                    if(CheckCollisionRecs(rect, r)){
                        wander_state = 1;
                    }
                }
            }
            else
            {
                wander_state = 1;
            }
        }
        break;
    case RANDOM:
    //implement by randomly alternating between left and right and up and down movement
        if (wander_state == 1)
        {
            if (pos.x >= originial_pos.x - 100)
            {
                
                pos.x -= FOREST_SCOURGE_SPEED;
                rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
                for(Rectangle &r : collision_rects){
                    if(CheckCollisionRecs(rect, r)){
                        wander_state = 2;
                    }
                }
            }
            else
            {
                wander_state = 2;
                
            }
        }
        if (wander_state == 2)
        {
            if (pos.x <= originial_pos.x + 100)
            {
                
                pos.x += FOREST_SCOURGE_SPEED;
                rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
                for(Rectangle &r : collision_rects){
                    if(CheckCollisionRecs(rect, r)){
                        wander_state = 1;
                    }
                }
            }
            else
            {
                wander_state = 1;

            }
        }
        break;
    }
}

void Enemy_forest_scourge::chase()
{
    float dt = GetFrameTime();

    Vector2 dir = Vector2Normalize(Vector2Subtract(player.pos, pos));
    Vector2 velocity = Vector2Scale(dir, FOREST_SCOURGE_SPEED * scale * dt * scale); // throw another * scale in there for good measure (im happy - it all works :) )

    // seperate x and y movement
    //this is VERY helpful and should DEFINENTLY be saved!!! both ^ and v !!!
    //! SAVE THIS
    pos.x += velocity.x;

    rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
    for (const Rectangle& r : collision_rects)
    {
        if (CheckCollisionRecs(rect, r))
        {
            
            pos.x -= velocity.x;
            break;
        }
    }

    
    pos.y += velocity.y;

    rect = {pos.x + FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y + FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
    for (const Rectangle& r : collision_rects)
    {
        if (CheckCollisionRecs(rect, r))
        {
            pos.y -= velocity.y;
            break;
        }
    }
}

void Enemy_forest_scourge::attack()
{
}

void Enemy_forest_scourge::run_away()
{
}

void Enemy_forest_scourge::decide_action()
{
    
    chase();
}
