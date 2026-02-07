#include "map_loader.hpp"
Music current_music{};


Texture2D map_to_load;

Texture2D broken_tile_tex;

Map_names current_map;
Map_names requested_map;
Vector2 requested_player_pos;

Vector2 map_pos;

Rectangle temp_rect;

std::vector<Load_rects> map_load_rects;
std::vector<std::unique_ptr<Entity>> entities;
std::vector<Rectangle> collision_rects;
std::vector<Ground_item> ground_items;
std::vector<Vector2> broken_floor_tiles;

float fade_frame_timer = SCREEN_FADE_TIME; 

void init_map()
{
    map_pos.x = 0;
    map_pos.y = 0;
    broken_tile_tex = LoadTexture(BROKEN_TILE_TEX_PATH);
    // starting_map = LoadTexture("gfx/maps/map_1.png");
    // wrong_map = LoadTexture("gfx/maps/wrong_map.png");
}

void add_ground_item(Ground_item item){
    if(std::find(player.picked_up_items.begin(), player.picked_up_items.end(), item.ground_item_name) != player.picked_up_items.end()){}
    else{ground_items.push_back(item);}
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
    broken_floor_tiles.clear();
    ground_items.clear();
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
        {MAP_2_WINDMILL_LOAD, INSIDE_VILLAGE_WINDMILL, VILLAGE_WINDMILL_INSIDE_SPAWNPOINT_FROM_VILLAGE},   
        {MAP_2_DARK_FOREST_NORTH_LOAD, DARK_FOREST_NORTH, DARK_FOREST_NORTH_SPAWNPOINT_FROM_VILLAGE}, // check
        {MAP_2_DARK_FOREST_SOUTH_LOAD, DARK_FOREST_SOUTH, DARK_FOREST_SOUTH_SPAWNPOINT_FROM_VILLAGE}, // check
        {MAP_2_VILLAGE_HOUSE_1_LOAD, INSIDE_VILLAGE_HOUSE_1, PLAYER_VILLAGE_HOUSE_START_POS},         // check
        {MAP_2_VILLAGE_HOUSE_2_LOAD, INSIDE_VILLAGE_HOUSE_2, PLAYER_VILLAGE_HOUSE_START_POS},         // check                                    // check
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

void load_village_windmill(){
    reset_loaded();
    map_to_load = LoadTexture(VILLAGE_WINDMILL_INSIDE_PATH);
    current_map = INSIDE_VILLAGE_WINDMILL;
    add_collisions({
        INSIDE_WINDMILL_RECT_1,
        INSIDE_WINDMILL_RECT_2,
        INSIDE_WINDMILL_RECT_3,
        INSIDE_WINDMILL_RECT_4,
        INSIDE_WINDMILL_RECT_5,
        INSIDE_WINDMILL_RECT_6,
        INSIDE_WINDMILL_RECT_7,
        INSIDE_WINDMILL_RECT_8,
        INSIDE_WINDMILL_RECT_9,
        INSIDE_WINDMILL_RECT_10,
        INSIDE_WINDMILL_RECT_11,
        INSIDE_WINDMILL_RECT_12,
        INSIDE_WINDMILL_RECT_13,
        INSIDE_WINDMILL_RECT_14,
        INSIDE_WINDMILL_RECT_15,
        INSIDE_WINDMILL_RECT_16,
        INSIDE_WINDMILL_RECT_17,
        INSIDE_WINDMILL_RECT_18,
        INSIDE_WINDMILL_RECT_19,
        INSIDE_WINDMILL_RECT_20,
    });
    add_load_rects({
        {WINDMILL_INSIDE_TO_VILLAGE, VILLAGE_MAP, VILLAGE_WINDMILL_OUTSIDE_SPAWNPOINT}
    });
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
        // BIG_TREE_LEVEL_RECT_11, not for level 1
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
        BIG_TREE_STAIRS_TOP_UP_RECT,
    });
    add_load_rects({
        {BIG_TREE_LEVEL_1_TO_DARK_FOREST_CENTER, DARK_FOREST_CENTER, DARK_FOREST_CENTER_SPAWNPOINT_FROM_BIG_TREE_LEVEL_1},
        {BIG_TREE_STAIRS_TOP_UP_LOAD_RECT, BIG_TREE_LEVEL_2, BIG_TREE_DEFAULT_TOP_SPAWNPOINT}
    });
    
    add_ground_item(Big_tree_level_1_stick);
     //probably should find another way to do this 
     //actually its better now, slightly. still have to hardcode every map item. dangit
     //the drawbacks from not using an engine w/ a gui ^

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
        BIG_TREE_STAIRS_BOTTOM_UP_RECT_1,
        BIG_TREE_STAIRS_BOTTOM_UP_RECT_2,
        BIG_TREE_STAIRS_BOTTOM_UP_RECT_3
    });
    add_load_rects({
        {BIG_TREE_STAIRS_TOP_DOWN_LOAD_RECT, BIG_TREE_LEVEL_1, BIG_TREE_DEFAULT_TOP_SPAWNPOINT},
        {BIG_TREE_STAIRS_BOTTOM_UP_LOAD_RECT, BIG_TREE_LEVEL_3, BIG_TREE_DEFAULT_BOTTOM_SPAWNPOINT}
    });
    entities.push_back(std::make_unique<Big_tree_level_tree_trunk>(2));
    for (auto &e : entities)
        e->load();
}

