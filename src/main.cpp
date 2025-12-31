#include "event_handler.hpp"

// ©2025 Charles Von Dollen, TheCharbot
// 16x16 sprites at 320x180 is just way too good

// Reminder: there must be one NPC that says "Smells like CHARACTER DEVELOPEMENT!"

// done TODO: make map 3, 4, and 5
// TODO: make enemy AI and item / combat system
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

        // DrawRectangle(player_normal_hitbox.x, player_normal_hitbox.y, player_normal_hitbox.width, player_normal_hitbox.height, GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}