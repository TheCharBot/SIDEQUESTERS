#include "map_loader.hpp"
Game_data game;



void init_map()
{
    
    game.broken_tile_tex = LoadTexture(BROKEN_TILE_TEX_PATH);
    game.door_lock_tex = LoadTexture(DOOR_LOCK_TEX_PATH);
    // starting_map = LoadTexture("gfx/maps/map_1.png");
    // wrong_map = LoadTexture("gfx/maps/wrong_map.png");
}

template<typename T, typename... Args>
void add_entity(Entity_names name, Args&&... args)
{
    

    if (std::find(player.defeated_entities.begin(),
                  player.defeated_entities.end(),
                  name)
        == player.defeated_entities.end())
    {
        auto entity = std::make_unique<T>(std::forward<Args>(args)...);
        entity->name = name;
        game.entities.push_back(std::move(entity));
    }
}


void add_ground_item(Ground_item item){
    if(std::find(player.picked_up_items.begin(), player.picked_up_items.end(), item.ground_item_name) != player.picked_up_items.end()){}
    else{game.ground_items.push_back(item);}
}
void add_locked_rect(Locked_rect rect){
    if(std::find(player.unlocked_doors.begin(), player.unlocked_doors.end(), rect.name) != player.unlocked_doors.end()){}
    else{game.locked_rects.push_back(rect);}
}

void add_collisions(std::initializer_list<Rectangle> rects)
{
    game.collision_rects.insert(game.collision_rects.end(), rects.begin(), rects.end());
}

void add_load_rects(std::initializer_list<Load_rects> rects)
{
    game.map_load_rects.insert(game.map_load_rects.end(), rects.begin(), rects.end());
}

void request_map(Map_names wanted_map, Vector2 wanted_player_spawn)
{
    game.requested_map = wanted_map;
    game.requested_player_pos = wanted_player_spawn;
}

// call before you change requested map, or something like that( might not work? might reload too many times?)
void reset_player(Vector2 spawn)
{
    player.pos = spawn;
    player.move_mode = 1;
}

void reset_loaded()
{
    unload_enemy_textures();
    game.entities.clear();
    game.map_load_rects.clear();
    game.collision_rects.clear();
    game.locked_rects.clear();
    game.broken_floor_tiles.clear();
    game.ground_items.clear();
    // unloading current map for efficiency
    if (game.map_to_load.id != 0)
    {
        UnloadTexture(game.map_to_load);
    }
    
    // unloading the current music to prevent mem leak
    // add back in when you have good music
    if(game.current_music.stream.buffer != nullptr){
        StopMusicStream(game.current_music);
        UnloadMusicStream(game.current_music);
        game.current_music = {};
    }
};

void kill_things_that_are_dead()
{
    
    game.entities.erase(
    std::remove_if(game.entities.begin(), game.entities.end(),
        [](const std::unique_ptr<Entity>& e) {
            return e->dead;
        }),
    game.entities.end());
    game.ground_items.erase(
    std::remove_if(game.ground_items.begin(), game.ground_items.end(),
        [](Ground_item& g) {
            return g.picked_up;
        }),
    game.ground_items.end());
}

void load_requested_map(){
    if (game.requested_map != WRONG_MAP)
    {
        if (game.current_map != game.requested_map)
        {
            game.fade_frame_timer = SCREEN_FADE_TIME;
            load_map(game.requested_map, game.requested_player_pos);
            
        }
        game.requested_map = WRONG_MAP;
    }
}

void remove_collision_rect(Rectangle rect)
{
    game.collision_rects.erase(
        std::remove_if(
            game.collision_rects.begin(),
            game.collision_rects.end(),
            [&](const Rectangle& r)
            {
                return r.x == rect.x &&
                       r.y == rect.y &&
                       r.width == rect.width &&
                       r.height == rect.height;
            }
        ),
        game.collision_rects.end()
    );
}

void remove_locked_rect(Locked_rect l_rect){
    game.locked_rects.erase(
        std::remove_if(
            game.locked_rects.begin(),
            game.locked_rects.end(),
            [&](const Locked_rect& l)
            {
                return l.rect.x == l_rect.rect.x &&
                       l.rect.y == l_rect.rect.y &&
                       l.rect.width == l_rect.rect.width &&
                       l.rect.height == l_rect.rect.height;
            }
        ),
        game.locked_rects.end()
    );
};


// map loader helper functions for easier organization and readability
void load_wrong_map()
{
    // resetting to default config for new map, plus spawning the player at a predetermined spot
    reset_player({0, 0});
    reset_loaded();
    // setting the map texture, i didn't want to figure out how to use any tmx software
    game.map_to_load = LoadTexture(WRONG_MAP_TEX_PATH);
    // setting the current map for sanity
    game.current_map = WRONG_MAP;
};



