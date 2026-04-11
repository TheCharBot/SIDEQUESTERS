#include "gui.hpp"

GUI_data gui;




void unload_start_menu_assets(){
    UnloadTexture(gui.start_menu_tex);
    // bool start_menu_unloaded = true;
}


void init_start_menu(){
    gui.start_menu_tex = get_texture(START_MENU_TEX_PATH);
    gui.start_menu_logo_pos = START_MENU_LOGO_POS;
    gui.start_menu_enimation_pos = START_MENU_EMINATION_POS;
    gui.start_menu_options_pos = START_MENU_OPTIONS_POS;
    gui.start_menu_select_right_pos = Vector2Add(START_MENU_OPTIONS_POS, START_MENU_OPTIONS_START_RIGHT_SELECT_OFFSET);
    gui.start_menu_select_left_pos = Vector2Add(START_MENU_OPTIONS_POS, START_MENU_OPTIONS_START_LEFT_SELECT_OFFSET);
    gui.start_menu_sel_mode = 0;
    gui.start_menu_unloaded = false;
    gui.start_menu_save_selecter_pos = SAVE_SLOT_1_SELECTER_POS;
    game.current_music = LoadMusicStream(ELEVATOR_MUS_PATH);
    

}



void start_menu_save_slots_screen_update(){
    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_SPEEDUP])){
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_PICKUP]);
        gui.start_menu_sel_mode = 0;
        // unload_start_menu_assets();
        game.state = Game_states::START_MENU; 
        // gui.start_menu_unloaded = true;
    }
    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_RIGHT])){
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_SELECT]);
        gui.start_menu_sel_mode += 1;
        gui.start_menu_sel_mode = Clamp(gui.start_menu_sel_mode, 0, 2);
    }
    else if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_LEFT])){
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_SELECT]);
        gui.start_menu_sel_mode -= 1;
        gui.start_menu_sel_mode = Clamp(gui.start_menu_sel_mode, 0, 2);
    }
    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_INTERACT])){
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_PICKUP]);
        switch(gui.start_menu_sel_mode){
            case 0:
                
                // unload_start_menu_assets();
                load_index_save(0);
                game.save_slot = 0;
                game.state = Game_states::GAMEPLAY; 
                // gui.start_menu_unloaded = true;
                break;
            case 1:
                load_index_save(1);
                game.save_slot = 1;
                // unload_start_menu_assets();
                game.state = Game_states::GAMEPLAY;
                break;
            case 2:
                load_index_save(2);
                game.save_slot = 2;
                // unload_start_menu_assets();
                game.state = Game_states::GAMEPLAY;
                break;
            
        }
    } //TODO: merge ^ v (later)
    switch(gui.start_menu_sel_mode){
        case 0:
            gui.start_menu_save_selecter_pos = Vector2Lerp(gui.start_menu_save_selecter_pos, SAVE_SLOT_1_SELECTER_POS, 0.4);
            
            break;
        case 1:
            gui.start_menu_save_selecter_pos = Vector2Lerp(gui.start_menu_save_selecter_pos, SAVE_SLOT_2_SELECTER_POS, 0.4);
            
            break;
        case 2:
            gui.start_menu_save_selecter_pos = Vector2Lerp(gui.start_menu_save_selecter_pos, SAVE_SLOT_3_SELECTER_POS, 0.4);
            
            break;
    }
}

void start_menu_credits_screen_update(){
    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_SPEEDUP])){
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_PICKUP]);
        gui.start_menu_sel_mode = 3;
        // unload_start_menu_assets();
        game.state = Game_states::START_MENU; 
        // gui.start_menu_unloaded = true;
    }
}

