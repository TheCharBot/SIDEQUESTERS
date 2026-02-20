#include "entities.hpp"

// 358, 302, coords for windmill

Village_windmill::Village_windmill()
{
    max_animation_frames = 4;
    current_animation_frame = 0;
    animation_frame_5 = 0;
    pos = {VILLAGE_WINDMILL_X, VILLAGE_WINDMILL_Y};
    rect = {pos.x + VILLAGE_WINDMILL_RECT_OFFSET_X, pos.y + VILLAGE_WINDMILL_RECT_OFFSET_Y, VILLAGE_WINDMILL_RECT_WIDTH, VILLAGE_WINDMILL_RECT_HEIGHT};
    collision_rects.push_back(rect);
    
}

Village_windmill::~Village_windmill()
{
    if (tex.id != 0)
    {
        UnloadTexture(tex);
    }
}

void Village_windmill::load()
{
    tex = LoadTexture(VILLAGE_WINDMILL_PATH);
}

void Village_windmill::update()
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
}

void Village_windmill::draw()
{
    DrawTexturePro(tex, village_windmill_animation[current_animation_frame], {pos.x, pos.y, float(VILLAGE_WINDMILL_WIDTH), float(VILLAGE_WINDMILL_HEIGHT)}, {0, 0}, 0, WHITE);
}

Start_bulldozer::Start_bulldozer()
{

    current_animation_frame = 0;
    pos = {START_BULLDOZER_X, START_BULLDOZER_Y};
    fallen = false;
}

Start_bulldozer::~Start_bulldozer()
{
    if (tex.id != 0)
    {
        UnloadTexture(tex);
    }
    rect = {};
    // pos = {START_BULLDOZER_X, START_BULLDOZER_Y};
}

void Start_bulldozer::load()
{
    tex = LoadTexture(BULLDOZER_TEX_PATH);
}
void Start_bulldozer::update()
{
    rect = {pos.x, pos.y, START_BULLDOZER_WIDTH, START_BULLDOZER_HEIGHT};
    // checking if the player is at a Specific y value
    if (player.normal_hitbox.y <= BULLDOZER_TRIGGER_Y)
    {
        is_inv_open = false;
        // running cutscene magic
        player.move_mode = 0;
        if (player.normal_hitbox.y > 160)
        {
            player.pos.y -= PLAYER_SPEED;
        }
        if (pos.x < MAX_BULLDOZER_X)
        {
            pos.x += BULLDOZER_SPEED;
        }
        if (CheckCollisionRecs(player.normal_hitbox, rect))
        {
            // why is this number not in assets?
            if (pos.x >= 232)
            {
                request_map(VILLAGE_MAP, {PLAYER_VILLAGE_MAP_POS_X, PLAYER_VILLAGE_MAP_POS_Y});
            }

            else
            {
                pos.x += BULLDOZER_SPEED;
                player.pos.x += BULLDOZER_SPEED;
            }
        }
    }
}
void Start_bulldozer::draw()
{

    DrawTexturePro(tex, start_bulldozer_animation[current_animation_frame], {pos.x, pos.y, float(START_BULLDOZER_WIDTH), float(START_BULLDOZER_HEIGHT)}, {0, 0}, 0, WHITE);

    // if (collided)
    // {
    //
    //     collided = false;

    // }
}

// portal stuff
Start_portal::Start_portal()
{

    max_animation_frames = 4;
    current_animation_frame = 0;
    animation_frame_5 = 0;

    pos = {float(START_PORTAL_X), float(START_PORTAL_Y)};
}

Start_portal::~Start_portal()
{
    if (tex.id != 0)
    {
        UnloadTexture(tex);
    }
    rect = {};
}

void Start_portal::load()
{

    tex = LoadTexture(PORTAL_TEX_PATH);
}

void Start_portal::update()
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

    // portal logic
}

void Start_portal::draw()
{

    DrawTexturePro(tex, start_portal_animation[current_animation_frame], {pos.x, pos.y, float(START_PORTAL_WIDTH), float(START_PORTAL_HEIGHT)}, {0, 0}, 0, WHITE);
}


Big_tree::Big_tree()
{
    pos = BIG_TREE_POS;
    //should probably move to macros later
    
    rect = {pos.x, pos.y+BIG_TREE_RECT_OFFSET_Y, BIG_TREE_RECT_W_H};
    rect1 = {pos.x+BIG_TREE_RECT1_OFFSET_X, pos.y+BIG_TREE_RECT1_OFFSET_Y, BIG_TREE_RECT1_W_H};
    rect2 = {pos.x+BIG_TREE_RECT2_OFFSET_X, pos.y+BIG_TREE_RECT2_OFFSET_Y, BIG_TREE_RECT2_W_H};
    rect3 = {pos.x+BIG_TREE_RECT3_OFFSET_X, pos.y+BIG_TREE_RECT3_OFFSET_Y, BIG_TREE_RECT3_W_H};
    collision_rects.push_back(rect1);
    collision_rects.push_back(rect2);
    collision_rects.push_back(rect3);
}

