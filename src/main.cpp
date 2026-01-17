#include "event_handler.hpp"

// ©2025, 2026 Charles Von Dollen, TheCharbot
// 16x16 sprites at 320x180 is just way too good

// Reminder: there must be one NPC that says "Smells like CHARACTER DEVELOPEMENT!"     
// done TODO: make map 3, 4, and 5
// done TODO: MAKE COMBAT/HEALTH SYSTEM!!!!
// done TODO: implement Big Tree Level 1
//TODO: FIX: SANITY: MAKE IMAGE NOTATION PROGRAM FOR YOUR OWN SAKE
//TODO: Make npc system, Start menu, save/load system, better player gfx, particles. Then your pretty much done!!!!(maybe)
int main()
{

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
        // DrawRectangle(player_normal_hitbox.x, player_normal_hitbox.y, player_normal_hitbox.width, player_normal_hitbox.height, GREEN);
        // DrawRectangle(player.attack_hitbox.x*scale, player.attack_hitbox.y*scale, player.attack_hitbox.width*scale, player.attack_hitbox.height*scale, RED);
        
        EndDrawing();
        
    }

    CloseWindow();
    return 0;
}