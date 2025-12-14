#include "map_loader.hpp"

Start_portal start_portal;

Texture2D starting_map;
Texture2D wrong_map;
Texture2D map_to_load;

int current_map;

Vector2 map_pos;

Rectangle temp_rect;


std::vector<std::unique_ptr<Entity>> entities;
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
        entities.clear();
        UnloadTexture(map_to_load);
        starting_map = LoadTexture(STARTING_MAP_TEX_PATH);
        map_to_load = starting_map;
        
        current_map = 0;
        //works, but inefficient, FIND BETTER WAY (later)
        // auto portal = std::make_unique<Start_portal>();
        // portal->load();

        // load_list.push_back(std::move(portal));
        

        map_surface_rects.push_back({float((MAP_1_RECT_1_X * scale)), float((MAP_1_RECT_1_Y * scale)), float(MAP_1_RECT_1_WIDTH * scale), float(MAP_1_RECT_1_HEIGHT * scale)});
        map_surface_rects.push_back({float((MAP_1_RECT_2_X * scale)), float((MAP_1_RECT_2_Y * scale)), float(MAP_1_RECT_2_WIDTH * scale), float(MAP_1_RECT_2_HEIGHT * scale)});
        map_surface_rects.push_back({float((MAP_1_RECT_3_X * scale)), float((MAP_1_RECT_3_Y * scale)), float(MAP_1_RECT_3_WIDTH * scale), float(MAP_1_RECT_3_HEIGHT * scale)});
        map_surface_rects.push_back({float((MAP_1_RECT_4_X * scale)), float((MAP_1_RECT_4_Y * scale)), float(MAP_1_RECT_4_WIDTH * scale), float(MAP_1_RECT_4_HEIGHT * scale)});
        
        entities.push_back(std::make_unique<Start_portal>());
        for (auto& e : entities) e->load();

        break;

    case 1:

        break;
    default:
        entities.clear();
        UnloadTexture(map_to_load);
        wrong_map = LoadTexture(WRONG_MAP_TEX_PATH);
        map_to_load = wrong_map;
        
        current_map = -1;

        break;
    }
};

void update_map()
{
    

    
};

void draw_map(){
   
    DrawTextureEx(map_to_load, map_pos, 0, scale, WHITE);
}