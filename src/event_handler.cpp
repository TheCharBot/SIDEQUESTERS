#include "event_handler.hpp"



// event handler, draw_all, init_all, update_all, and camera stuff
void init_all()
{

    // game.current_music = LoadMusicStream(START_MUSIC_PATH);
    init_items();
    init_gui();
    init_map();
    init_player();
    init_vfx();
    init_sfx();
    cam.target = {0.0f, 0.0f};
    cam.offset = {0, 0};
    cam.rotation = 0.0f;
    cam.zoom = scale;
    game.state = START_MENU;
    PlayMusicStream(game.current_music);
    SetMusicVolume(game.current_music, 1.0f);
    request_map(START_MAP, {PLAYER_START_MAP_POS_X, PLAYER_START_MAP_POS_Y}); // default
    load_requested_map();
    if(game.state <= Game_states::OPTIONS){
        init_start_menu();
    }
    // request_map(START_MAP, {PLAYER_START_MAP_POS_X, PLAYER_START_MAP_POS_Y}); // default
    // request_map(DARK_FOREST_SOUTH, DARK_FOREST_SOUTH_SPAWNPOINT_FROM_VILLAGE);
    // request_map(DARK_FOREST_NORTH, DARK_FOREST_NORTH_SPAWNPOINT_FROM_DARK_FOREST_CENTER);
    // request_map(DARK_FOREST_CENTER, {273, 817});
    // request_map(BIG_TREE_LEVEL_9, {129, 32}); //placeholder for fighting the regrown
    // request_map(VILLAGE_MAP, VILLAGE_HOUSE_1_OUTSIDE_SPAWNPOINT);
    

    

    
}

void update_all()
{
    
    if(!IsMusicStreamPlaying(game.current_music)){
        PlayMusicStream(game.current_music);
    }
    UpdateMusicStream(game.current_music);
    update_sfx();
    if(game.state <= Game_states::OPTIONS && !gui.start_menu_unloaded){
        //implement start menu code here
        start_menu_update();
        return;
    }
    
    update_map();
    update_player();
    for (auto &e : game.entities)
    {
        e->update();
    }

    //killing game.entities if they are dead
    kill_things_that_are_dead();
    update_vfx();

    //setting and clamping camera
    cam.target.x = player.pos.x - ((WINDOW_WIDTH) / 2) + (PLAYER_SPRITE_WIDTH / 2);
    cam.target.y = player.pos.y - ((WINDOW_HEIGHT) / 2) + (PLAYER_SPRITE_HEIGHT / 2);
    cam.target.x = Clamp(cam.target.x, 0, (game.map_to_load.width) - (WINDOW_WIDTH));
    cam.target.y = Clamp(cam.target.y, 0, (game.map_to_load.height) - (WINDOW_HEIGHT));

    //loading requested map at end of frame
    load_requested_map();
    update_gui();
    
}

void draw_all()
{
    
    if(game.state <= Game_states::OPTIONS && !gui.start_menu_unloaded){
        //implement start menu code here
        start_menu_draw();
        return;
    }
    BeginMode2D(cam);
    draw_map();
    for(Vector2 &v : game.broken_floor_tiles){
        DrawTexturePro(game.broken_tile_tex, BROKEN_TILE_RECT, {v.x, v.y, 16, 16}, {0, 0}, 0, WHITE); //look, i didnt want to make a whole new macro just for 16x16, deal with it
    }
    for(Ground_item &g : game.ground_items){
        
        DrawTexturePro(items_tex, g.item.img_rect, {g.pos.x, g.pos.y, 16, 16}, {0, 0}, 0, WHITE); // again ^
        
    }
    for (auto &e : game.entities)
    {
        e->draw();
        
    }

    draw_player();
    for (auto &e : game.entities)
    {
        if (e->rect.y > player.normal_hitbox.y)
        {
            e->draw();
            
        }
    }
    for(Locked_rect &l : game.locked_rects){
        DrawRectangle(l.rect.x, l.rect.y, l.rect.width, l.rect.height, GUI_LIGHT_GRAY); //box around thing, using color from aap64
        DrawRectangleLinesEx({l.rect.x, l.rect.y, l.rect.width, l.rect.height}, 1, BLACK); 
        //drawing 4 corners, sorry it mess
        DrawPixel(l.rect.x+1, l.rect.y+1, GUI_DARK_GRAY);
        DrawPixel(l.rect.x+1, l.rect.y+l.rect.height-2, GUI_DARK_GRAY);
        DrawPixel(l.rect.x+l.rect.width-2, l.rect.y+1, GUI_DARK_GRAY);
        DrawPixel(l.rect.x+l.rect.width-2, l.rect.y+l.rect.height-2, GUI_DARK_GRAY);

        //drawing lock texture
        DrawTextureEx(game.door_lock_tex,{l.rect.x+(l.rect.width/2-8), l.rect.y+(l.rect.height/2-8)}, 0, 1, WHITE); //just the offsets - i dont think macros are too nessecary
    }
    // DrawRectangle(player.normal_hitbox.x, player.normal_hitbox.y, player.normal_hitbox.width, player.normal_hitbox.height, GREEN);
    EndMode2D();
    draw_gui();


    
    


    //probably will get cleaned up-best i can do now for screen fading
    if(game.fade_frame_timer >= 0){
        
        DrawRectangle(0, 0, game.map_to_load.width*scale, game.map_to_load.height*scale, Fade(BLACK, game.fade_frame_timer*6));
        game.fade_frame_timer -= GetFrameTime();
    }

    
    
    
};
