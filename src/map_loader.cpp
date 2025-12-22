#include "map_loader.hpp"

Start_portal start_portal;

Texture2D map_to_load;

int current_map;
int requested_map = 1;

Vector2 map_pos;

Rectangle temp_rect;

std::vector<Load_rects> map_load_rects;
std::vector<std::unique_ptr<Entity>> entities;
std::vector<Rectangle> collision_rects;

void init_map()
{
    map_pos.x = 0;
    map_pos.y = 0;
   
    // starting_map = LoadTexture("gfx/maps/map_1.png");
    // wrong_map = LoadTexture("gfx/maps/wrong_map.png");
}

void reset_player(Vector2 spawn) {
    player.pos = spawn;
    player.move_mode = 1;
}

void reset_loaded(){
    entities.clear();
    map_load_rects.clear();
    collision_rects.clear();
    UnloadTexture(map_to_load);
};

void load_map(int map)
{
    switch (map)
    {
    case 0:
        //resetting to default config for new map, plus spawning the player at a predetermined spot
        reset_player({0, 0});
        reset_loaded();
        //setting the map texture, i didn't want to figure out how to use any tmx software
        map_to_load = LoadTexture(WRONG_MAP_TEX_PATH);
        //setting the current map for sanity
        current_map = 0;

        break;
    case 1:
        reset_player({PLAYER_START_MAP_POS_X, PLAYER_START_MAP_POS_Y});
        reset_loaded();

        map_to_load = LoadTexture(STARTING_MAP_TEX_PATH);

        current_map = 1;
        //proprietary collisions for map 1 (can't reuse - sorry)
        collision_rects.push_back(MAP_1_RECT_1);
        collision_rects.push_back(MAP_1_RECT_2);
        collision_rects.push_back(MAP_1_RECT_3);
        collision_rects.push_back(MAP_1_RECT_4);
        //then filling the entity list with moving things to put in the map
        entities.push_back(std::make_unique<Start_portal>());
        entities.push_back(std::make_unique<Start_bulldozer>());
        for (auto &e : entities)
            e->load();
        break;

    case 2:
        reset_player({PLAYER_VILLAGE_MAP_POS_X, PLAYER_VILLAGE_MAP_POS_Y});
        reset_loaded();

        map_to_load = LoadTexture(VILLAGE_MAP_PATH);

        
        collision_rects.push_back(MAP_2_RECT_1);
        collision_rects.push_back(MAP_2_RECT_2);
        collision_rects.push_back(MAP_2_RECT_3);
        collision_rects.push_back(MAP_2_RECT_4);
        collision_rects.push_back(MAP_2_RECT_5);
        collision_rects.push_back(MAP_2_RECT_6);
        collision_rects.push_back(MAP_2_RECT_7);
        collision_rects.push_back(MAP_2_RECT_8);
        collision_rects.push_back(MAP_2_RECT_9);
        collision_rects.push_back(MAP_2_RECT_10);
        collision_rects.push_back(MAP_2_RECT_11);
        collision_rects.push_back(MAP_2_RECT_12);
        collision_rects.push_back(MAP_2_RECT_13);
        collision_rects.push_back(MAP_2_RECT_14);
        collision_rects.push_back(MAP_2_RECT_15);
        collision_rects.push_back(MAP_2_RECT_16);
        collision_rects.push_back(MAP_2_RECT_17);
        collision_rects.push_back(MAP_2_RECT_18);
        collision_rects.push_back(MAP_2_RECT_19);
        collision_rects.push_back(MAP_2_RECT_20);
        collision_rects.push_back(MAP_2_RECT_21);

        map_load_rects.push_back({MAP_2_LOAD_RECT_1, 3});
        map_load_rects.push_back({MAP_2_LOAD_RECT_2, 4});
        entities.push_back(std::make_unique<Village_windmill>());
        for (auto &e : entities)
            e->load();
        break;
    default:
        reset_player({0, 0});
        reset_loaded();

        map_to_load = LoadTexture(WRONG_MAP_TEX_PATH);

        current_map = 0;

        break;
    }
};

void update_map() {

};

void draw_map()
{

    DrawTextureEx(map_to_load, {0, 0}, 0, scale, WHITE);
}