void start_menu_update(){
    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_DOWN])){
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_SELECT]);
        gui.start_menu_sel_mode += 1;
        gui.start_menu_sel_mode = Clamp(gui.start_menu_sel_mode, 0, 3);
    }
    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_UP])){
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_SELECT]);
        gui.start_menu_sel_mode -= 1;
        gui.start_menu_sel_mode = Clamp(gui.start_menu_sel_mode, 0, 3);
    }
    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_INTERACT])){
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_PICKUP]);
        switch(gui.start_menu_sel_mode){
            case 0:
                
                // unload_start_menu_assets();
                game.state = Game_states::SAVE_SLOTS; 
                for (int i = 0; i < 3; i++)
                {
                    const char* path = TextFormat("saves/start_menu_index_icon_%i.png", i);

                    if (FileExists(path))
                    {
                        gui.slot_icons[i] = get_texture(path);
                    }
                }
                // gui.start_menu_unloaded = true;
                break;
            case 1:
                
                // unload_start_menu_assets();
                game.state = Game_states::OPTIONS;
                gui.previous_state = START_MENU;
                break;
            case 2:
                
                // unload_start_menu_assets();
                game.state = Game_states::ACHIEVEMENTS;
                gui.previous_state = START_MENU;
                break;
            case 3:
                
                // unload_start_menu_assets();
                game.state = Game_states::CREDITS;
                gui.previous_state = START_MENU;
                break;
        }
    } //TODO: merge ^ v (later)
    switch(gui.start_menu_sel_mode){
        case 0:
            gui.start_menu_select_right_pos = Vector2Lerp(gui.start_menu_select_right_pos, Vector2Add(START_MENU_OPTIONS_POS, START_MENU_OPTIONS_START_RIGHT_SELECT_OFFSET), 0.4);
            gui.start_menu_select_left_pos = Vector2Lerp(gui.start_menu_select_left_pos, Vector2Add(START_MENU_OPTIONS_POS, START_MENU_OPTIONS_START_LEFT_SELECT_OFFSET), 0.4);
            break;
        case 1:
            gui.start_menu_select_right_pos = Vector2Lerp(gui.start_menu_select_right_pos, Vector2Add(START_MENU_OPTIONS_POS, START_MENU_OPTIONS_OPTIONS_RIGHT_SELECT_OFFSET), 0.4);
            gui.start_menu_select_left_pos = Vector2Lerp(gui.start_menu_select_left_pos, Vector2Add(START_MENU_OPTIONS_POS, START_MENU_OPTIONS_OPTIONS_LEFT_SELECT_OFFSET), 0.4);
            break;
        case 2:
            gui.start_menu_select_right_pos = Vector2Lerp(gui.start_menu_select_right_pos, Vector2Add(START_MENU_OPTIONS_POS, START_MENU_OPTIONS_ACHIEVEMENTS_RIGHT_SELECT_OFFSET), 0.4);
            gui.start_menu_select_left_pos = Vector2Lerp(gui.start_menu_select_left_pos, Vector2Add(START_MENU_OPTIONS_POS, START_MENU_OPTIONS_ACHIEVEMENTS_LEFT_SELECT_OFFSET), 0.4);
            break;
        case 3:
            gui.start_menu_select_right_pos = Vector2Lerp(gui.start_menu_select_right_pos, Vector2Add(START_MENU_OPTIONS_POS, START_MENU_OPTIONS_CREDITS_RIGHT_SELECT_OFFSET), 0.4);
            gui.start_menu_select_left_pos = Vector2Lerp(gui.start_menu_select_left_pos, Vector2Add(START_MENU_OPTIONS_POS, START_MENU_OPTIONS_CREDITS_LEFT_SELECT_OFFSET), 0.4);
            break;
    }
}

void start_menu_draw(){ //sorry ugly code. deal with it
    switch(game.state){
        case START_MENU:
            DrawTexturePro(gui.start_menu_tex, start_menu_emination, {gui.start_menu_enimation_pos.x*scale, gui.start_menu_enimation_pos.y*scale, start_menu_emination.width*scale, start_menu_emination.height*scale}, {0, 0}, 0, WHITE);

            DrawTexturePro(gui.start_menu_tex, start_menu_text_rect, {gui.start_menu_logo_pos.x*scale, gui.start_menu_logo_pos.y*scale, start_menu_text_rect.width*scale, start_menu_text_rect.height*scale}, {0, 0}, 0, WHITE);

            DrawTexturePro(gui.start_menu_tex, start_menu_options_rect, {gui.start_menu_options_pos.x*scale, gui.start_menu_options_pos.y*scale, start_menu_options_rect.width*scale, start_menu_options_rect.height*scale}, {0, 0}, 0, WHITE);

            DrawTexturePro(gui.start_menu_tex, start_menu_select_right, {gui.start_menu_select_right_pos.x*scale, gui.start_menu_select_right_pos.y*scale, start_menu_select_right.width*scale, start_menu_select_right.height*scale}, {0, 0}, 0, WHITE);
            DrawTexturePro(gui.start_menu_tex, start_menu_select_left, {gui.start_menu_select_left_pos.x*scale, gui.start_menu_select_left_pos.y*scale, start_menu_select_left.width*scale, start_menu_select_left.height*scale}, {0, 0}, 0, WHITE);
            break;
        case SAVE_SLOTS:
            DrawTexturePro(gui.start_menu_tex, start_menu_saves_select_screen, {0, 0, start_menu_saves_select_screen.width*scale, start_menu_saves_select_screen.height*scale}, {0, 0}, 0, WHITE);
            DrawTexturePro(gui.start_menu_tex, start_menu_saves_select_screen_selecter, {gui.start_menu_save_selecter_pos.x*scale, gui.start_menu_save_selecter_pos.y*scale, start_menu_saves_select_screen_selecter.width*scale, start_menu_saves_select_screen_selecter.height*scale}, {0, 0}, 0, WHITE);
            for (int i = 0; i < 3; i++)
            {
                if (gui.slot_icons[i].id != 0) // texture exists
                {
                    DrawTextureEx(gui.slot_icons[i], Vector2Scale({float(25+(i*96)), 19}, scale), 0, scale, WHITE);//TODO: MACROS
                    // std::cout <<"working?";
                }
            }
            break;
        
        case CREDITS:
            DrawTexturePro(gui.start_menu_tex, start_menu_credits_screen, {0, 0, start_menu_credits_screen.width*scale, start_menu_credits_screen.height*scale}, {0, 0}, 0, WHITE);
            break;
        default:
            break;
    }
}



