#include "config.hpp"

#include "event_handler.hpp"
//©2025 Charles Von Dollen, TheCharbot
//16x16 sprites at 320x180 is just way too good
int main() 
{
    InitWindow(WINDOW_WIDTH*scale, WINDOW_HEIGHT*scale, "SIDEQUESTERS");
    SetTargetFPS(60);
    Image icon;
    icon = LoadImage("gfx/icon/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
    
    init_all();
    
    //Game Loop
    
    while(WindowShouldClose() == false) 
    {
        //Game Logic
        update_all();

        
        BeginDrawing();
        ClearBackground(BLACK);
        
        //Game Drawing
        draw_all();
        // DrawRectangle(float((MAP_1_RECT_1_X * scale)), float((MAP_1_RECT_1_Y * scale)), float(MAP_1_RECT_1_WIDTH * scale), float(MAP_1_RECT_1_HEIGHT * scale), RED);
        // DrawRectangle(float((MAP_1_RECT_4_X * scale)), float((MAP_1_RECT_4_Y * scale)), float(MAP_1_RECT_4_WIDTH * scale), float(MAP_1_RECT_4_HEIGHT * scale), RED);
        // DrawRectangle(float((MAP_1_RECT_2_X * scale)), float((MAP_1_RECT_2_Y * scale)), float(MAP_1_RECT_2_WIDTH * scale), float(MAP_1_RECT_2_HEIGHT * scale), RED);
        // DrawRectangle(float((MAP_1_RECT_3_X * scale)), float((MAP_1_RECT_3_Y * scale)), float(MAP_1_RECT_3_WIDTH * scale), float(MAP_1_RECT_3_HEIGHT * scale), RED);

        // DrawRectangle(player_normal_hitbox.x, player_normal_hitbox.y, player_normal_hitbox.width, player_normal_hitbox.height, GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}