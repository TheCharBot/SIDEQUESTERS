#include "game_funcs.hpp"
Game_data game;




void init_map()
{
    
    game.broken_tile_tex = get_texture(BROKEN_TILE_TEX_PATH);
    game.door_lock_tex = get_texture(DOOR_LOCK_TEX_PATH);
    // starting_map = get_texture("gfx/maps/map_1.png");
    // wrong_map = get_texture("gfx/maps/wrong_map.png");
}



Texture2D& get_texture(const std::string& path)
{
    auto it = game.texture_cache.find(path);
    if (it != game.texture_cache.end())
        return it->second;

    Texture2D tex = LoadTexture(path.c_str());
    game.texture_cache[path] = tex;
    return game.texture_cache[path];
}

void unload_all_textures()
{
    for (auto& [path, tex] : game.texture_cache)
    {
        UnloadTexture(tex);
    }
    game.texture_cache.clear();
}







template<typename T>
void write_vector(std::ofstream& file, const std::vector<T>& vec)
{
    size_t size = vec.size();
    file.write((char*)&size, sizeof(size));
    if(size > 0)
        file.write((char*)vec.data(), size * sizeof(T));
}

template<typename T>
void read_vector(std::ifstream& file, std::vector<T>& vec)
{
    size_t size;
    file.read((char*)&size, sizeof(size));

    vec.resize(size);

    if(size > 0)
        file.read((char*)vec.data(), size * sizeof(T));
}
//
Game_save save_current_state(){
    Game_save save;

    save.current_mapSV = game.current_map;
    save.player_posSV = player.pos;
    save.defeated_entitiesSV = player.defeated_entities;
    save.picked_up_itemsSV = player.picked_up_items;
    save.unlocked_doorsSV = player.unlocked_doors;
    save.finished_dialogSV = gui.finished_dialog;
    save.player_dungeon_keysSV = player.dungeon_keys;
    save.player_current_healthSV = player.current_health;
    save.player_max_healthSV = player.max_health;
    for(int i = 0; i < 28; i++){
        save.inventory_slotsSV[i] = inventory_slots[i];
    }
    // std::cout << "saving";
    return save;
    //just save the current save and return the save generated :)
}

void load_map_save(Map_names wanted_map, Vector2 wanted_player_spawn){ //force load a map - cuz its a save, u want it to actually work!
    game.fade_frame_timer = SCREEN_FADE_TIME;
    load_map(wanted_map, wanted_player_spawn);
}

void load_save(Game_save save){
    
    player.defeated_entities = save.defeated_entitiesSV;
    player.picked_up_items = save.picked_up_itemsSV;
    player.unlocked_doors = save.unlocked_doorsSV;
    gui.finished_dialog = save.finished_dialogSV;
    player.dungeon_keys = save.player_dungeon_keysSV;
    player.current_health =  save.player_current_healthSV;
    player.max_health = save.player_max_healthSV;
    for(int i = 0; i < 28; i++){
        inventory_slots[i] = save.inventory_slotsSV[i];
    }
    load_map_save(save.current_mapSV, save.player_posSV);
    // std::cout << "loading";
    
}
void load_index_save(int start_menu_slot_index)
{
    Game_save dat;

    std::string path = "saves/save" + std::to_string(start_menu_slot_index) + ".dat";

    if(!FileExists(path.c_str())){
        
        return;
    }
    
    std::ifstream file(path, std::ios::binary);

    // primitives
    file.read((char*)&dat.current_mapSV, sizeof(dat.current_mapSV));
    file.read((char*)&dat.player_posSV, sizeof(dat.player_posSV));

    // vectors
    read_vector(file, dat.defeated_entitiesSV);
    read_vector(file, dat.picked_up_itemsSV);
    read_vector(file, dat.unlocked_doorsSV);
    read_vector(file, dat.finished_dialogSV);

    // primitives
    file.read((char*)&dat.player_dungeon_keysSV, sizeof(dat.player_dungeon_keysSV));
    file.read((char*)&dat.player_current_healthSV, sizeof(dat.player_current_healthSV));
    file.read((char*)&dat.player_max_healthSV, sizeof(dat.player_max_healthSV));

    // fixed array
    file.read((char*)dat.inventory_slotsSV, sizeof(dat.inventory_slotsSV));

    file.close();

    load_save(dat);
}
void save_index_state(int start_menu_slot_index)
{
    Game_save dat = save_current_state();

    std::string path = "saves/save" + std::to_string(start_menu_slot_index) + ".dat";

    std::ofstream file(path, std::ios::binary);

    // primitives
    file.write((char*)&dat.current_mapSV, sizeof(dat.current_mapSV));
    file.write((char*)&dat.player_posSV, sizeof(dat.player_posSV));

    // vectors
    write_vector(file, dat.defeated_entitiesSV);
    write_vector(file, dat.picked_up_itemsSV);
    write_vector(file, dat.unlocked_doorsSV);
    write_vector(file, dat.finished_dialogSV);

    // more primitives
    file.write((char*)&dat.player_dungeon_keysSV, sizeof(dat.player_dungeon_keysSV));
    file.write((char*)&dat.player_current_healthSV, sizeof(dat.player_current_healthSV));
    file.write((char*)&dat.player_max_healthSV, sizeof(dat.player_max_healthSV));

    // fixed array
    file.write((char*)dat.inventory_slotsSV, sizeof(dat.inventory_slotsSV));

    file.close();


    // screenshot thumbnail
    Image img = LoadImageFromScreen();

    Vector2 screenPos = GetWorldToScreen2D(player.pos, cam);

    Rectangle crop = {
        screenPos.x - 7*scale,
        screenPos.y - 37*scale,
        float(78*scale),
        float(142*scale)
    };

    ImageCrop(&img, crop);
    ImageResizeNN(&img, img.width/scale, img.height/scale);

    ExportImage(img, TextFormat("saves/start_menu_index_icon_%i.png", start_menu_slot_index));

    UnloadImage(img);
}