void options_screen_update(){

    gui.options_selector_move_mode = gui.selector_move_mode::IDLE;

    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_SPEEDUP])){
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_PICKUP]);
        gui.pause_menu_sel_mode = 1;
        gui.start_menu_sel_mode = 1;
        game.state = gui.previous_state; 
    }
    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_DOWN])){
        gui.options_menu_select_index++;
        gui.options_selector_move_mode = gui.selector_move_mode::DOWN;
    }
    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_UP])){
        gui.options_menu_select_index--;
        gui.options_selector_move_mode = gui.selector_move_mode::UP;
    }
    gui.options_menu_select_index = Clamp(gui.options_menu_select_index, 0, 13);
    
    gui.options_boxes_selector_pos = Vector2Add(Vector2SubtractValue(options_boxes_pos[gui.options_menu_select_index], 5), gui.options_boxes_pos);
    if(gui.options_selector_move_mode == gui.selector_move_mode::DOWN){
        switch(gui.options_menu_select_index){
            case 4:
                gui.options_boxes_wanted_pos = {5, -112};
                break;
            case 8:
                gui.options_boxes_wanted_pos = {5, -240};
                break;
            case 12:
                gui.options_boxes_wanted_pos = {5, -368};
                break;

            default:
                break;
        }
    }
    else if(gui.options_selector_move_mode == gui.selector_move_mode::UP){
        switch(gui.options_menu_select_index){
            case 4:
                gui.options_boxes_wanted_pos = {5, 32};
                break;
            case 8:
                gui.options_boxes_wanted_pos = {5, -112};
                break;
            case 12:
                gui.options_boxes_wanted_pos = {5, -240};
                break;
            default:
                break;
        }
    }
    gui.options_boxes_pos = Vector2Lerp(gui.options_boxes_pos, gui.options_boxes_wanted_pos, 0.4);
}

void achievements_screen_update(){
    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_SPEEDUP])){
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_PICKUP]);
        gui.pause_menu_sel_mode = 2;
        gui.start_menu_sel_mode = 2;
        game.state = gui.previous_state; 
    }
}

void options_screen_draw(){
    DrawTexturePro(gui.start_menu_tex, start_menu_options_screen, {0, 0, start_menu_options_screen.width*scale, start_menu_options_screen.height*scale}, {0, 0}, 0, WHITE);
    DrawTextureEx(gui.options_boxes_tex, Vector2Scale(gui.options_boxes_pos, scale), 0, scale, WHITE);
    DrawTextureEx(gui.options_boxes_selector_tex, Vector2Scale(gui.options_boxes_selector_pos, scale), 0, scale, WHITE);
}

void achievements_screen_draw(){
    DrawTexturePro(gui.start_menu_tex, start_menu_achievements_screen, {0, 0, start_menu_achievements_screen.width*scale, start_menu_achievements_screen.height*scale}, {0, 0}, 0, WHITE);
}