void load_start_map()
{

    reset_loaded();

    game.map_to_load = LoadTexture(STARTING_MAP_TEX_PATH);

    game.current_map = START_MAP;
    // proprietary collisions for map 1 (can't reuse - sorry)
    add_collisions({MAP_1_RECT_1,
                    MAP_1_RECT_2,
                    MAP_1_RECT_3,
                    MAP_1_RECT_4});

    // then filling the entity list with moving things to put in the map
    add_entity<Start_portal>(START_PORTAL);
    add_entity<Start_bulldozer>(START_BULLDOZER);
    for (auto &e : game.entities)
        e->load();
};

void load_village_map()
{
    reset_loaded();

    game.map_to_load = LoadTexture(VILLAGE_MAP_PATH);
    game.current_map = VILLAGE_MAP;
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
        {MAP_2_VILLAGE_HOUSE_2_LOAD, INSIDE_VILLAGE_HOUSE_2, PLAYER_VILLAGE_HOUSE_START_POS},         // check                                    // check //what'r you doing out here?
        {MAP_2_VILLAGE_HOUSE_3_LOAD, INSIDE_VILLAGE_HOUSE_3, PLAYER_VILLAGE_HOUSE_START_POS},         // check
        {MAP_2_VILLAGE_HOUSE_4_LOAD, INSIDE_VILLAGE_HOUSE_4, PLAYER_VILLAGE_HOUSE_START_POS},         // check
        {MAP_2_VILLAGE_HOUSE_5_LOAD, INSIDE_VILLAGE_HOUSE_5, PLAYER_VILLAGE_HOUSE_START_POS},
        {MAP_2_VILLAGE_HOUSE_6_LOAD, INSIDE_VILLAGE_HOUSE_6, PLAYER_VILLAGE_HOUSE_START_POS},
        {MAP_2_VILLAGE_HOUSE_7_LOAD, INSIDE_VILLAGE_HOUSE_7, PLAYER_VILLAGE_HOUSE_START_POS},

    });
    add_entity<Village_questgiver_1>(VILLAGE_QUESTGIVER_1);
    add_entity<Village_windmill>(VILLAGE_WINDMILL);
    for (auto &e : game.entities)
        e->load();
}
// village houses helper functions
void load_village_house_1()
{
    reset_loaded();
    game.map_to_load = LoadTexture(VILLAGE_HOUSE_1_PATH);
    game.current_map = INSIDE_VILLAGE_HOUSE_1;

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
    game.map_to_load = LoadTexture(VILLAGE_HOUSE_2_PATH);
    game.current_map = INSIDE_VILLAGE_HOUSE_2;
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
    game.map_to_load = LoadTexture(VILLAGE_HOUSE_3_PATH);
    game.current_map = INSIDE_VILLAGE_HOUSE_3;
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
    game.map_to_load = LoadTexture(VILLAGE_HOUSE_4_PATH);
    game.current_map = INSIDE_VILLAGE_HOUSE_4;
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
    game.map_to_load = LoadTexture(VILLAGE_HOUSE_5_PATH);
    game.current_map = INSIDE_VILLAGE_HOUSE_5;
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
    game.map_to_load = LoadTexture(VILLAGE_HOUSE_6_PATH);
    game.current_map = INSIDE_VILLAGE_HOUSE_6;
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
    game.map_to_load = LoadTexture(VILLAGE_HOUSE_7_PATH);
    game.current_map = INSIDE_VILLAGE_HOUSE_7;
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
    game.map_to_load = LoadTexture(VILLAGE_WINDMILL_INSIDE_PATH);
    game.current_map = INSIDE_VILLAGE_WINDMILL;
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
    game.current_music = LoadMusicStream(DARK_FOREST_MUS_PATH);
    game.map_to_load = LoadTexture(DARK_FOREST_NORTH_PATH);
    game.current_map = DARK_FOREST_NORTH;
    add_collisions({MAP_3_RECT_1,
                    MAP_3_RECT_2,
                    MAP_3_RECT_3,
                    MAP_3_RECT_4,
                    MAP_3_RECT_5,
                    MAP_3_RECT_6,
                    MAP_3_RECT_7});
    add_load_rects({{DARK_FOREST_NORTH_TO_VILLAGE, VILLAGE_MAP, VILLAGE_SPAWNPOINT_FROM_DARK_FOREST_NORTH},
                    {DARK_FOREST_NORTH_TO_DARK_FOREST_CENTER, DARK_FOREST_CENTER, DARK_FOREST_CENTER_SPAWNPOINT_FROM_DARK_FOREST_NORTH}});
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    for (auto &e : game.entities)
        e->load();
}

void load_dark_forest_south()
{
    reset_loaded();
    game.current_music = LoadMusicStream(DARK_FOREST_MUS_PATH);
    game.map_to_load = LoadTexture(DARK_FOREST_SOUTH_PATH);
    game.current_map = DARK_FOREST_SOUTH;
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
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    for (auto &e : game.entities)
        e->load();
    
}

void load_dark_forest_center(){
    reset_loaded();
    game.current_music = LoadMusicStream(DARK_FOREST_MUS_PATH);
    game.map_to_load = LoadTexture(DARK_FOREST_CENTER_PATH);
    game.current_map = DARK_FOREST_CENTER;
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
    for(int i = 0; i < 16; i++){ //adding a lot of 'em
        add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    }
    add_entity<Big_tree>(BIG_TREE);
    
    for (auto &e : game.entities)
        e->load();
    // PlayMusicStream(game.current_music);
}



