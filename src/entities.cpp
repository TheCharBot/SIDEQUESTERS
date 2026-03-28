#include "entities.hpp"

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
    tex = get_texture(VILLAGE_QUESTGIVER_1_PATH);
}

void Village_questgiver_1::update()
{
    if(IsKeyPressed(KEY_INTERACT) && CheckCollisionRecs(interact_rect, player.collision_rect) && !gui.global_textbox.is_textbox_open){
        if(!is_text_finished(VILLAGE_QUESTGIVER_1_FOUND_ITEM_TEXT)){
            for (int i = 0; i < 28; i++) {
                if (inventory_slots[i].filled_with->name== Item_names::SACRED_BARK) {
                    found_wanted_item = true;
                    break;
                };
            };
        }
        if(!is_text_finished(VILLAGE_QUESTGIVER_1_STORY_TEXT)){
            set_textbox_indice_text(0, {"Well, well, well.", NONE});
            set_textbox_indice_text(1, {"Now look what they did.", NONE});
            set_textbox_indice_text(2, {"Ruining our ground, and their reputation.", NONE});
            set_textbox_indice_text(3, {"They claimed to have possible accidents under control, but I still believe it's stupid to put a bulldozer factory in the sky.", NONE});
            set_textbox_indice_text(4, {"Like, how do they get them down from there?", NONE});
            set_textbox_indice_text(5, {"I guess . . . they found one way.", NONE});
            set_textbox_indice_text(6, {"Anyways, who are you?", NONE});
            set_textbox_indice_text(7, {"Ah, I see, the Chosen.", NONE});
            set_textbox_indice_text(8, {"Well, I don't see anything changing, even with you, but I could help you out.", NONE});
            set_textbox_indice_text(9, {"See, there is this gigantic tree, used to be the base of some group.", NONE});
            set_textbox_indice_text(10, {"I said used to because it was recently taken over by the Regrown.", NONE});
            set_textbox_indice_text(11, {"'What's that', ah, I'll tell you what, once you kill it.", NONE});
            set_textbox_indice_text(12, {"You're going to need to go into the Dark Forest just south of here and bring back some sort of proof that you did away with that thing.", NONE});
            set_textbox_indice_text(13, {"'What do I need', oh, I just need a little bit of bark from the tree, found only at the very top . . .", NONE});
            setup_textbox(14, VILLAGE_QUESTGIVER_1);
            add_finished_text(VILLAGE_QUESTGIVER_1_STORY_TEXT);
            //TODO: figure out what this guy is actually going to say
        }
        else if(is_text_finished(VILLAGE_QUESTGIVER_1_STORY_TEXT) && !found_wanted_item){
            set_textbox_indice_text(0, {"Now, what are you waiting for! Get a move on!", NONE});
            set_textbox_indice_text(1, {"I don't have all day! (or do I?)", NONE});
            setup_textbox(2, VILLAGE_QUESTGIVER_1);
        }
        
        else if(is_text_finished(VILLAGE_QUESTGIVER_1_STORY_TEXT) && !is_text_finished(VILLAGE_QUESTGIVER_1_FOUND_ITEM_TEXT) && found_wanted_item){
            set_textbox_indice_text(0, {"Oh! I wasn't expecting you to have actually done that! I guess my initial judgement of you was a bit harsh . . .", NONE});
            set_textbox_indice_text(1, {"Good job, in fact, you can keep that piece of bark, I just wanted that Regrown dead.", NONE});
            set_textbox_indice_text(2, {"Ah! You want to learn more about the Regrown? I'll tell you then!", NONE});
            set_textbox_indice_text(3, {"It is an evil tree spirit, mentally connected to every single Forest Scourge everywhere. At all times.", NONE});
            set_textbox_indice_text(4, {"You don't even know what a Forest Scourge is? I won't go too in-depth with them, just know that those little guys with the spears are what I'm talking about.", NONE});
            set_textbox_indice_text(5, {"But essentially, the Regrown controls them all, and by killing it, you have given them a taste of Freedom.", NONE});
            set_textbox_indice_text(6, {"Which could be good, as they could join our side, but who knows.", NONE});
            set_textbox_indice_text(7, {"Anyways, I've been talking too long, you had better be on your way, go do something!", NONE}); //right here make ties to other people in the village once the demo's out
            setup_textbox(8, VILLAGE_QUESTGIVER_1);
            add_finished_text(VILLAGE_QUESTGIVER_1_FOUND_ITEM_TEXT);
        }
        else{
            set_textbox_indice_text(0, {"Well, thanks for helping, but you're going to need to do more than just that to 'save the world'", NONE});
            set_textbox_indice_text(1, {"Go find someone in need of help, I'm sure you can. It's not perfect around here.", NONE});
            setup_textbox(2, VILLAGE_QUESTGIVER_1);
        }
        
    }
    
}

void Village_questgiver_1::draw()
{
    DrawTexturePro(tex, current_animation_arr[current_animation_frame], {pos.x, pos.y, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT}, {0, 0}, 0, WHITE);
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