void load_big_tree_level_3(){
    reset_loaded();
    map_to_load = LoadTexture(BIG_TREE_LEVEL_3_PATH);
    current_map = BIG_TREE_LEVEL_3;
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
        BIG_TREE_STAIRS_TOP_UP_RECT
    });
    add_load_rects({
        {BIG_TREE_STAIRS_BOTTOM_DOWN_LOAD_RECT, BIG_TREE_LEVEL_2, BIG_TREE_DEFAULT_BOTTOM_SPAWNPOINT},
        {BIG_TREE_STAIRS_TOP_UP_LOAD_RECT, BIG_TREE_LEVEL_4, BIG_TREE_DEFAULT_TOP_SPAWNPOINT}
    });
    entities.push_back(std::make_unique<Big_tree_level_tree_trunk>(1));
    for (auto &e : entities)
        e->load();
}
void load_big_tree_level_4(){
    reset_loaded();
    map_to_load = LoadTexture(BIG_TREE_LEVEL_4_PATH);
    current_map = BIG_TREE_LEVEL_4;
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
        BIG_TREE_STAIRS_BOTTOM_UP_RECT_1,
        BIG_TREE_STAIRS_BOTTOM_UP_RECT_2,
        BIG_TREE_STAIRS_BOTTOM_UP_RECT_3
    });
    add_load_rects({
        {BIG_TREE_STAIRS_TOP_DOWN_LOAD_RECT, BIG_TREE_LEVEL_3, BIG_TREE_DEFAULT_TOP_SPAWNPOINT},
        {BIG_TREE_STAIRS_BOTTOM_UP_LOAD_RECT, BIG_TREE_LEVEL_5, BIG_TREE_DEFAULT_BOTTOM_SPAWNPOINT}
    });
    entities.push_back(std::make_unique<Big_tree_level_tree_trunk>(1));
    for (auto &e : entities)
        e->load();
}
void load_big_tree_level_5(){
    reset_loaded();
    map_to_load = LoadTexture(BIG_TREE_LEVEL_5_PATH);
    current_map = BIG_TREE_LEVEL_5;
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
        BIG_TREE_STAIRS_TOP_UP_RECT
    });
    add_load_rects({
        {BIG_TREE_STAIRS_BOTTOM_DOWN_LOAD_RECT, BIG_TREE_LEVEL_4, BIG_TREE_DEFAULT_BOTTOM_SPAWNPOINT},
        {BIG_TREE_STAIRS_TOP_UP_LOAD_RECT, BIG_TREE_LEVEL_6, BIG_TREE_DEFAULT_TOP_SPAWNPOINT}
    });
    entities.push_back(std::make_unique<Big_tree_level_tree_trunk>(1));
    for (auto &e : entities)
        e->load();
}
void load_big_tree_level_6(){
    reset_loaded();
    map_to_load = LoadTexture(BIG_TREE_LEVEL_6_PATH);
    current_map = BIG_TREE_LEVEL_6;
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
        BIG_TREE_STAIRS_BOTTOM_UP_RECT_1,
        BIG_TREE_STAIRS_BOTTOM_UP_RECT_2,
        BIG_TREE_STAIRS_BOTTOM_UP_RECT_3
    });
    add_load_rects({
        {BIG_TREE_STAIRS_TOP_DOWN_LOAD_RECT, BIG_TREE_LEVEL_5, BIG_TREE_DEFAULT_TOP_SPAWNPOINT},
        {BIG_TREE_STAIRS_BOTTOM_UP_LOAD_RECT, BIG_TREE_LEVEL_7, BIG_TREE_DEFAULT_BOTTOM_SPAWNPOINT}
    });
    entities.push_back(std::make_unique<Big_tree_level_tree_trunk>(3));
    for (auto &e : entities)
        e->load();
}
void load_big_tree_level_7(){
    reset_loaded();
    map_to_load = LoadTexture(BIG_TREE_LEVEL_7_PATH);
    current_map = BIG_TREE_LEVEL_7;
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
        BIG_TREE_STAIRS_TOP_UP_RECT
    });
    add_load_rects({
        {BIG_TREE_STAIRS_BOTTOM_DOWN_LOAD_RECT, BIG_TREE_LEVEL_6, BIG_TREE_DEFAULT_BOTTOM_SPAWNPOINT},
        {BIG_TREE_STAIRS_TOP_UP_LOAD_RECT, BIG_TREE_LEVEL_8, BIG_TREE_DEFAULT_TOP_SPAWNPOINT}
    });
}
void load_big_tree_level_8(){
    reset_loaded();
    map_to_load = LoadTexture(BIG_TREE_LEVEL_8_PATH);
    current_map = BIG_TREE_LEVEL_8;
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
        BIG_TREE_STAIRS_BOTTOM_UP_RECT_1,
        BIG_TREE_STAIRS_BOTTOM_UP_RECT_2,
        BIG_TREE_STAIRS_BOTTOM_UP_RECT_3
    });
    add_load_rects({
        {BIG_TREE_STAIRS_TOP_DOWN_LOAD_RECT, BIG_TREE_LEVEL_7, BIG_TREE_DEFAULT_TOP_SPAWNPOINT},
        {BIG_TREE_STAIRS_BOTTOM_UP_LOAD_RECT, BIG_TREE_LEVEL_9, BIG_TREE_DEFAULT_BOTTOM_SPAWNPOINT}
    });
    entities.push_back(std::make_unique<Big_tree_level_tree_trunk>(2));
    for (auto &e : entities)
        e->load();
}
void load_big_tree_level_9(){
    reset_loaded();
    map_to_load = LoadTexture(BIG_TREE_LEVEL_9_PATH);
    current_map = BIG_TREE_LEVEL_9;
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
        BIG_TREE_STAIRS_TOP_UP_RECT
    });
    add_load_rects({
        {BIG_TREE_STAIRS_BOTTOM_DOWN_LOAD_RECT, BIG_TREE_LEVEL_8, BIG_TREE_DEFAULT_BOTTOM_SPAWNPOINT},
        {BIG_TREE_STAIRS_TOP_UP_LOAD_RECT, BIG_TREE_LEVEL_10, BIG_TREE_DEFAULT_TOP_SPAWNPOINT}
    });
    entities.push_back(std::make_unique<Big_tree_level_tree_trunk>(1));
    for (auto &e : entities)
        e->load();
}
void load_big_tree_level_10(){
    reset_loaded();
    map_to_load = LoadTexture(BIG_TREE_LEVEL_10_PATH);
    current_map = BIG_TREE_LEVEL_10;
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
    add_load_rects({
        {BIG_TREE_STAIRS_TOP_DOWN_LOAD_RECT, BIG_TREE_LEVEL_9, BIG_TREE_DEFAULT_TOP_SPAWNPOINT},
        
    });
    
    if(!player.defeated_bosses.the_regrown_defeated){ //little bit of boss key stuff!!!
        entities.push_back(std::make_unique<The_Regrown>()); 
    }
        
    
    for (auto &e : entities)
        e->load();
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
    case INSIDE_VILLAGE_WINDMILL:
        load_village_windmill();
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
    case BIG_TREE_LEVEL_3:
        load_big_tree_level_3();
        break;
    case BIG_TREE_LEVEL_4:
        load_big_tree_level_4();
        break;
    case BIG_TREE_LEVEL_5:
        load_big_tree_level_5();
        break;
    case BIG_TREE_LEVEL_6:
        load_big_tree_level_6();
        break;
    case BIG_TREE_LEVEL_7:
        load_big_tree_level_7();
        break;
    case BIG_TREE_LEVEL_8:
        load_big_tree_level_8();
        break;
    case BIG_TREE_LEVEL_9:
        load_big_tree_level_9();
        break;
    case BIG_TREE_LEVEL_10:
        load_big_tree_level_10();
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

void kill_things_that_are_dead()
{
    entities.erase(
    std::remove_if(entities.begin(), entities.end(),
        [](const std::unique_ptr<Entity>& e) {
            return e->dead;
        }),
    entities.end());
    ground_items.erase(
    std::remove_if(ground_items.begin(), ground_items.end(),
        [](Ground_item& g) {
            return g.picked_up;
        }),
    ground_items.end());
}

void load_requested_map(){
    if (requested_map != WRONG_MAP)
    {
        if (current_map != requested_map)
        {
            fade_frame_timer = SCREEN_FADE_TIME;
            load_map(requested_map, requested_player_pos);
            
        }
        requested_map = WRONG_MAP;
    }
}

void remove_collision_rect(Rectangle rect)
{
    collision_rects.erase(
        std::remove_if(
            collision_rects.begin(),
            collision_rects.end(),
            [&](const Rectangle& r)
            {
                return r.x == rect.x &&
                       r.y == rect.y &&
                       r.width == rect.width &&
                       r.height == rect.height;
            }
        ),
        collision_rects.end()
    );
}
