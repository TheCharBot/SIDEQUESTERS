#include "game_funcs.hpp"
Game_data game;




void init_map()
{
    
    game.broken_tile_tex = get_texture(BROKEN_TILE_TEX_PATH);
    game.door_lock_tex = get_texture(DOOR_LOCK_TEX_PATH);
    // starting_map = get_texture("gfx/maps/map_1.png");
    // wrong_map = get_texture("gfx/maps/wrong_map.png");
}

void init_keybinds(){
    game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_UP]    = KEY_UP;
    game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_DOWN]  = KEY_DOWN;
    game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_RIGHT] = KEY_RIGHT;
    game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_LEFT]  = KEY_LEFT;
    game.keybinds[Custom_keyboard_keys::KEY_ITEM_HOTBAR_1]  = KEY_A;
    game.keybinds[Custom_keyboard_keys::KEY_ITEM_HOTBAR_2]  = KEY_S;
    game.keybinds[Custom_keyboard_keys::KEY_ITEM_HOTBAR_3]  = KEY_D;
    game.keybinds[Custom_keyboard_keys::KEY_OPEN_INVENTORY] = KEY_TAB;
    game.keybinds[Custom_keyboard_keys::KEY_INTERACT]       = KEY_X;
    game.keybinds[Custom_keyboard_keys::KEY_SPEEDUP]        = KEY_Z;
    game.keybinds[Custom_keyboard_keys::KEY_SAVE]           = KEY_ENTER;
    game.keybinds[Custom_keyboard_keys::KEY_SPRINT]         = KEY_LEFT_SHIFT;
    game.default_keybinds = game.keybinds;
};
// KeyboardKey KEY_CONTROLS_UP    = KEY_UP;
// KeyboardKey KEY_CONTROLS_DOWN  = KEY_DOWN;
// KeyboardKey KEY_CONTROLS_RIGHT = KEY_RIGHT;
// KeyboardKey KEY_CONTROLS_LEFT  = KEY_LEFT;
// KeyboardKey KEY_ITEM_HOTBAR_1  = KEY_A;
// KeyboardKey KEY_ITEM_HOTBAR_2  = KEY_S;
// KeyboardKey KEY_ITEM_HOTBAR_3  = KEY_D;
// KeyboardKey KEY_OPEN_INVENTORY = KEY_TAB;
// KeyboardKey KEY_INTERACT       = KEY_X;
// KeyboardKey KEY_SPEEDUP        = KEY_Z;
// KeyboardKey KEY_SAVE           = KEY_ENTER;
// KeyboardKey KEY_SPRINT         = KEY_LEFT_SHIFT; 
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

