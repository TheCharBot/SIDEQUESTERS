#include "entities_world.hpp"
#include "game_objects.hpp"

// 358, 302, coords for windmill

Village_windmill::Village_windmill()
{
    max_animation_frames = 4;
    current_animation_frame = 0;
    animation_frame_5 = 0;
    pos = {VILLAGE_WINDMILL_X, VILLAGE_WINDMILL_Y};
    rect = {pos.x + VILLAGE_WINDMILL_RECT_OFFSET_X, pos.y + VILLAGE_WINDMILL_RECT_OFFSET_Y, VILLAGE_WINDMILL_RECT_WIDTH, VILLAGE_WINDMILL_RECT_HEIGHT};
    game.collision_rects.push_back(rect);
    
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
    tex = get_texture(VILLAGE_WINDMILL_PATH);
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
    tex = get_texture(BULLDOZER_TEX_PATH);
}
void Start_bulldozer::update()
{
    rect = {pos.x, pos.y, START_BULLDOZER_WIDTH, START_BULLDOZER_HEIGHT};
    // checking if the player is at a Specific y value
    if (player.collision_rect.y <= BULLDOZER_TRIGGER_Y)
    {
        gui.is_inv_open = false;
        // running cutscene magic
        player.move_mode = 0;
        if (player.collision_rect.y > 160)
        {
            player.pos.y -= player.speed;
        }
        if (pos.x < MAX_BULLDOZER_X)
        {
            pos.x += BULLDOZER_SPEED;
        }
        if (CheckCollisionRecs(player.collision_rect, rect))
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

    tex = get_texture(PORTAL_TEX_PATH);
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
    game.collision_rects.push_back(rect1);
    game.collision_rects.push_back(rect2);
    game.collision_rects.push_back(rect3);
}

Big_tree::~Big_tree()
{
    if(tex.id != 1){
        UnloadTexture(tex);
    }
}

void Big_tree::load()
{
    tex = get_texture(BIG_TREE_TEX_PATH);
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
    game.collision_rects.push_back(rect);
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
    tex = get_texture(BIG_TREE_LEVELS_TREE_TRUNKS_TEX_PATH);
}

void Big_tree_level_tree_trunk::update()
{
    if (hit_flash_timer > 0.0f)
        hit_flash_timer -= GetFrameTime();
    if(CheckCollisionRecs(rect, player.active_attack_hitbox)){
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
        if(game.current_map == BIG_TREE_LEVEL_5){
            add_ground_item(game.ground_item_ids[Ground_item_names::BIG_TREE_LEVEL_5_KEY]);
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





Berry_bush::Berry_bush(int index)
{
    //TODO: MACROS!!!
    switch(index){
        case 0:
            pos = {529, 335};
            break;
        case 1:
            pos = {791, 335};
            break;
        case 2:
            pos = {682, 702};
            break;
        case 3:
            pos = {647, 857};
            break;
        case 4:
            pos = {823, 857};
            break;
        case 5:
            pos = {587, 555};
            break;
        case 6:
            pos = {331, 762};
            break;
        default:
            pos = {529, 335};
            break;
    }
    rect = {pos.x+5, pos.y+7, 25, 13};
    health = BERRY_BUSH_HEALTH;
    item_drop.ground_item_name = {};
    item_drop.pos = {pos.x+13, pos.y+10};
    item_drop.item = game.item_ids[Item_names::RED_BERRIES];
    flash_time = 0.0f;
}

Berry_bush::~Berry_bush()
{
    // if(tex.id != 0){
    //     UnloadTexture(tex);
    // } really only put if thres one - otherwise NO! it will MESS THINGS UP!
}

void Berry_bush::load()
{
    
    tex = get_texture(BERRY_BUSH_TEX_PATH);
        
    
}

void Berry_bush::update()
{
    if(CheckCollisionRecs(rect, player.active_attack_hitbox)){
        health -= player.active_damage;
        flash_time = ENEMY_IFRAME_TIME;
    }
    if(health < 0){
        switch(GetRandomValue(0, 2)){
            case 0:
                break;
            default:
                game.ground_items.push_back(item_drop);
                break;
        }
        // player.defeated_entities.push_back(name);
        dead = true;
    }
    flash_time-=GetFrameTime();
}

void Berry_bush::draw()
{
    DrawTexture(tex, pos.x, pos.y, flash_time > 0.0f ? RED : WHITE);
}


Ground_pot::Ground_pot(Vector2 wanted_pos)
{
    
    pos = wanted_pos;
    rect_rebuild();
    current_animation_frame = 0;
    animation_frame_5 = 0;
    max_animation_frames = 6;
    current_anim_arr = ground_pot_normal;
    broken = false;
}

Ground_pot::~Ground_pot()
{
}

void Ground_pot::load()
{
    
    tex = get_texture(POT_TEX_PATH);
}

void Ground_pot::update()
{
    
    if(CheckCollisionRecs(rect, player.collision_rect) && knockback_time <= 0){
        if(player.behavior_mode == Player::Behavior_mode::SPRINTING){
            // std::cout<< "yes sprint it worked";
            pot_break();
        }
        take_knockback({player.collision_rect.x + player.collision_rect.width  * 0.5f, player.collision_rect.y + player.collision_rect.height * 0.5f}, 200);
    }

    if(knockback_time > 0){
        update_knockback();
    }
    if(broken){
        animation_frame_5++;
        if (animation_frame_5 >= ANIMATION_INTERVAL)
        {
            current_animation_frame++;
            if (current_animation_frame >= max_animation_frames)
            {
                dead = true;
            }
            animation_frame_5 = 0;
        }
    }
    
}

void Ground_pot::draw()
{
    DrawTextureRec(tex, current_anim_arr[current_animation_frame], pos, WHITE);
}

void Ground_pot::take_knockback(Vector2 origin, int strength)
{
    Vector2 pot_center = {rect.x + rect.width * 0.5f, rect.y + rect.height * 0.5f};
    Vector2 dir = Vector2Subtract(pot_center, origin);

    if (Vector2Length(dir) < 0.001f) {
        dir = Vector2Negate(Vector2Normalize(player.movement));
    }

    dir = Vector2Normalize(dir);
    knockback_vel = Vector2Scale(dir, strength);
    knockback_time = 0.2f;
}

void Ground_pot::update_knockback()
{
    Vector2 pos_save = pos;
    Vector2 new_pos = Vector2Add(pos, Vector2Scale(knockback_vel, GetFrameTime()));

    // try X
    pos.x = new_pos.x;
    rect_rebuild();
    for(Rectangle &r : game.collision_rects){
        if (CheckCollisionRecs(rect, r)) pos.x = pos_save.x;
    }
    // try Y
    pos.y = new_pos.y;
    rect_rebuild();
    for(Rectangle &r : game.collision_rects){
        if (CheckCollisionRecs(rect, r)) pos.y = pos_save.y;
    }

    // decay the velocity 
    knockback_vel = Vector2Lerp(knockback_vel, {0, 0}, GetFrameTime() * 10);

    knockback_time -= GetFrameTime();
}

void Ground_pot::rect_rebuild()
{
    rect = {pos.x+25, pos.y+38, 14, 4}; //TODO: MACROS
}

void Ground_pot::pot_break()
{
    current_anim_arr = ground_pot_break;
    broken = true;
}

Village_windmill_grinder::Village_windmill_grinder()
{
    pos = {87, 14}; // TODO: MACROS
    current_anim_arr = village_windmill_grinder_idle;
    max_animation_frames = 8;
    rect = {pos.x+3, pos.y+111, 107, 40};
    add_collisions({rect});
}

Village_windmill_grinder::~Village_windmill_grinder()
{
}

void Village_windmill_grinder::load()
{
    tex = get_texture(VILLAGE_WINDMILL_GRINDER_TEX_PATH);
}

void Village_windmill_grinder::update()
{
    animation_frame_5++;
    if (animation_frame_5 >= ANIMATION_INTERVAL*5)
    {
        current_animation_frame++;
        if (current_animation_frame >= max_animation_frames)
        {
            current_animation_frame = 0;
        }
        animation_frame_5 = 0;
    }   
}

void Village_windmill_grinder::draw()
{
    DrawTextureRec(tex, current_anim_arr[current_animation_frame], pos, WHITE);
}
