#include "event_handler.hpp"

//Official WNAR Build
//

// "Who Needs A Reason?"


// ©2025, 2026 Charles Von Dollen, TheCharbot
// 16x16 sprites at 320x180 is just way too good

// Reminder: there must be one NPC that says "Smells like CHARACTER DEVELOPEMENT!"
// done TODO: make map 3, 4, and 5
// done TODO: MAKE COMBAT/HEALTH SYSTEM!!!!
// done TODO: implement Big Tree Level 1
// done TODO: ADD GLOBAL HITSTOP <<<<<<<<<<<<<<-------------
// done TODO: make ground item system
// done TODO: IMPLEMENT HEALTHBAR

//TODO: FIX: SANITY: MAKE IMAGE NOTATION PROGRAM FOR YOUR OWN SAKE


//Current TODO: finish the dungeon

//done TODO: URGENT: Clean everything up, make more content, spawn enemies more, finish the dungeon, then make the dialog system

//done TODO: get the text to look better, use antialiasing or something

//done TODO: Make npc system

//done TODO: implement SFX system

//done TODO: make a Game_data struct, change everything to work w/ it

//later TODO: FIGURE OUT DIALOG STORAGE SYSTEM

//done TODO: get default save to work
//TODO: finish options, credits, and achievements in Start menu
//done TODO: make save/load system <- CURRENT
//done TODO: GET IMAGES TO WORK ON START MENU
//done TODO: make the save selector, then save/load system, then picture/icon system on the save selector

//done TODO: Make Stamina GUI
//TODO: make a more populated village, and furnish the rest of the homes
//done TODO: make better player gfx
//nope TODO: particles?
//maybe later TODO: Make better flashing gfx and stuff for ground items, plus make animations work for broken ground tiles
//TODO: Full game: make dialog choice system

// #define _DEBUG

int main()
{
    
    // load_config_state();//TODO: uncomment in final release
    // std::cout << scale;
    SetConfigFlags(FLAG_MSAA_4X_HINT); 
    
    InitWindow(WINDOW_WIDTH * scale, WINDOW_HEIGHT * scale, "SIDEQUESTERS");
    if(!IsWindowFullscreen() && GetScreenWidth() >= GetMonitorWidth(GetCurrentMonitor()) && GetScreenHeight() >= GetMonitorHeight(GetCurrentMonitor())){
        ToggleFullscreen();
        scale = GetMonitorWidth(GetCurrentMonitor())/WINDOW_WIDTH;
    }
    SetExitKey(KEY_F10); //uncomment for turning off esc key close window
    InitAudioDevice();
    SetTargetFPS(60);
    Image icon;
    icon = LoadImage("gfx/icon/icon.png");
    SetWindowIcon(icon);
    
    UnloadImage(icon);

    init_all();
    // Game Loop
    
    game.new_scale = scale;
    while (WindowShouldClose() == false)
    {
        // Game Logic

        update_all();
        // std::cout << player.current_stamina << "\n";

        BeginDrawing();
        ClearBackground(BLACK);

        // Game Drawing
        draw_all();
        
        // uncomment these for helpful debug stuff!
        // std::cout << GetFPS() << "\n";
        
        
        EndDrawing();
        
    }
    // game.new_scale = 3;
    // if(game.state == Game_states::GAMEPLAY){
    //     save_index_state(game.save_slot);
    // } //TODO: Uncomment in final release
    if(scale != game.new_scale){
        scale = game.new_scale;
    }
    save_config_state();
    
    CloseWindow();
    return 0;
}