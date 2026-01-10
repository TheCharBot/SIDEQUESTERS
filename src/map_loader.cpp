#include "map_loader.hpp"
Music current_music{};


Texture2D map_to_load;

Map_names current_map;
Map_names requested_map;
Vector2 requested_player_pos;

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

void add_collisions(std::initializer_list<Rectangle> rects)
{
    collision_rects.insert(collision_rects.end(), rects.begin(), rects.end());
}

void add_load_rects(std::initializer_list<Load_rects> rects)
{
    map_load_rects.insert(map_load_rects.end(), rects.begin(), rects.end());
}

void request_map(Map_names wanted_map, Vector2 wanted_player_spawn)
{
    requested_map = wanted_map;
    requested_player_pos = wanted_player_spawn;
}

// call before you change requested map, or something like that( might not work? might reload too many times?)
void reset_player(Vector2 spawn)
{
    player.pos = spawn;
    player.move_mode = 1;
}

void reset_loaded()
{
    entities.clear();
    map_load_rects.clear();
    collision_rects.clear();
    // unloading current map for efficiency
    if (map_to_load.id != 0)
    {
        UnloadTexture(map_to_load);
    }
    unload_enemy_textures();
    // unloading the current music to prevent mem leak
    // add back in when you have good music
    //  if(current_music.stream.buffer != nullptr){
    //      StopMusicStream(current_music);
    //      UnloadMusicStream(current_music);
    //      current_music = {};
    //  }
};

// map loader helper functions for easier organization and readability
void load_wrong_map()
{
    // resetting to default config for new map, plus spawning the player at a predetermined spot
    reset_player({0, 0});
    reset_loaded();
    // setting the map texture, i didn't want to figure out how to use any tmx software
    map_to_load = LoadTexture(WRONG_MAP_TEX_PATH);
    // setting the current map for sanity
    current_map = WRONG_MAP;
};



void load_start_map()
{

    reset_loaded();

    map_to_load = LoadTexture(STARTING_MAP_TEX_PATH);

    current_map = START_MAP;
    // proprietary collisions for map 1 (can't reuse - sorry)
    add_collisions({MAP_1_RECT_1,
                    MAP_1_RECT_2,
                    MAP_1_RECT_3,
                    MAP_1_RECT_4});

    // then filling the entity list with moving things to put in the map
    entities.push_back(std::make_unique<Start_portal>());
    entities.push_back(std::make_unique<Start_bulldozer>());
    for (auto &e : entities)
        e->load();
};