Big_tree::~Big_tree()
{
    if(tex.id != 1){
        UnloadTexture(tex);
    }
}

void Big_tree::load()
{
    tex = LoadTexture(BIG_TREE_TEX_PATH);
}

void Big_tree::update()
{
}

void Big_tree::draw()
{
    DrawTextureEx(tex, pos, 0, 1, WHITE);
}

Big_tree_level_tree_trunk::Big_tree_level_tree_trunk(int which_trunk)
{
    
    pos = BIG_TREE_LEVELS_TREE_TRUNKS_POS;
    switch(which_trunk){
        case 1:
            img_rect = Big_tree_levels_tree_trunk_middle;
            rect = {pos.x+BIG_TREE_LEVELS_TREE_TRUNKS_OFFSET_X, pos.y+BIG_TREE_LEVELS_TREE_TRUNKS_OFFSET_Y, BIG_TREE_LEVELS_TREE_TRUNKS_W_H};
            break;
        case 2:
            img_rect = Big_tree_levels_tree_trunk_top;
            rect = {0, 1000, 1, 1};
            break;
        case 3:
            img_rect = Big_tree_levels_tree_trunk_bottom;
            rect = {pos.x+BIG_TREE_LEVELS_TREE_TRUNKS_OFFSET_X, pos.y+BIG_TREE_LEVELS_TREE_TRUNKS_OFFSET_Y, BIG_TREE_LEVELS_TREE_TRUNKS_W_H};
            break;
    }
    collision_rects.push_back(rect);
    hit_flash_timer = 0;
    iframe_timer = 0;   
    health = BIG_TREE_LEVELS_TREE_TRUNKS_HEALTH;
}

Big_tree_level_tree_trunk::~Big_tree_level_tree_trunk()
{
    if(tex.id != 0){
        UnloadTexture(tex);
    }
}

void Big_tree_level_tree_trunk::load()
{
    tex = LoadTexture(BIG_TREE_LEVELS_TREE_TRUNKS_TEX_PATH);
}

void Big_tree_level_tree_trunk::update()
{
    if (hit_flash_timer > 0.0f)
        hit_flash_timer -= GetFrameTime();
    if(CheckCollisionRecs(rect, player.attack_hitbox)){
        if (!can_take_damage)
            return;
        if (can_take_damage)
        {
            
            health -= player.active_damage;
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
    
    if (!can_take_damage)
    {
        iframe_timer -= GetFrameTime();
        if (iframe_timer <= 0.0f)
        {
            can_take_damage = true;
            iframe_timer = 0.0f;
        }
    }
    if(health == 0){
        if(current_map == BIG_TREE_LEVEL_5){
            add_ground_item(Big_tree_level_5_key);
        }
        player.defeated_entities.push_back(name);
        remove_collision_rect(rect);
        dead = true;
        
    }

}

void Big_tree_level_tree_trunk::draw()
{
    DrawTexturePro(tex, img_rect, {pos.x, pos.y, img_rect.width, img_rect.height}, {0, 0}, 0, hit_flash_timer > 0.0f ? RED : WHITE);
}



Village_questgiver_1::Village_questgiver_1()
{
    pos = VILLAGE_QUESTGIVER_1_POS;
    current_animation_frame = 0;
    current_animation_arr = village_questgiver_idle;
    rect = {pos.x+VILLAGE_QUESTGIVER_1_HITBOX_OFFSET_X, pos.y+VILLAGE_QUESTGIVER_1_HITBOX_OFFSET_Y, VILLAGE_QUESTGIVER_1_HITBOX_WIDTH, VILLAGE_QUESTGIVER_1_HITBOX_HEIGHT};
    interact_rect = {pos.x+22, pos.y+45, 19, 15};
    add_collisions({rect});
}

Village_questgiver_1::~Village_questgiver_1()
{
    if(tex.id != 0){
        UnloadTexture(tex);
    }
}

void Village_questgiver_1::load()
{
    tex = LoadTexture(VILLAGE_QUESTGIVER_1_PATH);
}

void Village_questgiver_1::update()
{
    if(IsKeyPressed(KEY_INTERACT) && CheckCollisionRecs(interact_rect, player.normal_hitbox) && !is_textbox_open){
        
        //TODO: figure out what this guy is actually going to say
    }
}

void Village_questgiver_1::draw()
{
    DrawTexturePro(tex, current_animation_arr[current_animation_frame], {pos.x, pos.y, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT}, {0, 0}, 0, WHITE);
}
