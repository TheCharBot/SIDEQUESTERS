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
    DrawTexturePro(tex, village_windmill_animation[current_animation_frame], {pos.x * scale, pos.y * scale, float(VILLAGE_WINDMILL_WIDTH * scale), float(VILLAGE_WINDMILL_HEIGHT * scale)}, {0, 0}, 0, WHITE);
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

    DrawTexturePro(tex, start_bulldozer_animation[current_animation_frame], {pos.x * scale, pos.y * scale, float(START_BULLDOZER_WIDTH * scale), float(START_BULLDOZER_HEIGHT * scale)}, {0, 0}, 0, WHITE);

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

    DrawTexturePro(tex, start_portal_animation[current_animation_frame], {pos.x * scale, pos.y * scale, float(START_PORTAL_WIDTH * scale), float(START_PORTAL_HEIGHT * scale)}, {0, 0}, 0, WHITE);
}
