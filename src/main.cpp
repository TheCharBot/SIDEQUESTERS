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

//TODO: FIGURE OUT DIALOG STORAGE SYSTEM

//TODO: make Start menu
//TODO: make save/load system
//TODO: make better player gfx
//TODO: particles
//TODO: Make better flashing gfx and stuff for ground items, plus make animations work for broken ground tiles
int main()
{
   
    SetConfigFlags(FLAG_MSAA_4X_HINT); 
    InitWindow(WINDOW_WIDTH * scale, WINDOW_HEIGHT * scale, "SIDEQUESTERS");
    InitAudioDevice();
    SetTargetFPS(60);
    Image icon;
    icon = LoadImage("gfx/icon/icon.png");
    SetWindowIcon(icon);
    
    UnloadImage(icon);

    init_all();

    // Game Loop

    while (WindowShouldClose() == false)
    {
        // Game Logic

        update_all();

        BeginDrawing();
        ClearBackground(BLACK);

        // Game Drawing
        draw_all();
        
        // uncomment these for helpful debug stuff!
        // std::cout << GetFPS() << "\n";
        
        // DrawRectangle(player.attack_hitbox.x*scale, player.attack_hitbox.y*scale, player.attack_hitbox.width*scale, player.attack_hitbox.height*scale, RED);
        EndDrawing();
        
    }

    CloseWindow();
    return 0;
}