void save_config_state()
{
    Config_dat cfg_dat{};

    cfg_dat.scale = scale;
    cfg_dat.KEY_CONTROLS_UP = KEY_CONTROLS_UP;
    cfg_dat.KEY_CONTROLS_DOWN = KEY_CONTROLS_DOWN;
    cfg_dat.KEY_CONTROLS_RIGHT = KEY_CONTROLS_RIGHT;
    cfg_dat.KEY_CONTROLS_LEFT = KEY_CONTROLS_LEFT;
    cfg_dat.KEY_ITEM_HOTBAR_1 = KEY_ITEM_HOTBAR_1;
    cfg_dat.KEY_ITEM_HOTBAR_2 = KEY_ITEM_HOTBAR_2;
    cfg_dat.KEY_ITEM_HOTBAR_3 = KEY_ITEM_HOTBAR_3;
    cfg_dat.KEY_OPEN_INVENTORY = KEY_OPEN_INVENTORY;
    cfg_dat.KEY_INTERACT = KEY_INTERACT;
    cfg_dat.KEY_SPEEDUP = KEY_SPEEDUP;
    cfg_dat.KEY_SAVE = KEY_SAVE;
    cfg_dat.KEY_SPRINT = KEY_SPRINT;

    std::ofstream file("saves/config.dat", std::ios::binary);

    if(!file.is_open())
        return;

    file.write((char*)&CONFIG_MAGIC, sizeof(CONFIG_MAGIC));
    file.write((char*)&CONFIG_VERSION, sizeof(CONFIG_VERSION));
    file.write((char*)&cfg_dat, sizeof(cfg_dat));
}
void load_config_state()
{
    std::ifstream file("saves/config.dat", std::ios::binary);

    if(!file.is_open())
        return;

    int magic;
    int version;

    file.read((char*)&magic, sizeof(magic));
    file.read((char*)&version, sizeof(version));

    if(magic != CONFIG_MAGIC)
        return;

    if(version != CONFIG_VERSION)
        return;

    Config_dat cfg_dat{};

    if(!file.read((char*)&cfg_dat, sizeof(cfg_dat)))
        return;

    scale = cfg_dat.scale;

    KEY_CONTROLS_UP = (KeyboardKey)cfg_dat.KEY_CONTROLS_UP;
    KEY_CONTROLS_DOWN = (KeyboardKey)cfg_dat.KEY_CONTROLS_DOWN;
    KEY_CONTROLS_RIGHT = (KeyboardKey)cfg_dat.KEY_CONTROLS_RIGHT;
    KEY_CONTROLS_LEFT = (KeyboardKey)cfg_dat.KEY_CONTROLS_LEFT;
    KEY_ITEM_HOTBAR_1 = (KeyboardKey)cfg_dat.KEY_ITEM_HOTBAR_1;
    KEY_ITEM_HOTBAR_2 = (KeyboardKey)cfg_dat.KEY_ITEM_HOTBAR_2;
    KEY_ITEM_HOTBAR_3 = (KeyboardKey)cfg_dat.KEY_ITEM_HOTBAR_3;
    KEY_OPEN_INVENTORY = (KeyboardKey)cfg_dat.KEY_OPEN_INVENTORY;
    KEY_INTERACT = (KeyboardKey)cfg_dat.KEY_INTERACT;
    KEY_SPEEDUP = (KeyboardKey)cfg_dat.KEY_SPEEDUP;
    KEY_SAVE = (KeyboardKey)cfg_dat.KEY_SAVE;
    KEY_SPRINT = (KeyboardKey)cfg_dat.KEY_SPRINT;

    
}