const char* GetKeyNameCustom(KeyboardKey key){
    switch(key){
        case KEY_SPACE:         return "SPACE";
        case KEY_ENTER:         return "ENTER";
        case KEY_TAB:           return "TAB";
        case KEY_BACKSPACE:     return "BACKSPACE";
        case KEY_ESCAPE:        return "ESCAPE";
        case KEY_LEFT_SHIFT:    return "L.SHIFT";
        case KEY_RIGHT_SHIFT:   return "R.SHIFT";
        case KEY_LEFT_CONTROL:  return "L.CTRL";
        case KEY_RIGHT_CONTROL: return "R.CTRL";
        case KEY_LEFT_ALT:      return "L.ALT";
        case KEY_RIGHT_ALT:     return "R.ALT";
        case KEY_UP:            return "UP";
        case KEY_DOWN:          return "DOWN";
        case KEY_LEFT:          return "LEFT";
        case KEY_RIGHT:         return "RIGHT";
        case KEY_F1:            return "F1";
        case KEY_F2:            return "F2";
        case KEY_F3:            return "F3";
        case KEY_F4:            return "F4";
        case KEY_F5:            return "F5";
        case KEY_F6:            return "F6";
        case KEY_F7:            return "F7";
        case KEY_F8:            return "F8";
        case KEY_F9:            return "F9";
        case KEY_F10:           return "F10";
        case KEY_F11:           return "F11";
        case KEY_F12:           return "F12";

        // Letters — raylib key codes for letters are just their ASCII values
        default:
            if(key >= KEY_A && key <= KEY_Z){
                static char buf[2];
                buf[0] = 'A' + (key - KEY_A);
                buf[1] = '\0';
                return buf;
            }
            if(key >= KEY_ZERO && key <= KEY_NINE){
                static char buf[2];
                buf[0] = '0' + (key - KEY_ZERO);
                buf[1] = '\0';
                return buf;
            }
            return "???";
    }
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
        load_map(START_MAP, {PLAYER_START_MAP_POS_X, PLAYER_START_MAP_POS_Y});
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
    cfg_dat.KEY_CONTROLS_UP    = game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_UP];
    cfg_dat.KEY_CONTROLS_DOWN  = game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_DOWN]; 
    cfg_dat.KEY_CONTROLS_RIGHT = game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_RIGHT];
    cfg_dat.KEY_CONTROLS_LEFT  = game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_LEFT]; 
    cfg_dat.KEY_ITEM_HOTBAR_1  = game.keybinds[Custom_keyboard_keys::KEY_ITEM_HOTBAR_1]; 
    cfg_dat.KEY_ITEM_HOTBAR_2  = game.keybinds[Custom_keyboard_keys::KEY_ITEM_HOTBAR_2]; 
    cfg_dat.KEY_ITEM_HOTBAR_3  = game.keybinds[Custom_keyboard_keys::KEY_ITEM_HOTBAR_3]; 
    cfg_dat.KEY_OPEN_INVENTORY = game.keybinds[Custom_keyboard_keys::KEY_OPEN_INVENTORY];
    cfg_dat.KEY_INTERACT       = game.keybinds[Custom_keyboard_keys::KEY_INTERACT];      
    cfg_dat.KEY_SPEEDUP        = game.keybinds[Custom_keyboard_keys::KEY_SPEEDUP];       
    cfg_dat.KEY_SAVE           = game.keybinds[Custom_keyboard_keys::KEY_SAVE];          
    cfg_dat.KEY_SPRINT         = game.keybinds[Custom_keyboard_keys::KEY_SPRINT];        

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

    game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_UP]    = (KeyboardKey)cfg_dat.KEY_CONTROLS_UP;
    game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_DOWN]  = (KeyboardKey)cfg_dat.KEY_CONTROLS_DOWN;
    game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_RIGHT] = (KeyboardKey)cfg_dat.KEY_CONTROLS_RIGHT;
    game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_LEFT]  = (KeyboardKey)cfg_dat.KEY_CONTROLS_LEFT;
    game.keybinds[Custom_keyboard_keys::KEY_ITEM_HOTBAR_1]  = (KeyboardKey)cfg_dat.KEY_ITEM_HOTBAR_1;
    game.keybinds[Custom_keyboard_keys::KEY_ITEM_HOTBAR_2]  = (KeyboardKey)cfg_dat.KEY_ITEM_HOTBAR_2;
    game.keybinds[Custom_keyboard_keys::KEY_ITEM_HOTBAR_3]  = (KeyboardKey)cfg_dat.KEY_ITEM_HOTBAR_3;
    game.keybinds[Custom_keyboard_keys::KEY_OPEN_INVENTORY] = (KeyboardKey)cfg_dat.KEY_OPEN_INVENTORY;
    game.keybinds[Custom_keyboard_keys::KEY_INTERACT]       = (KeyboardKey)cfg_dat.KEY_INTERACT;
    game.keybinds[Custom_keyboard_keys::KEY_SPEEDUP]        = (KeyboardKey)cfg_dat.KEY_SPEEDUP;
    game.keybinds[Custom_keyboard_keys::KEY_SAVE]           = (KeyboardKey)cfg_dat.KEY_SAVE;
    game.keybinds[Custom_keyboard_keys::KEY_SPRINT]         = (KeyboardKey)cfg_dat.KEY_SPRINT;

    
}


void draw_locked_doors(){
    for(Locked_rect &l : game.locked_rects){
        DrawRectangle(l.rect.x, l.rect.y, l.rect.width, l.rect.height, GUI_LIGHT_GRAY); //box around thing, using color from aap64
        DrawRectangleLinesEx({l.rect.x, l.rect.y, l.rect.width, l.rect.height}, 1, BLACK); 
        //drawing 4 corners, sorry it mess
        DrawPixel(l.rect.x+1, l.rect.y+1, GUI_DARK_GRAY);
        DrawPixel(l.rect.x+1, l.rect.y+l.rect.height-2, GUI_DARK_GRAY);
        DrawPixel(l.rect.x+l.rect.width-2, l.rect.y+1, GUI_DARK_GRAY);
        DrawPixel(l.rect.x+l.rect.width-2, l.rect.y+l.rect.height-2, GUI_DARK_GRAY);

        //drawing lock texture
        DrawTextureEx(game.door_lock_tex,{l.rect.x+(l.rect.width/2-8), l.rect.y+(l.rect.height/2-8)}, 0, 1, WHITE); //just the offsets - i dont think macros are too nessecary
    }
}

void sort_and_draw_player_and_entities(){
    game.draw_order = {};
    //might not be the best idea to put it here, but this game could run on a potato so far
    for (int i = 0; i < (int)game.entities.size(); i++)
    game.draw_order.push_back({ game.entities[i]->rect.y+game.entities[i]->rect.height, i });

    game.draw_order.push_back({ player.collision_rect.y+player.collision_rect.height, -1 }); // -1 = player

    std::sort(game.draw_order.begin(), game.draw_order.end());

    for (auto &[y, i] : game.draw_order) {
        if (i == -1) draw_player();
        else         game.entities[i]->draw();
    }
}

void draw_broken_floor_tiles(){
    for(Vector2 &v : game.broken_floor_tiles){
        DrawTexturePro(game.broken_tile_tex, BROKEN_TILE_RECT, {v.x, v.y, 16, 16}, {0, 0}, 0, WHITE); //look, i didnt want to make a whole new macro just for 16x16, deal with it
    }
}

void draw_ground_items(){
    for(Ground_item &g : game.ground_items){
        
        DrawTexturePro(gui.items_tex, g.item.img_rect, {g.pos.x, g.pos.y, 16, 16}, {0, 0}, 0, WHITE); // again ^
        
    }
}