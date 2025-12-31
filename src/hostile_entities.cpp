#include "hostile_entities.hpp"

Enemy_forest_scourge::Enemy_forest_scourge()
{
    current_anim_arr = forest_scourge_walk_down_right;
    max_animation_frames = 7;
    current_animation_frame = 0;
    animation_frame_5 = 0;
    dead = false;
    health = 2;
    pos = {104, 144};
    hitbox = {pos.x+FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y+FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
}

Enemy_forest_scourge::~Enemy_forest_scourge()
{
    if(tex.id != 0){
        UnloadTexture(tex);
    }
}

void Enemy_forest_scourge::load()
{
    random_index = rand() % 6;
    tex = LoadTexture("gfx/enemies/forest_scourge/forest_scourge_tex.png");
}

void Enemy_forest_scourge::update()
{
    hitbox = {pos.x+FOREST_SCOURGE_HITBOX_OFFSET_X, pos.y+FOREST_SCOURGE_HITBOX_OFFSET_Y, FOREST_SCOURGE_HITBOX_WIDTH, FOREST_SCOURGE_HITBOX_HEIGHT};
    if(CheckCollisionRecs(hitbox, player.normal_hitbox)){
        health = 0;
    }
    if(health <= 0){
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
    
    
}

void Enemy_forest_scourge::draw()
{
    DrawTexturePro(tex, current_anim_arr[current_animation_frame], {pos.x*scale, pos.y*scale, (float)DEFAULT_SPRITE_WIDTH*scale, (float)DEFAULT_SPRITE_HEIGHT*scale}, {0, 0}, 0, WHITE);
}

void Enemy_forest_scourge::wander_patrol()
{
}

void Enemy_forest_scourge::chase()
{
}

void Enemy_forest_scourge::attack()
{
}

void Enemy_forest_scourge::run_away()
{
}