void load_big_tree_level_1(){
    reset_loaded();
    game.map_to_load = LoadTexture(BIG_TREE_LEVEL_1_PATH);
    game.current_map = BIG_TREE_LEVEL_1;
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
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);

    add_ground_item(Big_tree_level_1_stick);

    for (auto &e : game.entities)
        e->load();
     //probably should find another way to do this 
     //actually its better now, slightly. still have to hardcode every map item. dangit
     //the drawbacks from not using an engine w/ a gui ^

};

void load_big_tree_level_2(){
    reset_loaded();
    game.map_to_load = LoadTexture(BIG_TREE_LEVEL_2_PATH);
    game.current_map = BIG_TREE_LEVEL_2;
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
    add_ground_item(Big_tree_level_2_key);
    add_locked_rect({BIG_TREE_LEVELS_BOTTOM_UP_LOCK_RECT, BIG_TREE_LEVEL_2_TO_BIG_TREE_LEVEL_3_LOCK}); 
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Big_tree_level_tree_trunk>(Entity_names::BIG_TREE_LEVEL_2_TREE_TRUNK, 2);
    for (auto &e : game.entities)
        e->load();
}

void load_big_tree_level_3(){
    reset_loaded();
    game.map_to_load = LoadTexture(BIG_TREE_LEVEL_3_PATH);
    game.current_map = BIG_TREE_LEVEL_3;
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
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Big_tree_level_tree_trunk>(Entity_names::BIG_TREE_LEVEL_3_TREE_TRUNK, 1);
    for (auto &e : game.entities)
        e->load();
}
void load_big_tree_level_4(){
    reset_loaded();
    game.map_to_load = LoadTexture(BIG_TREE_LEVEL_4_PATH);
    game.current_map = BIG_TREE_LEVEL_4;
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
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Big_tree_level_tree_trunk>(Entity_names::BIG_TREE_LEVEL_4_TREE_TRUNK, 1);
    for (auto &e : game.entities)
        e->load();
}
void load_big_tree_level_5(){
    reset_loaded();
    game.map_to_load = LoadTexture(BIG_TREE_LEVEL_5_PATH);
    game.current_map = BIG_TREE_LEVEL_5;
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
    // add_ground_item(Big_tree_level_5_key);//(different name)
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Big_tree_level_tree_trunk>(Entity_names::BIG_TREE_LEVEL_5_TREE_TRUNK, 1);
    for (auto &e : game.entities)
        e->load();
}
void load_big_tree_level_6(){
    reset_loaded();
    game.map_to_load = LoadTexture(BIG_TREE_LEVEL_6_PATH);
    game.current_map = BIG_TREE_LEVEL_6;
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
    add_locked_rect({BIG_TREE_LEVELS_BOTTOM_UP_LOCK_RECT, BIG_TREE_LEVEL_6_TO_BIG_TREE_LEVEL_7_LOCK}); 
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Big_tree_level_tree_trunk>(Entity_names::BIG_TREE_LEVEL_6_TREE_TRUNK, 3);
    for (auto &e : game.entities)
        e->load();
}
void load_big_tree_level_7(){
    reset_loaded();
    game.map_to_load = LoadTexture(BIG_TREE_LEVEL_7_PATH);
    game.current_map = BIG_TREE_LEVEL_7;
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
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    for (auto &e : game.entities)
        e->load();
}
void load_big_tree_level_8(){
    reset_loaded();
    game.map_to_load = LoadTexture(BIG_TREE_LEVEL_8_PATH);
    game.current_map = BIG_TREE_LEVEL_8;
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
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Big_tree_level_tree_trunk>(Entity_names::BIG_TREE_LEVEL_8_TREE_TRUNK, 2);
    for (auto &e : game.entities)
        e->load();
}
void load_big_tree_level_9(){
    reset_loaded();
    game.map_to_load = LoadTexture(BIG_TREE_LEVEL_9_PATH);
    game.current_map = BIG_TREE_LEVEL_9;
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
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Enemy_forest_scourge>(FOREST_SCOURGE);
    add_entity<Big_tree_level_tree_trunk>(Entity_names::BIG_TREE_LEVEL_9_TREE_TRUNK, 1);
    for (auto &e : game.entities)
        e->load();
}
void load_big_tree_level_10(){
    reset_loaded();
    game.map_to_load = LoadTexture(BIG_TREE_LEVEL_10_PATH);
    game.current_map = BIG_TREE_LEVEL_10;
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
    
    add_entity<The_Regrown>(Entity_names::THE_REGROWN);
        
    
    for (auto &e : game.entities)
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

        game.map_to_load = LoadTexture(WRONG_MAP_TEX_PATH);

        game.current_map = WRONG_MAP;

        break;
    }
    
    
};

void update_map() {

};

void draw_map()
{

    DrawTextureEx(game.map_to_load, {0, 0}, 0, 1, WHITE);
    
}

