#include "gui.hpp"

Texture2D inventory_tex;
Texture2D inventory_cursor_tex;
Texture2D items_tex;
Texture2D health_bar_tex;
Texture2D hotbar_tex;
Texture2D textbox_tex;
Vector2 hotbar_pos = HOTBAR_POS;
Vector2 textbox_pos = TEXTBOX_POS;
std::vector<Item> player_inventory = {};
Inventory_cursor inv_cursor;
Item temp_item;
Dialog_chunk current_dialog[MAX_DIALOG_INDICIES];

Font global_font;

int dialog_index_state = 0;

bool is_inv_open;





void inv_cursor_init()
{
    inv_cursor.held_item.reset();
    inv_cursor.inv_slot_index = 0;
    inv_cursor.max_anim_frames = 2;
    inv_cursor.current_anim_frame = 0;
    inv_cursor.anim_frame_5 = 0;
}

void inv_cursor_update()
{
    inv_cursor.anim_frame_5++;
    if (inv_cursor.anim_frame_5 >= ANIMATION_INTERVAL + 10)
    {
        inv_cursor.current_anim_frame++;
        if (inv_cursor.current_anim_frame >= inv_cursor.max_anim_frames)
        {
            inv_cursor.current_anim_frame = 0;
        }
        inv_cursor.anim_frame_5 = 0;
    }
    if (IsKeyPressed(KEY_CONTROLS_UP))
    {
        inv_cursor.inv_slot_index -= 7;
    }
    if (IsKeyPressed(KEY_CONTROLS_DOWN))
    {
        inv_cursor.inv_slot_index += 7;
    }
    if (IsKeyPressed(KEY_CONTROLS_RIGHT))
    {
        inv_cursor.inv_slot_index += 1;
    }
    if (IsKeyPressed(KEY_CONTROLS_LEFT))
    {
        inv_cursor.inv_slot_index -= 1;
    }
    if (inv_cursor.inv_slot_index > 27)
    {
        inv_cursor.inv_slot_index = 27;
    }
    if (inv_cursor.inv_slot_index < 0)
    {
        inv_cursor.inv_slot_index = 0;
    }
    // picking up an item
    if (IsKeyPressed(KEY_INTERACT))
    {
        // works!!!!!!! was not expecting that!!!!!

        auto &slot = inventory_slots[inv_cursor.inv_slot_index];

        std::swap(inv_cursor.held_item, slot.filled_with);
    }
}



void health_bar_draw(){
    //use a for loop and multiply health by ten then draw for i in that
    //okay, that worked too well, but remember: for some odd and unknown reason c++ likes < better than >
    
    //i sorry, but i had too. i hate it too
    //but, it works, so im happy
    //* KEEP THIS - IT WORKS
    //oh gee willikers these are some AWFUL draw calls, but whatever >:)
    DrawTexturePro(health_bar_tex, health_bar_left_end, {float(HEALTHBAR_OFFSET_X*scale), float(HEALTHBAR_OFFSET_Y*scale), health_bar_left_end.width*scale, health_bar_left_end.height*scale}, {0, 0}, 0, WHITE);
    DrawTexturePro(health_bar_tex, health_bar_right_end, {float(((player.max_health*10+2)+HEALTHBAR_OFFSET_X)*scale), float(HEALTHBAR_OFFSET_Y*scale), health_bar_right_end.width*scale, health_bar_right_end.height*scale}, {0, 0}, 0, WHITE);
    for(int i = 0; i < player.max_health*10; i++){
        //put stuff here to draw the empty healthbar
        DrawTexturePro(health_bar_tex, health_bar_middle_dead, {((i*health_bar_middle_dead.width+2)+HEALTHBAR_OFFSET_X)*scale, float(HEALTHBAR_OFFSET_Y*scale), health_bar_middle_dead.width*scale, health_bar_middle_dead.height*scale}, {0, 0}, 0, WHITE);
    }
    for(int i = 0; i < player.current_health*10; i++){
        //put stuff here to draw the health in the healthbar
        DrawTexturePro(health_bar_tex, health_bar_middle, {((i*health_bar_middle.width+2)+HEALTHBAR_OFFSET_X)*scale, float(HEALTHBAR_OFFSET_Y*scale), health_bar_middle.width*scale, health_bar_middle.height*scale}, {0, 0}, 0, WHITE);
    }
}