void pause_menu_update()
{   
    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_DOWN])){
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_SELECT]);
        gui.pause_menu_sel_mode += 1;
        gui.pause_menu_sel_mode = Clamp(gui.pause_menu_sel_mode, 0, 2);
    }
    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_UP])){
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_SELECT]);
        gui.pause_menu_sel_mode -= 1;
        gui.pause_menu_sel_mode = Clamp(gui.pause_menu_sel_mode, 0, 2);
    }
    if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_INTERACT])){
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_PICKUP]);
        switch(gui.pause_menu_sel_mode){
            case 0:
                
                // unload_start_menu_assets();
                
                
                
                
                save_index_state(game.save_slot);
                game.state = Game_states::START_MENU; 
                reset_loaded();
                game.current_music = LoadMusicStream(ELEVATOR_MUS_PATH);
                gui.previous_state = PAUSE_MENU;
                
                // gui.start_menu_unloaded = true;
                break;
            case 1:
                
                // unload_start_menu_assets();
                game.state = Game_states::OPTIONS;
                gui.previous_state = PAUSE_MENU;
                break;
            case 2:
                
                // unload_start_menu_assets();
                game.state = Game_states::ACHIEVEMENTS;
                gui.previous_state = PAUSE_MENU;
                break;
        }
    }
    switch(gui.pause_menu_sel_mode){
        case 0:
            gui.pause_menu_select_right_pos = Vector2Lerp(gui.pause_menu_select_right_pos, Vector2Add(PAUSE_MENU_OPTIONS_POS, PAUSE_MENU_OPTIONS_SAVEQUIT_RIGHT_SELECT_OFFSET), 0.4);
            gui.pause_menu_select_left_pos = Vector2Lerp(gui.pause_menu_select_left_pos, Vector2Add(PAUSE_MENU_OPTIONS_POS, PAUSE_MENU_OPTIONS_SAVEQUIT_LEFT_SELECT_OFFSET), 0.4);
            break;
        case 1:
            gui.pause_menu_select_right_pos = Vector2Lerp(gui.pause_menu_select_right_pos, Vector2Add(PAUSE_MENU_OPTIONS_POS, PAUSE_MENU_OPTIONS_OPTIONS_RIGHT_SELECT_OFFSET), 0.4);
            gui.pause_menu_select_left_pos = Vector2Lerp(gui.pause_menu_select_left_pos, Vector2Add(PAUSE_MENU_OPTIONS_POS, PAUSE_MENU_OPTIONS_OPTIONS_LEFT_SELECT_OFFSET), 0.4);
            break;
        case 2:
            gui.pause_menu_select_right_pos = Vector2Lerp(gui.pause_menu_select_right_pos, Vector2Add(PAUSE_MENU_OPTIONS_POS, PAUSE_MENU_OPTIONS_ACHIEVEMENTS_RIGHT_SELECT_OFFSET), 0.4);
            gui.pause_menu_select_left_pos = Vector2Lerp(gui.pause_menu_select_left_pos, Vector2Add(PAUSE_MENU_OPTIONS_POS, PAUSE_MENU_OPTIONS_ACHIEVEMENTS_LEFT_SELECT_OFFSET), 0.4);
            break;
    }
}

void pause_menu_draw()
{
    
    DrawTexturePro(
        gui.pause_menu_tex, 
        pause_menu_background, 
        {gui.pause_menu_background_pos.x*scale, gui.pause_menu_background_pos.y*scale, pause_menu_background.width*scale, pause_menu_background.height*scale}, 
        {0, 0}, 
        0, 
        WHITE);
    DrawTexturePro(
        gui.pause_menu_tex, 
        pause_menu_options, 
        {gui.pause_menu_options_pos.x*scale, gui.pause_menu_options_pos.y*scale, pause_menu_options.width*scale, pause_menu_options.height*scale}, 
        {0, 0}, 
        0, 
        WHITE);
    DrawTexturePro(
        gui.pause_menu_tex, 
        pause_menu_left_selector, 
        {gui.pause_menu_select_left_pos.x*scale, gui.pause_menu_select_left_pos.y*scale, pause_menu_left_selector.width*scale, pause_menu_left_selector.height*scale}, 
        {0, 0}, 
        0, 
        WHITE);
    DrawTexturePro(
        gui.pause_menu_tex, 
        pause_menu_right_selector, 
        {gui.pause_menu_select_right_pos.x*scale, gui.pause_menu_select_right_pos.y*scale, pause_menu_right_selector.width*scale, pause_menu_right_selector.height*scale}, 
        {0, 0}, 
        0,
        WHITE);
        // case OPTIONS:
        //     
        //     break;
        // case ACHIEVEMENTS:
        //     
        //     break;
        
    
}



void inv_cursor_init()
{
    gui.inv_cursor.held_item.reset();
    gui.inv_cursor.inv_slot_index = 0;
    gui.inv_cursor.max_anim_frames = 2;
    gui.inv_cursor.current_anim_frame = 0;
    gui.inv_cursor.anim_frame_5 = 0;
}