void load_village_map()
{
    reset_loaded();

    map_to_load = LoadTexture(VILLAGE_MAP_PATH);
    current_map = VILLAGE_MAP;
    add_collisions({
        MAP_2_RECT_1,
        MAP_2_RECT_2,
        MAP_2_RECT_3,
        MAP_2_RECT_4,
        MAP_2_RECT_5,
        MAP_2_RECT_6,
        MAP_2_RECT_7,
        MAP_2_RECT_8,
        MAP_2_RECT_9,
        MAP_2_RECT_10,
        MAP_2_RECT_11,
        MAP_2_RECT_12,
        MAP_2_RECT_13,
        MAP_2_RECT_14,
        MAP_2_RECT_15,
        MAP_2_RECT_16,
        MAP_2_RECT_17,
        MAP_2_RECT_18,
        MAP_2_RECT_19,
        MAP_2_RECT_20,
        MAP_2_RECT_21});
    add_load_rects({
        {MAP_2_DARK_FOREST_NORTH_LOAD, DARK_FOREST_NORTH, DARK_FOREST_NORTH_SPAWNPOINT_FROM_VILLAGE}, // check
        {MAP_2_DARK_FOREST_SOUTH_LOAD, DARK_FOREST_SOUTH, DARK_FOREST_SOUTH_SPAWNPOINT_FROM_VILLAGE}, // check
        {MAP_2_VILLAGE_HOUSE_1_LOAD, INSIDE_VILLAGE_HOUSE_1, PLAYER_VILLAGE_HOUSE_START_POS},         // check
        {MAP_2_VILLAGE_HOUSE_2_LOAD, INSIDE_VILLAGE_HOUSE_2, PLAYER_VILLAGE_HOUSE_START_POS},         // check
        //TODO: make inside village windmill
        {MAP_2_WINDMILL_LOAD, -1, {0, 0}},                                       // check
        {MAP_2_VILLAGE_HOUSE_3_LOAD, INSIDE_VILLAGE_HOUSE_3, PLAYER_VILLAGE_HOUSE_START_POS},         // check
        {MAP_2_VILLAGE_HOUSE_4_LOAD, INSIDE_VILLAGE_HOUSE_4, PLAYER_VILLAGE_HOUSE_START_POS},         // check
        {MAP_2_VILLAGE_HOUSE_5_LOAD, INSIDE_VILLAGE_HOUSE_5, PLAYER_VILLAGE_HOUSE_START_POS},
        {MAP_2_VILLAGE_HOUSE_6_LOAD, INSIDE_VILLAGE_HOUSE_6, PLAYER_VILLAGE_HOUSE_START_POS},
        {MAP_2_VILLAGE_HOUSE_7_LOAD, INSIDE_VILLAGE_HOUSE_7, PLAYER_VILLAGE_HOUSE_START_POS},

    });

    entities.push_back(std::make_unique<Village_windmill>());
    for (auto &e : entities)
        e->load();
}
// village houses helper functions
void load_village_house_1()
{
    reset_loaded();
    map_to_load = LoadTexture(VILLAGE_HOUSE_1_PATH);
    current_map = INSIDE_VILLAGE_HOUSE_1;

    add_collisions({
        VILLAGE_HOUSE_RECT_1,
        VILLAGE_HOUSE_RECT_2,
        VILLAGE_HOUSE_RECT_3,
        VILLAGE_HOUSE_RECT_4,
        VILLAGE_HOUSE_RECT_5,
        VILLAGE_HOUSE_1_RECT_6,
        VILLAGE_HOUSE_1_RECT_7,
    });
    add_load_rects({{VILLAGE_HOUSE_OUTSIDE_LOAD_RECT, VILLAGE_MAP, VILLAGE_HOUSE_1_OUTSIDE_SPAWNPOINT}});
};
void load_village_house_2()
{
    reset_loaded();
    map_to_load = LoadTexture(VILLAGE_HOUSE_2_PATH);
    current_map = INSIDE_VILLAGE_HOUSE_2;
    add_collisions({
        VILLAGE_HOUSE_RECT_1,
        VILLAGE_HOUSE_RECT_2,
        VILLAGE_HOUSE_RECT_3,
        VILLAGE_HOUSE_RECT_4,
        VILLAGE_HOUSE_RECT_5,
    });
    add_load_rects({{VILLAGE_HOUSE_OUTSIDE_LOAD_RECT, VILLAGE_MAP, VILLAGE_HOUSE_2_OUTSIDE_SPAWNPOINT}});
};
void load_village_house_3()
{
    reset_loaded();
    map_to_load = LoadTexture(VILLAGE_HOUSE_3_PATH);
    current_map = INSIDE_VILLAGE_HOUSE_3;
    add_collisions({
        VILLAGE_HOUSE_RECT_1,
        VILLAGE_HOUSE_RECT_2,
        VILLAGE_HOUSE_RECT_3,
        VILLAGE_HOUSE_RECT_4,
        VILLAGE_HOUSE_RECT_5,
    });
    add_load_rects({{VILLAGE_HOUSE_OUTSIDE_LOAD_RECT, VILLAGE_MAP, VILLAGE_HOUSE_3_OUTSIDE_SPAWNPOINT}});
};
void load_village_house_4()
{
    reset_loaded();
    map_to_load = LoadTexture(VILLAGE_HOUSE_4_PATH);
    current_map = INSIDE_VILLAGE_HOUSE_4;
    add_collisions({
        VILLAGE_HOUSE_RECT_1,
        VILLAGE_HOUSE_RECT_2,
        VILLAGE_HOUSE_RECT_3,
        VILLAGE_HOUSE_RECT_4,
        VILLAGE_HOUSE_RECT_5,
    });
    add_load_rects({{VILLAGE_HOUSE_OUTSIDE_LOAD_RECT, VILLAGE_MAP, VILLAGE_HOUSE_4_OUTSIDE_SPAWNPOINT}});
};
void load_village_house_5()
{
    reset_loaded();
    map_to_load = LoadTexture(VILLAGE_HOUSE_5_PATH);
    current_map = INSIDE_VILLAGE_HOUSE_5;
    add_collisions({
        VILLAGE_HOUSE_RECT_1,
        VILLAGE_HOUSE_RECT_2,
        VILLAGE_HOUSE_RECT_3,
        VILLAGE_HOUSE_RECT_4,
        VILLAGE_HOUSE_RECT_5,
    });
    add_load_rects({{VILLAGE_HOUSE_OUTSIDE_LOAD_RECT, VILLAGE_MAP, VILLAGE_HOUSE_5_OUTSIDE_SPAWNPOINT}});
};
void load_village_house_6()
{
    reset_loaded();
    map_to_load = LoadTexture(VILLAGE_HOUSE_6_PATH);
    current_map = INSIDE_VILLAGE_HOUSE_6;
    add_collisions({
        VILLAGE_HOUSE_RECT_1,
        VILLAGE_HOUSE_RECT_2,
        VILLAGE_HOUSE_RECT_3,
        VILLAGE_HOUSE_RECT_4,
        VILLAGE_HOUSE_RECT_5,
    });
    add_load_rects({{VILLAGE_HOUSE_OUTSIDE_LOAD_RECT, VILLAGE_MAP, VILLAGE_HOUSE_6_OUTSIDE_SPAWNPOINT}});
};
void load_village_house_7()
{
    reset_loaded();
    map_to_load = LoadTexture(VILLAGE_HOUSE_7_PATH);
    current_map = INSIDE_VILLAGE_HOUSE_7;
    add_collisions({
        VILLAGE_HOUSE_RECT_1,
        VILLAGE_HOUSE_RECT_2,
        VILLAGE_HOUSE_RECT_3,
        VILLAGE_HOUSE_RECT_4,
        VILLAGE_HOUSE_RECT_5,
    });
    add_load_rects({{VILLAGE_HOUSE_OUTSIDE_LOAD_RECT, VILLAGE_MAP, VILLAGE_HOUSE_7_OUTSIDE_SPAWNPOINT}});
};

