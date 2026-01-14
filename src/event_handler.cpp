#include "event_handler.hpp"

// event handler, draw_all, init_all, update_all, and camera stuff
void init_all()
{

    // current_music = LoadMusicStream(START_MUSIC_PATH);
    init_items();
    init_gui();
    init_map();
    init_player();

    // request_map(START_MAP, {PLAYER_START_MAP_POS_X, PLAYER_START_MAP_POS_Y});
    // request_map(DARK_FOREST_SOUTH, DARK_FOREST_SOUTH_SPAWNPOINT_FROM_VILLAGE);
    // request_map(DARK_FOREST_NORTH, DARK_FOREST_NORTH_SPAWNPOINT_FROM_DARK_FOREST_CENTER);
    request_map(DARK_FOREST_CENTER, {273, 817});
    cam.target = {0.0f, 0.0f};
    cam.offset = {0, 0};
    cam.rotation = 0.0f;
    cam.zoom = scale;

    PlayMusicStream(current_music);
    SetMusicVolume(current_music, 1.0f);
}

void update_all()
{
    UpdateMusicStream(current_music);

    update_map();
    update_player();
    for (auto &e : entities)
    {
        e->update();
    }

    //killing entities if they have 0 health
    entities.erase(
    std::remove_if(entities.begin(), entities.end(),
        [](const std::unique_ptr<Entity>& e) {
            return e->dead;
        }),
    entities.end());


    //setting and clamping camera
    cam.target.x = player.pos.x - ((WINDOW_WIDTH) / 2) + (PLAYER_SPRITE_WIDTH / 2);
    cam.target.y = player.pos.y - ((WINDOW_HEIGHT) / 2) + (PLAYER_SPRITE_HEIGHT / 2);
    cam.target.x = Clamp(cam.target.x, 0, (map_to_load.width) - (WINDOW_WIDTH));
    cam.target.y = Clamp(cam.target.y, 0, (map_to_load.height) - (WINDOW_HEIGHT));

    //loading requested map at end of frame
    if (requested_map != WRONG_MAP)
    {
        if (current_map != requested_map)
        {
            fade_frame_timer = SCREEN_FADE_TIME;
            load_map(requested_map, requested_player_pos);
            
        }
        requested_map = WRONG_MAP;
    }
    update_gui();
    
}

void draw_all()
{
    BeginMode2D(cam);
    draw_map();
    for (auto &e : entities)
    {
        e->draw();
        
    }

    draw_player();
    for (auto &e : entities)
    {
        if (e->rect.y > player.normal_hitbox.y)
        {
            e->draw();
            
        }
    }
    
    
    EndMode2D();
    draw_gui();
    //probably will get cleaned up-best i can do now for screen fading
    if(fade_frame_timer >= 0){
        
        DrawRectangle(0, 0, map_to_load.width*scale, map_to_load.height*scale, Fade(BLACK, fade_frame_timer*6));
        fade_frame_timer -= GetFrameTime();
    }
    
};