void inv_cursor_update()
{
    gui.inv_cursor.anim_frame_5++;
    if (gui.inv_cursor.anim_frame_5 >= ANIMATION_INTERVAL + 10)
    {
        gui.inv_cursor.current_anim_frame++;
        if (gui.inv_cursor.current_anim_frame >= gui.inv_cursor.max_anim_frames)
        {
            gui.inv_cursor.current_anim_frame = 0;
        }
        gui.inv_cursor.anim_frame_5 = 0;
    }
    if (IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_UP]))
    {
        gui.inv_cursor.inv_slot_index -= 7;
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_SELECT]);
    }
    if (IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_DOWN]))
    {
        gui.inv_cursor.inv_slot_index += 7;
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_SELECT]);
    }
    if (IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_RIGHT]))
    {
        gui.inv_cursor.inv_slot_index += 1;
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_SELECT]);
    }
    if (IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_CONTROLS_LEFT]))
    {
        gui.inv_cursor.inv_slot_index -= 1;
        PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_SELECT]);
    }
    if (gui.inv_cursor.inv_slot_index > 27)
    {
        gui.inv_cursor.inv_slot_index = 27;
    }
    if (gui.inv_cursor.inv_slot_index < 0)
    {
        gui.inv_cursor.inv_slot_index = 0;
    }
    // picking up an item
    if (IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_INTERACT]))
    {
        // works!!!!!!! was not expecting that!!!!!
        if(inventory_slots[gui.inv_cursor.inv_slot_index].filled_with){
            PlaySound(game.sfx_manager[SFX_ids::INV_CURSOR_PICKUP]);
        }

        auto &slot = inventory_slots[gui.inv_cursor.inv_slot_index];

        std::swap(gui.inv_cursor.held_item, slot.filled_with);
    }
}



void health_bar_draw(){
    //use a for loop and multiply health by ten then draw for i in that
    //okay, that worked too well, but remember: for some odd and unknown reason c++ likes < better than >
    
    //i sorry, but i had too. i hate it too
    //but, it works, so im happy
    //* KEEP THIS - IT WORKS
    //oh gee willikers these are some AWFUL draw calls, but whatever >:)
    DrawTexturePro(gui.gui_bar_segments_tex, health_bar_left_end, {float(HEALTHBAR_OFFSET_X*scale), float(HEALTHBAR_OFFSET_Y*scale), health_bar_left_end.width*scale, health_bar_left_end.height*scale}, {0, 0}, 0, WHITE);
    DrawTexturePro(gui.gui_bar_segments_tex, health_bar_right_end, {float(((player.max_health*10+2)+HEALTHBAR_OFFSET_X)*scale), float(HEALTHBAR_OFFSET_Y*scale), health_bar_right_end.width*scale, health_bar_right_end.height*scale}, {0, 0}, 0, WHITE);
    for(int i = 0; i < player.max_health*10; i++){
        //put stuff here to draw the empty healthbar
        DrawTexturePro(gui.gui_bar_segments_tex, health_bar_middle_dead, {((i*health_bar_middle_dead.width+2)+HEALTHBAR_OFFSET_X)*scale, float(HEALTHBAR_OFFSET_Y*scale), health_bar_middle_dead.width*scale, health_bar_middle_dead.height*scale}, {0, 0}, 0, WHITE); 
    }
    for(int i = 0; i < player.current_health*10; i++){
        //put stuff here to draw the health in the healthbar
        DrawTexturePro(gui.gui_bar_segments_tex, health_bar_middle, {((i*health_bar_middle.width+2)+HEALTHBAR_OFFSET_X)*scale, float(HEALTHBAR_OFFSET_Y*scale), health_bar_middle.width*scale, health_bar_middle.height*scale}, {0, 0}, 0, WHITE);
    }
}

void stamina_bar_draw(){
    if(player.current_stamina < player.max_stamina){

        
        for(int i = 0; i < player.max_stamina; i++){
            //put stuff here to draw the empty stamina bar
            DrawTexturePro(gui.gui_bar_segments_tex, stamina_bar_dead, {float((i*stamina_bar_dead.width+2)+STAMINA_BAR_OFFSET_X)*scale, float(STAMINA_BAR_OFFSET_Y*scale), float(stamina_bar_segment.width*scale), float(stamina_bar_segment.height*scale)}, {0, 0}, 0, WHITE); 
        }
        for(int i = 0; i < player.current_stamina; i++){
            //put stuff here to draw the health in the stamina bar
            DrawTexturePro(gui.gui_bar_segments_tex, stamina_bar_segment, {float((i*stamina_bar_segment.width+2)+STAMINA_BAR_OFFSET_X)*scale, float(STAMINA_BAR_OFFSET_Y*scale), float(stamina_bar_segment.width*scale), float(stamina_bar_segment.height*scale)}, {0, 0}, 0, WHITE);
        }
    }
};