void load_dark_forest_north()
{
    reset_loaded();
    map_to_load = LoadTexture(DARK_FOREST_NORTH_PATH);
    current_map = DARK_FOREST_NORTH;
    add_collisions({MAP_3_RECT_1,
                    MAP_3_RECT_2,
                    MAP_3_RECT_3,
                    MAP_3_RECT_4,
                    MAP_3_RECT_5,
                    MAP_3_RECT_6,
                    MAP_3_RECT_7});
    add_load_rects({{DARK_FOREST_NORTH_TO_VILLAGE, VILLAGE_MAP, VILLAGE_SPAWNPOINT_FROM_DARK_FOREST_NORTH},
                    {DARK_FOREST_NORTH_TO_DARK_FOREST_CENTER, DARK_FOREST_CENTER, DARK_FOREST_CENTER_SPAWNPOINT_FROM_DARK_FOREST_NORTH}});
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    for (auto &e : entities)
        e->load();
}

void load_dark_forest_south()
{
    reset_loaded();
    map_to_load = LoadTexture(DARK_FOREST_SOUTH_PATH);
    current_map = DARK_FOREST_SOUTH;
    add_collisions({
        MAP_4_RECT_1,
        MAP_4_RECT_2,
        MAP_4_RECT_3,
        MAP_4_RECT_4,
        MAP_4_RECT_5,
        MAP_4_RECT_6,
        MAP_4_RECT_7,
        MAP_4_RECT_8,
        MAP_4_RECT_9,
        MAP_4_RECT_10,
        MAP_4_RECT_11,
        MAP_4_RECT_12,
    });
    add_load_rects({
        {DARK_FOREST_SOUTH_TO_VILLAGE, VILLAGE_MAP, VILLAGE_SPAWNPOINT_FROM_DARK_FOREST_SOUTH},
        {DARK_FOREST_SOUTH_TO_DARK_FOREST_CENTER_1, DARK_FOREST_CENTER, DARK_FOREST_CENTER_SPAWNPOINT_FROM_DARK_FOREST_SOUTH_1},
        {DARK_FOREST_SOUTH_TO_DARK_FOREST_CENTER_2, DARK_FOREST_CENTER, DARK_FOREST_CENTER_SPAWNPOINT_FROM_DARK_FOREST_SOUTH_2}
    });
    //tons of lil dudes
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    entities.push_back(std::make_unique<Enemy_forest_scourge>());
    for (auto &e : entities)
        e->load();
}

