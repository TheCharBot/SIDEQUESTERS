#include "map_loader.hpp"

Texture2D starting_map;
Texture2D wrong_map;

Texture2D map_to_load;

Vector2 map_pos;

Rectangle temp_rect;

std::vector<Rectangle> map_surface_rects;


void init_map()
{
    map_pos.x = 0;
    map_pos.y = 0;
    // starting_map = LoadTexture("gfx/maps/map_1.png");
    // wrong_map = LoadTexture("gfx/maps/wrong_map.png");
}

void load_map(int map)
{
    switch (map)
    {
    case 0:
        UnloadTexture(map_to_load);
        starting_map = LoadTexture(STARTING_MAP_TEX_PATH);
        map_to_load = starting_map;
        //works, but inefficient, FIND BETTER WAY (later)
        map_surface_rects.push_back({float((MAP_1_RECT_1_X * scale)), float((MAP_1_RECT_1_Y * scale)), float(MAP_1_RECT_1_WIDTH * scale), float(MAP_1_RECT_1_HEIGHT * scale)});
        map_surface_rects.push_back({float((MAP_1_RECT_2_X * scale)), float((MAP_1_RECT_2_Y * scale)), float(MAP_1_RECT_2_WIDTH * scale), float(MAP_1_RECT_2_HEIGHT * scale)});
        map_surface_rects.push_back({float((MAP_1_RECT_3_X * scale)), float((MAP_1_RECT_3_Y * scale)), float(MAP_1_RECT_3_WIDTH * scale), float(MAP_1_RECT_3_HEIGHT * scale)});
        map_surface_rects.push_back({float((MAP_1_RECT_4_X * scale)), float((MAP_1_RECT_4_Y * scale)), float(MAP_1_RECT_4_WIDTH * scale), float(MAP_1_RECT_4_HEIGHT * scale)});
        // temp_rect = {float(cam.offset.x + (197 * scale)), float(cam.offset.y + (184 * scale)), float(86 * scale), float(82 * scale)};
        break;

    case 1:

        break;
    default:
        UnloadTexture(map_to_load);
        wrong_map = LoadTexture(WRONG_MAP_TEX_PATH);
        map_to_load = wrong_map;
        break;
    }
};

void update_map()
{
    

    
};

void draw_map(){
   
    DrawTextureEx(map_to_load, map_pos, 0, scale, WHITE);
}