void hotbar_draw(){
    DrawTextureEx(gui.hotbar_tex, Vector2Scale(gui.hotbar_pos, scale), 0, scale, WHITE);
    if(inventory_slots[23].filled_with){
        DrawTexturePro(gui.items_tex, inventory_slots[23].filled_with->img_rect, {gui.hotbar_pos.x*scale+HOTBAR_SLOT_1_OFFSET_X*scale, gui.hotbar_pos.y*scale, float(ITEM_SPRITE_WIDTH*scale), float(ITEM_SPRITE_HEIGHT*scale)}, {0, 0}, 0, WHITE);

        if(inventory_slots[23].filled_with->type == CONSUMABLE){
            inventory_slots[23].amount_in_slot = inventory_slots[23].filled_with->consumable.amount;
            DrawText(std::to_string(inventory_slots[23].filled_with->consumable.amount).c_str(), (gui.hotbar_pos.x+HOTBAR_SLOT_1_OFFSET_X+14)*scale, (gui.hotbar_pos.y+14)*scale, 5*scale, WHITE);
        }
    }
    if(inventory_slots[24].filled_with){
        DrawTexturePro(gui.items_tex, inventory_slots[24].filled_with->img_rect, {gui.hotbar_pos.x*scale+HOTBAR_SLOT_2_OFFSET_X*scale, gui.hotbar_pos.y*scale, float(ITEM_SPRITE_WIDTH*scale), float(ITEM_SPRITE_HEIGHT*scale)}, {0, 0}, 0, WHITE);

        if(inventory_slots[24].filled_with->type == CONSUMABLE){
            inventory_slots[24].amount_in_slot = inventory_slots[24].filled_with->consumable.amount;
            DrawText(std::to_string(inventory_slots[24].filled_with->consumable.amount).c_str(), (gui.hotbar_pos.x+HOTBAR_SLOT_2_OFFSET_X+14)*scale, (gui.hotbar_pos.y+14)*scale, 5*scale, WHITE);
        }
    }
    if(inventory_slots[25].filled_with){
        DrawTexturePro(gui.items_tex, inventory_slots[25].filled_with->img_rect, {gui.hotbar_pos.x*scale+HOTBAR_SLOT_3_OFFSET_X*scale, gui.hotbar_pos.y*scale, float(ITEM_SPRITE_WIDTH*scale), float(ITEM_SPRITE_HEIGHT*scale)}, {0, 0}, 0, WHITE);

        if(inventory_slots[25].filled_with->type == CONSUMABLE){
            inventory_slots[25].amount_in_slot = inventory_slots[25].filled_with->consumable.amount;
            DrawText(std::to_string(inventory_slots[25].filled_with->consumable.amount).c_str(), (gui.hotbar_pos.x+HOTBAR_SLOT_3_OFFSET_X+14)*scale, (gui.hotbar_pos.y+14)*scale, 5*scale, WHITE);
        }
    }
    // DrawText(std::to_string(player.dungeon_keys).c_str(), (hotbar_pos.x+104)*scale, (hotbar_pos.y-1)*scale, 17, (Color){51, 57, 65, 255});

    //layers (!)
    DrawTextEx(gui.global_font, std::to_string(player.dungeon_keys).c_str(), Vector2Scale({gui.hotbar_pos.x+HOTBAR_KEY_TEXT_OFFSET_X+1, gui.hotbar_pos.y-HOTBAR_KEY_TEXT_OFFSET_Y+1}, scale), DEFAULT_FONT_SIZE*scale, scale, BLACK);
    DrawTextEx(gui.global_font, std::to_string(player.dungeon_keys).c_str(), Vector2Scale({gui.hotbar_pos.x+HOTBAR_KEY_TEXT_OFFSET_X, gui.hotbar_pos.y-HOTBAR_KEY_TEXT_OFFSET_Y}, scale), DEFAULT_FONT_SIZE*scale, scale, GUI_DARK_GRAY);
    
}



void set_textbox_indice_text(int index, Dialog_chunk dialog){
    //it works. fine whatever
    if (dialog.text.length() > MAX_TEXTBOX_CHARACTERS) {
        dialog.text.resize(MAX_TEXTBOX_CHARACTERS);
    }

    int offset = 0;

    if ((int)dialog.text.length() > MAX_ONE_LINE_CHARACTERS + offset) {
        for (int i = 1; i <= MAX_ONE_LINE_CHARACTERS; i++) {
            if (dialog.text[MAX_ONE_LINE_CHARACTERS + offset - i] == ' ') {
                int pos = MAX_ONE_LINE_CHARACTERS + offset - i;
                dialog.text.erase(pos, 1);
                dialog.text.insert(pos, "\n");
                offset++;
                break;
            }
        }
    }

    if ((int)dialog.text.length() > MAX_TWO_LINE_CHARACTERS + offset) {
        for (int i = 1; i <= MAX_ONE_LINE_CHARACTERS; i++) {
            if (dialog.text[MAX_TWO_LINE_CHARACTERS + offset - i] == ' ') {
                int pos = MAX_TWO_LINE_CHARACTERS + offset - i;
                dialog.text.erase(pos, 1);
                dialog.text.insert(pos, "\n");
                offset++;
                break;
            }
        }
    }

    if ((int)dialog.text.length() > MAX_THREE_LINE_CHARACTERS + offset) {
        for (int i = 1; i <= MAX_ONE_LINE_CHARACTERS; i++) {
            if (dialog.text[MAX_THREE_LINE_CHARACTERS + offset - i] == ' ') {
                int pos = MAX_THREE_LINE_CHARACTERS + offset - i;
                dialog.text.erase(pos, 1);
                dialog.text.insert(pos, "\n");
                offset++;
                break;
            }
        }
    }
    
    gui.global_textbox.current_dialog[index] = dialog;
}

