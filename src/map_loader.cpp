#include "map_loader.hpp"

Start_portal start_portal;

Texture2D map_to_load;

int current_map;
int requested_map = 1;

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

void reset_player(Vector2 spawn) {
    player_pos = spawn;
    player_move_mode = 1;
}


void load_map(int map)
{
    switch (map)
    {
    case 0:
        reset_player({0, 0});
        
        entities.clear();
        map_surface_rects.clear();

        UnloadTexture(map_to_load);

        map_to_load = LoadTexture(WRONG_MAP_TEX_PATH);

        current_map = 0;

        break;
    case 1:
        reset_player({PLAYER_START_MAP_POS_X, PLAYER_START_MAP_POS_Y});
        
        entities.clear();
        map_surface_rects.clear();

        UnloadTexture(map_to_load);

        map_to_load = LoadTexture(STARTING_MAP_TEX_PATH);

        current_map = 1;
        // works, but inefficient, FIND BETTER WAY (later)
        //  auto portal = std::make_unique<Start_portal>();
        //  portal->load();

        // load_list.push_back(std::move(portal));

        map_surface_rects.push_back({float((MAP_1_RECT_1_X)), float((MAP_1_RECT_1_Y)), float(MAP_1_RECT_1_WIDTH), float(MAP_1_RECT_1_HEIGHT)});
        map_surface_rects.push_back({float((MAP_1_RECT_2_X)), float((MAP_1_RECT_2_Y)), float(MAP_1_RECT_2_WIDTH), float(MAP_1_RECT_2_HEIGHT)});
        map_surface_rects.push_back({float((MAP_1_RECT_3_X)), float((MAP_1_RECT_3_Y)), float(MAP_1_RECT_3_WIDTH), float(MAP_1_RECT_3_HEIGHT)});
        map_surface_rects.push_back({float((MAP_1_RECT_4_X)), float((MAP_1_RECT_4_Y)), float(MAP_1_RECT_4_WIDTH), float(MAP_1_RECT_4_HEIGHT)});

        entities.push_back(std::make_unique<Start_portal>());
        entities.push_back(std::make_unique<Start_bulldozer>());
        for (auto &e : entities)
            e->load();

        break;

    // case 2:

    //     break;
    default:
        reset_player({0, 0});
        player_pos.x = 0;
        player_pos.y = 0;
        entities.clear();
        map_surface_rects.clear();

        UnloadTexture(map_to_load);

        map_to_load = LoadTexture(WRONG_MAP_TEX_PATH);

        current_map = 0;

        break;
    }
};

void update_map() {

};

void draw_map()
{

    DrawTextureEx(map_to_load, map_pos, 0, scale, WHITE);
}