void load_dark_forest_center(){
    reset_loaded();
    map_to_load = LoadTexture(DARK_FOREST_CENTER_PATH);
    current_map = DARK_FOREST_CENTER;
    add_collisions({
        MAP_5_RECT_1,
        MAP_5_RECT_2,
        MAP_5_RECT_3,
        MAP_5_RECT_4,
        MAP_5_RECT_5,
        MAP_5_RECT_6,
        MAP_5_RECT_7,
        MAP_5_RECT_8,
        MAP_5_RECT_9,
        MAP_5_RECT_10,
        MAP_5_RECT_11,
        MAP_5_RECT_12,
        MAP_5_RECT_13,
        MAP_5_RECT_14,
        MAP_5_RECT_15,
        MAP_5_RECT_16,
        MAP_5_RECT_17,
    });


    add_load_rects({
        {DARK_FOREST_CENTER_TO_DARK_FOREST_NORTH, DARK_FOREST_NORTH, DARK_FOREST_NORTH_SPAWNPOINT_FROM_DARK_FOREST_CENTER},
        {DARK_FOREST_CENTER_TO_DARK_FOREST_SOUTH_1, DARK_FOREST_SOUTH, DARK_FOREST_SOUTH_1_SPAWNPOINT_FROM_DARK_FOREST_CENTER},
        {DARK_FOREST_CENTER_TO_DARK_FOREST_SOUTH_2, DARK_FOREST_SOUTH, DARK_FOREST_SOUTH_2_SPAWNPOINT_FROM_DARK_FOREST_CENTER},
        {DARK_FOREST_CENTER_TO_BIG_TREE_LEVEL_1, BIG_TREE_LEVEL_1, BIG_TREE_LEVEL_1_SPAWNPOINT_FROM_DARK_FOREST_CENTER}
    });
    entities.push_back(std::make_unique<Big_tree>());
    for (auto &e : entities)
        e->load();
}



void load_big_tree_level_1(){
    reset_loaded();
    map_to_load = LoadTexture(BIG_TREE_LEVEL_1_PATH);
    current_map = BIG_TREE_LEVEL_1;
    add_collisions({
        BIG_TREE_LEVEL_RECT_1,
        BIG_TREE_LEVEL_RECT_2,
        BIG_TREE_LEVEL_RECT_3,
        BIG_TREE_LEVEL_RECT_4,
        BIG_TREE_LEVEL_RECT_5,
        BIG_TREE_LEVEL_RECT_6,
        BIG_TREE_LEVEL_RECT_7,
        BIG_TREE_LEVEL_RECT_8,
        BIG_TREE_LEVEL_RECT_9,
        BIG_TREE_LEVEL_RECT_10,
        // BIG_TREE_LEVEL_RECT_11,
        BIG_TREE_LEVEL_RECT_12,
        BIG_TREE_LEVEL_RECT_13,
        BIG_TREE_LEVEL_RECT_14,
        BIG_TREE_LEVEL_RECT_15,
        BIG_TREE_LEVEL_RECT_16,
        BIG_TREE_LEVEL_RECT_17,
        BIG_TREE_LEVEL_RECT_18,
        BIG_TREE_LEVEL_RECT_19,
        BIG_TREE_LEVEL_RECT_20,
        BIG_TREE_LEVEL_RECT_21,
        BIG_TREE_LEVEL_RECT_22,
        BIG_TREE_LEVEL_1_RECT_1
    });
    add_load_rects({
        {BIG_TREE_LEVEL_1_TO_DARK_FOREST_CENTER, DARK_FOREST_CENTER, DARK_FOREST_CENTER_SPAWNPOINT_FROM_BIG_TREE_LEVEL_1},
        {BIG_TREE_LEVEL_1_TO_BIG_TREE_LEVEL_2, BIG_TREE_LEVEL_2, BIG_TREE_LEVEL_2_SPAWNPOINT_BIG_TREE_LEVEL_1}
    });
    

};