void setup_textbox(int max_indecies, Entity_names speaker){ //try to have more than just one text box. please <- WRONG!!!! DON'T TRUST HIM!!!!!
    gui.global_textbox.dialog_max_indecies = max_indecies-1;
    gui.global_textbox.is_textbox_open = true;
    gui.global_textbox.dialog_index_state = 0;
    gui.global_textbox.current_dialog_character = 0;
    gui.global_textbox.current_speaker = speaker;
}

void textbox_update_draw(){
    if(gui.global_textbox.is_textbox_open){
    
        player.move_mode = 0;
        
        DrawTextureEx(gui.textbox_tex, Vector2Scale(gui.textbox_pos, scale), 0, scale, WHITE); //drawing the textbox

        

        

        if(IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_INTERACT]) && gui.global_textbox.current_dialog_character >= int(gui.global_textbox.current_dialog[gui.global_textbox.dialog_index_state].text.length())){ //doin the checker to make sure it wants to stay at that specific dialog thing
            gui.global_textbox.dialog_index_state++;
            gui.global_textbox.current_dialog_character = 0;
            if(gui.global_textbox.dialog_index_state > gui.global_textbox.dialog_max_indecies){
                gui.global_textbox.dialog_index_state = 0;
                gui.global_textbox.is_textbox_open = false;
                player.move_mode = 1;
                gui.global_textbox.current_speaker = Entity_names::DEFAULT;
            }
        }
        if(IsKeyDown(game.keybinds[Custom_keyboard_keys::KEY_SPEEDUP])){
            gui.global_textbox.current_dialog_character+=5; //advancing the current characters to be drawn fastly
        }
        else{
            gui.global_textbox.current_dialog_character++; //advancing the current characters to be drawn
        }
        //if i have messages short enough to cause a real problem with this, the order can be changed:

        if(gui.global_textbox.current_dialog_character > int(gui.global_textbox.current_dialog[gui.global_textbox.dialog_index_state].text.length())){ //clamping the current characters (should probably use the Clamp() function)
            gui.global_textbox.current_dialog_character = gui.global_textbox.current_dialog[gui.global_textbox.dialog_index_state].text.length();
        }
        Dialog_chunk temp_drawing_dialog = gui.global_textbox.current_dialog[gui.global_textbox.dialog_index_state]; //setting the temporary dialog
        temp_drawing_dialog.text.resize(gui.global_textbox.current_dialog_character); //cutting the temp dialog
        DrawTextEx(gui.global_font, temp_drawing_dialog.text.c_str(), Vector2Scale({gui.textbox_pos.x+9, gui.textbox_pos.y+4}, scale), DIALOG_FONT_SIZE*scale, 1, BLACK);
        DrawTextEx(gui.global_font, temp_drawing_dialog.text.c_str(), Vector2Scale({gui.textbox_pos.x+8, gui.textbox_pos.y+3}, scale), DIALOG_FONT_SIZE*scale, 1, WHITE); //drawing the temp dialog //TODO: MACROS
    }
}

bool is_text_finished(Dialog_names text_name){
    return std::find(gui.finished_dialog.begin(),
                     gui.finished_dialog.end(),
                     text_name) != gui.finished_dialog.end();
}

void add_finished_text(Dialog_names text_name){
    if(!is_text_finished(text_name)){
        gui.finished_dialog.push_back(text_name);
    }
}



