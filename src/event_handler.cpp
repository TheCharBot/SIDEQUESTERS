#include "event_handler.hpp"

Game_save test_save;

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
    // request_map(DARK_FOREST_SOUTH, DARK_FOREST_SOUTH_SPAWNPOINT_FROM_VILLAGE);
    // request_map(DARK_FOREST_SOUTH, DARK_FOREST_SOUTH_SPAWNPOINT_FROM_VILLAGE);
    // request_map(DARK_FOREST_NORTH, DARK_FOREST_NORTH_SPAWNPOINT_FROM_DARK_FOREST_CENTER);
    // request_map(DARK_FOREST_CENTER, {273, 817});
    
    // request_map(VILLAGE_MAP, VILLAGE_HOUSE_1_OUTSIDE_SPAWNPOINT);
    // request_map(BIG_TREE_LEVEL_9, {129, 32}); //placeholder for fighting the regrown
    load_requested_map();
    
    init_start_menu();
    
    
    // player.defeated_entities.push_back(THE_REGROWN);
    

    

    
}



void update_all()
{
    
    // if(IsKeyPressed(KEY_O)){
    //     save_index_state(1);
    // }
    // if(IsKeyPressed(KEY_P)){
    //     save_index_state(2);
    // }
    if(!IsMusicStreamPlaying(game.current_music)){
        PlayMusicStream(game.current_music);
    }
    UpdateMusicStream(game.current_music);
    
    update_sfx();
    switch(game.state){
        //implement start menu code here
        case START_MENU:
            start_menu_update();
            return;
        case SAVE_SLOTS:
            start_menu_save_slots_screen_update(); //just cuz theyre only used once - im so done with the mess ive made
            return;
        case CREDITS:
            start_menu_credits_screen_update();
            return;
        case OPTIONS:
            options_screen_update();
            return;
        case ACHIEVEMENTS:
            achievements_screen_update();
            return;
        default:
            break;
    }
    
    if(IsKeyPressed(KEY_ESCAPE)){
        if(game.state != PAUSE_MENU){
            game.state = PAUSE_MENU;
            gui.pause_menu_versions_of_menus = true;
        }
        else if(game.state == PAUSE_MENU){
            game.state = GAMEPLAY;
            gui.pause_menu_versions_of_menus = false;
        }
    }
    if(game.state == Game_states::PAUSE_MENU){
        pause_menu_update();
    }
    
    if(!gui.is_inv_open && game.state == Game_states::GAMEPLAY){  
        if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_SAVE]) && game.state == Game_states::GAMEPLAY){
            save_index_state(game.save_slot);
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
        cam.target = Vector2Lerp(cam.target, {player.pos.x - ((WINDOW_WIDTH) / 2) + (DEFAULT_SPRITE_WIDTH/2), player.pos.y - ((WINDOW_HEIGHT) / 2) + (DEFAULT_SPRITE_HEIGHT/2)}, (GetFrameTime()*4));

        cam.target.x = Clamp(cam.target.x, 0, (game.map_to_load.width) - (WINDOW_WIDTH));
        cam.target.y = Clamp(cam.target.y, 0, (game.map_to_load.height) - (WINDOW_HEIGHT));

        //loading requested map at end of frame
        load_requested_map();
        
    }
    update_gui();
    
}

void draw_all()
{
    switch(game.state){
        //implement start menu code here
        case START_MENU:
            start_menu_draw();
            return;
        case SAVE_SLOTS:
            start_menu_draw(); //just cuz theyre only used once - im so done with the mess ive made
            return;
        case CREDITS:
            start_menu_draw();
            return;
        case OPTIONS:
            options_screen_draw();
            return;
        case ACHIEVEMENTS:
            achievements_screen_draw();
            return;
        default:
            break;
    }
    
    BeginMode2D(cam);
    draw_map();

    draw_broken_floor_tiles();
    draw_ground_items();

    
    sort_and_draw_player_and_entities();
    draw_locked_doors();

    // DrawRectangle(player.collision_rect.x, player.collision_rect.y, player.collision_rect.width, player.collision_rect.height, GREEN);
    EndMode2D();
    draw_gui();
    if(game.state == Game_states::PAUSE_MENU){
        pause_menu_draw();
    }

    
    


    //probably will get cleaned up-best i can do now for screen fading
    if(game.fade_frame_timer >= 0){
        
        DrawRectangle(0, 0, game.map_to_load.width*scale, game.map_to_load.height*scale, Fade(BLACK, game.fade_frame_timer*6));
        game.fade_frame_timer -= GetFrameTime();
    }

    
    
    
};