void hotbar_draw(){
    DrawTextureEx(hotbar_tex, Vector2Scale(hotbar_pos, scale), 0, scale, WHITE);
    if(inventory_slots[23].filled_with){
        DrawTexturePro(
                items_tex,
                inventory_slots[23].filled_with->img_rect,
                {hotbar_pos.x*scale+HOTBAR_SLOT_1_OFFSET_X*scale, hotbar_pos.y*scale,
                 float(ITEM_SPRITE_WIDTH*scale),
                 float(ITEM_SPRITE_HEIGHT*scale)},
                {0, 0}, 0, WHITE);
    }
    if(inventory_slots[24].filled_with){
        DrawTexturePro(
                items_tex,
                inventory_slots[24].filled_with->img_rect,
                {hotbar_pos.x*scale+HOTBAR_SLOT_2_OFFSET_X*scale, hotbar_pos.y*scale,
                 float(ITEM_SPRITE_WIDTH*scale),
                 float(ITEM_SPRITE_HEIGHT*scale)},
                {0, 0}, 0, WHITE);
    }
    if(inventory_slots[25].filled_with){
        DrawTexturePro(
                items_tex,
                inventory_slots[25].filled_with->img_rect,
                {hotbar_pos.x*scale+HOTBAR_SLOT_3_OFFSET_X*scale, hotbar_pos.y*scale,
                 float(ITEM_SPRITE_WIDTH*scale),
                 float(ITEM_SPRITE_HEIGHT*scale)},
                {0, 0}, 0, WHITE);
    }
    // DrawText(std::to_string(player.dungeon_keys).c_str(), (hotbar_pos.x+104)*scale, (hotbar_pos.y-1)*scale, 17, (Color){51, 57, 65, 255});

    //layers (!)
    DrawTextEx(global_font, std::to_string(player.dungeon_keys).c_str(), Vector2Scale({hotbar_pos.x+HOTBAR_KEY_TEXT_OFFSET_X, hotbar_pos.y-HOTBAR_KEY_TEXT_OFFSET_Y}, scale), DEFAULT_FONT_SIZE*scale, 1, BLACK);
    DrawTextEx(global_font, std::to_string(player.dungeon_keys).c_str(), Vector2Scale({hotbar_pos.x+HOTBAR_KEY_TEXT_OFFSET_X, hotbar_pos.y-HOTBAR_KEY_TEXT_OFFSET_Y}, scale), DEFAULT_FONT_SIZE*scale, 1, GUI_DARK_GRAY);
    DrawTextEx(global_font, std::to_string(player.dungeon_keys).c_str(), Vector2Scale({hotbar_pos.x+HOTBAR_KEY_TEXT_OFFSET_X, hotbar_pos.y-HOTBAR_KEY_TEXT_OFFSET_Y}, scale), DEFAULT_FONT_SIZE*scale, 1, GUI_DARK_GRAY);
    
}

void start_textbox(){
    DrawTextureEx(textbox_tex, Vector2Scale({0, 110}, scale), 0, scale, WHITE);
    DrawTextEx(global_font, current_dialog[dialog_index_state].text, Vector2Scale({textbox_pos.x+5, textbox_pos.y+5}, scale), DEFAULT_FONT_SIZE*scale, 1, WHITE);
    if(IsKeyPressed(KEY_INTERACT)){
        dialog_index_state++;
    }
}

void init_gui()
{
    inv_cursor_init();
    inventory_tex = LoadTexture(INVENTORY_PATH);
    items_tex = LoadTexture(ITEM_SHEET_PATH);
    inventory_cursor_tex = LoadTexture(INV_CURSOR_PATH);
    health_bar_tex = LoadTexture(HEALTH_BAR_PATH);
    hotbar_tex = LoadTexture(HOTBAR_TEX_PATH);
    global_font = LoadFont(GLOB_FONT_PATH);
    textbox_tex = LoadTexture(TEXTBOX_TEX_PATH);
}

void update_gui()
{
    // maybe a performance problem but whatever
    // health_bar_draw(); //genuinely WHY was this here
    if (is_inv_open)
    {
        inv_cursor_update();
    }

    if (IsKeyPressed(KEY_OPEN_INVENTORY))
    {
        is_inv_open = !is_inv_open;
        if (is_inv_open)
        {
            player.move_mode = 0;
            player.current_animation_frame = 0;
            for(auto &e : entities){
                e->move_mode = 0;
            }
        }
        else
        {

            player.move_mode = 1;
            for(auto &e : entities){
                e->move_mode = 1;
            }
        }
    }
}

void draw_gui()
{
    hotbar_draw();
    health_bar_draw();
    if (is_inv_open)
    {
        // drawing inventory
        DrawTextureEx(inventory_tex, {0, 0}, 0, scale, WHITE);
        // drawing cursor

        DrawTexturePro(inventory_cursor_tex, inv_cursor_anim[inv_cursor.current_anim_frame], {(inventory_slots[inv_cursor.inv_slot_index].pos.x - 3)*scale, (inventory_slots[inv_cursor.inv_slot_index].pos.y - 1)*scale, inv_cursor_anim[inv_cursor.current_anim_frame].width*scale, inv_cursor_anim[inv_cursor.current_anim_frame].height*scale}, {0, 0}, 0, WHITE);
        // drawing held item if there is a held item
        if (inv_cursor.held_item)
        {
            DrawTexturePro(items_tex, inv_cursor.held_item->img_rect, {inventory_slots[inv_cursor.inv_slot_index].pos.x*scale-(1*scale), inventory_slots[inv_cursor.inv_slot_index].pos.y*scale-(1*scale), float(ITEM_SPRITE_WIDTH*scale), float(ITEM_SPRITE_HEIGHT*scale)}, {0, 0}, 0, WHITE);
        }
        // drawing items
        for (Inventory_slot &s : inventory_slots)
        {
            if (!s.filled_with)
                continue; // IMPORTANT

            DrawTexturePro(
                items_tex,
                s.filled_with->img_rect,
                {s.pos.x*scale, s.pos.y*scale,
                 float(ITEM_SPRITE_WIDTH*scale),
                 float(ITEM_SPRITE_HEIGHT*scale)},
                {0, 0}, 0, WHITE);
        }
    }
}