void init_gui()
{
    inv_cursor_init();
    gui.pause_menu_tex = get_texture(PAUSE_MENU_TEX_PATH);
    gui.inventory_tex = get_texture(INVENTORY_PATH);
    gui.items_tex = get_texture(ITEM_SHEET_PATH);
    gui.inventory_cursor_tex = get_texture(INV_CURSOR_PATH);
    gui.gui_bar_segments_tex = get_texture(GUI_BAR_SEGMENTS_PATH);
    gui.hotbar_tex = get_texture(HOTBAR_TEX_PATH);
    gui.options_boxes_tex = get_texture(OPTIONS_BOXES_TEX_PATH);
    gui.options_boxes_selector_tex = get_texture(OPTIONS_BOXES_SELECTOR_TEX_PATH);
    
    gui.textbox_tex = get_texture(TEXTBOX_TEX_PATH);
    add_item_to_inventory(game.item_ids[Item_names::RED_BERRIES]);
    add_item_to_inventory(game.item_ids[Item_names::STICK]);

    gui.global_font = LoadFont(GLOB_FONT_PATH);

    gui.textbox_pos = TEXTBOX_POS;
    gui.hotbar_pos = HOTBAR_POS;

    gui.pause_menu_background_pos = PAUSE_MENU_POS;
    gui.pause_menu_options_pos = PAUSE_MENU_OPTIONS_POS;
    
    gui.pause_menu_select_right_pos = Vector2Add(PAUSE_MENU_OPTIONS_POS, PAUSE_MENU_OPTIONS_SAVEQUIT_RIGHT_SELECT_OFFSET);
    gui.pause_menu_select_left_pos = Vector2Add(PAUSE_MENU_OPTIONS_POS, PAUSE_MENU_OPTIONS_SAVEQUIT_LEFT_SELECT_OFFSET);

    gui.options_boxes_pos = {5, 32}; //TODO: MACROS
    gui.options_boxes_wanted_pos = {5, 32};

    gui.options_boxes_selector_pos = Vector2SubtractValue(gui.options_boxes_pos, 2);
    gui.options_menu_select_index = 0;

    gui.options_selector_move_mode = gui.selector_move_mode::IDLE;
}

void update_gui()
{
    // maybe a performance problem but whatever
    // health_bar_draw(); //genuinely WHY was this here
    if (gui.is_inv_open)
    {
        inv_cursor_update();
    }

    if (IsKeyPressed(game.keybinds[Custom_keyboard_keys::KEY_OPEN_INVENTORY]) && !gui.global_textbox.is_textbox_open)
    {
        gui.is_inv_open = !gui.is_inv_open;
        // if (gui.is_inv_open)
        // {
        //     player.move_mode = 0;
        //     player.current_animation_frame = 0;
        //     for(auto &e : game.entities){
        //         e->move_mode = 0;
        //     }
        // }
        // else
        // {

        //     player.move_mode = 1;
        //     for(auto &e : game.entities){
        //         e->move_mode = 1;
        //     }
        // }
    }
}

void draw_inventory(){
    // drawing inventory
    DrawTextureEx(gui.inventory_tex, {0, 0}, 0, scale, WHITE);
    // drawing cursor

    DrawTexturePro(
        gui.inventory_cursor_tex, 
        inv_cursor_anim[gui.inv_cursor.current_anim_frame], 
        {(inventory_slots[gui.inv_cursor.inv_slot_index].pos.x - 3)*scale, 
            (inventory_slots[gui.inv_cursor.inv_slot_index].pos.y - 1)*scale, 
            inv_cursor_anim[gui.inv_cursor.current_anim_frame].width*scale, 
            inv_cursor_anim[gui.inv_cursor.current_anim_frame].height*scale}, 
        {0, 0}, 
        0, 
        WHITE);
    // drawing held item if there is a held item
    if (gui.inv_cursor.held_item)
    {
        DrawTexturePro(gui.items_tex, gui.inv_cursor.held_item->img_rect, {inventory_slots[gui.inv_cursor.inv_slot_index].pos.x*scale-(1*scale), inventory_slots[gui.inv_cursor.inv_slot_index].pos.y*scale-(1*scale), float(ITEM_SPRITE_WIDTH*scale), float(ITEM_SPRITE_HEIGHT*scale)}, {0, 0}, 0, WHITE);
    }
    // drawing items
    for (Inventory_slot &s : inventory_slots)
    {
        if (!s.filled_with)
            continue; // IMPORTANT
        if(s.filled_with->type == CONSUMABLE){
            s.amount_in_slot = s.filled_with->consumable.amount;
            DrawText(std::to_string(s.filled_with->consumable.amount).c_str(), (s.pos.x+14)*scale, (s.pos.y+14)*scale, 5*scale, WHITE);
        }
        DrawTexturePro(
            gui.items_tex,
            s.filled_with->img_rect,
            {s.pos.x*scale, s.pos.y*scale,
                float(ITEM_SPRITE_WIDTH*scale),
                float(ITEM_SPRITE_HEIGHT*scale)},
            {0, 0}, 0, WHITE);
    }
}

void draw_gui()
{
    // if(IsKeyPressed(KEY_H)){ 
    //     set_textbox_indice_text(0, {"ah, hello there traveler, i havent seen someone of your competence anywhere. would you mind doing a small favor for me?", NONE});
        
    //     setup_textbox(1);
    // } //uncomment for testing!
    hotbar_draw();
    health_bar_draw();
    stamina_bar_draw();
    textbox_update_draw();
    if (gui.is_inv_open)
    {
        draw_inventory();
    }
}