void load_big_tree_level_2(){
    reset_loaded();
    map_to_load = LoadTexture(BIG_TREE_LEVEL_2_PATH);
    current_map = BIG_TREE_LEVEL_2;
    add_collisions({
        BIG_TREE_LEVEL_RECT_1,
        BIG_TREE_LEVEL_RECT_2,
        BIG_TREE_LEVEL_RECT_3,
        BIG_TREE_LEVEL_RECT_4,
        BIG_TREE_LEVEL_RECT_5,
        BIG_TREE_LEVEL_RECT_6,
        BIG_TREE_LEVEL_RECT_7,
        BIG_TREE_LEVEL_RECT_8,
        BIG_TREE_LEVEL_RECT_9,
        BIG_TREE_LEVEL_RECT_10,
        BIG_TREE_LEVEL_RECT_11,
        BIG_TREE_LEVEL_RECT_12,
        BIG_TREE_LEVEL_RECT_13,
        BIG_TREE_LEVEL_RECT_14,
        BIG_TREE_LEVEL_RECT_15,
        BIG_TREE_LEVEL_RECT_16,
        BIG_TREE_LEVEL_RECT_17,
        BIG_TREE_LEVEL_RECT_18,
        BIG_TREE_LEVEL_RECT_19,
        BIG_TREE_LEVEL_RECT_20,
        BIG_TREE_LEVEL_RECT_21,
        BIG_TREE_LEVEL_RECT_22,
    });
}

void load_map(Map_names map, Vector2 new_player_pos)
{
    reset_player(new_player_pos);
    switch (map)
    {
    case WRONG_MAP:
        load_wrong_map();
        break;
    case START_MAP:
        load_start_map();
        break;

    case VILLAGE_MAP:
        load_village_map();
        break;

    case INSIDE_VILLAGE_HOUSE_1:
        load_village_house_1();
        break;
    case INSIDE_VILLAGE_HOUSE_2:
        load_village_house_2();
        break;
    case INSIDE_VILLAGE_HOUSE_3:
        load_village_house_3();
        break;
    case INSIDE_VILLAGE_HOUSE_4:
        load_village_house_4();
        break;
    case INSIDE_VILLAGE_HOUSE_5:
        load_village_house_5();
        break;
    case INSIDE_VILLAGE_HOUSE_6:
        load_village_house_6();
        break;
    case INSIDE_VILLAGE_HOUSE_7:
        load_village_house_7();
        break;

    case DARK_FOREST_NORTH:
        load_dark_forest_north();
        break;
    case DARK_FOREST_SOUTH:
        load_dark_forest_south();
        break;
    case DARK_FOREST_CENTER:
        load_dark_forest_center();
        break;
    case BIG_TREE_LEVEL_1:
        load_big_tree_level_1();
        break;
    case BIG_TREE_LEVEL_2:
        load_big_tree_level_2();
        break;
    
    default:
        // loading the wrong map, or loading a nonexistent map
        reset_player({0, 0});
        reset_loaded();

        map_to_load = LoadTexture(WRONG_MAP_TEX_PATH);

        current_map = WRONG_MAP;

        break;
    }
};

void update_map() {

};

void draw_map()
{

    DrawTextureEx(map_to_load, {0, 0}, 0, 1, WHITE);
}