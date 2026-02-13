#include "event_handler.hpp"

// event handler, draw_all, init_all, update_all, and camera stuff
void init_all()
{

    // current_music = LoadMusicStream(START_MUSIC_PATH);
    init_items();
    init_gui();
    init_map();
    init_player();
    init_vfx();
    request_map(START_MAP, {PLAYER_START_MAP_POS_X, PLAYER_START_MAP_POS_Y}); // default
    // request_map(DARK_FOREST_SOUTH, DARK_FOREST_SOUTH_SPAWNPOINT_FROM_VILLAGE);
    // request_map(DARK_FOREST_NORTH, DARK_FOREST_NORTH_SPAWNPOINT_FROM_DARK_FOREST_CENTER);
    // request_map(DARK_FOREST_CENTER, {273, 817});
    // request_map(BIG_TREE_LEVEL_9, {129, 32}); //placeholder for fighting the regrown
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

    //killing entities if they are dead
    kill_things_that_are_dead();
    update_vfx();

    //setting and clamping camera
    cam.target.x = player.pos.x - ((WINDOW_WIDTH) / 2) + (PLAYER_SPRITE_WIDTH / 2);
    cam.target.y = player.pos.y - ((WINDOW_HEIGHT) / 2) + (PLAYER_SPRITE_HEIGHT / 2);
    cam.target.x = Clamp(cam.target.x, 0, (map_to_load.width) - (WINDOW_WIDTH));
    cam.target.y = Clamp(cam.target.y, 0, (map_to_load.height) - (WINDOW_HEIGHT));

    //loading requested map at end of frame
    load_requested_map();
    update_gui();
    
}

void draw_all()
{
    BeginMode2D(cam);
    draw_map();
    for(Vector2 &v : broken_floor_tiles){
        DrawTexturePro(broken_tile_tex, BROKEN_TILE_RECT, {v.x, v.y, 16, 16}, {0, 0}, 0, WHITE); //look, i didnt want to make a whole new macro just for 16x16, deal with it
    }
    for(Ground_item &g : ground_items){
        
        DrawTexturePro(items_tex, g.item.img_rect, {g.pos.x, g.pos.y, 16, 16}, {0, 0}, 0, WHITE); // again ^
        
    }
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
    for(Locked_rect &l : locked_rects){
        DrawRectangle(l.rect.x, l.rect.y, l.rect.width, l.rect.height, Color{74, 84, 98, 255}); //box around thing, using color from aap64
        DrawRectangleLinesEx({l.rect.x, l.rect.y, l.rect.width, l.rect.height}, 1, BLACK); 
        //drawing 4 corners, sorry it mess
        DrawPixel(l.rect.x+1, l.rect.y+1, Color{51, 57, 65, 255});
        DrawPixel(l.rect.x+1, l.rect.y+l.rect.height-2, Color{51, 57, 65, 255});//TODO: MACROS FOR COLORS
        DrawPixel(l.rect.x+l.rect.width-2, l.rect.y+1, Color{51, 57, 65, 255});
        DrawPixel(l.rect.x+l.rect.width-2, l.rect.y+l.rect.height-2, Color{51, 57, 65, 255});

        //drawing lock texture
        DrawTextureEx(door_lock_tex,{l.rect.x+(l.rect.width/2-8), l.rect.y+(l.rect.height/2-8)}, 0, 1, WHITE);
    }
    // DrawRectangle(player.normal_hitbox.x, player.normal_hitbox.y, player.normal_hitbox.width, player.normal_hitbox.height, GREEN);
    EndMode2D();
    draw_gui();
    //probably will get cleaned up-best i can do now for screen fading
    if(fade_frame_timer >= 0){
        
        DrawRectangle(0, 0, map_to_load.width*scale, map_to_load.height*scale, Fade(BLACK, fade_frame_timer*6));
        fade_frame_timer -= GetFrameTime();
    }
    
};
