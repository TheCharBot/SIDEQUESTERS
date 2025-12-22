#include "event_handler.hpp"
//event handler, draw_all, init_all, update_all, and camera stuff
void init_all(){
    init_map();
    init_player();
    request_map(START_MAP, {PLAYER_START_MAP_POS_X, PLAYER_START_MAP_POS_Y});
    cam.target = { 0.0f, 0.0f };
    cam.offset = {0, 0};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;    
}

void update_all(){
    
    update_map();
    update_player();
    for (auto& e : entities){
        e->update();
    } 
    
    
    cam.target.x = player.pos.x*scale - ((WINDOW_WIDTH * scale) / 2) + (PLAYER_SPRITE_WIDTH * scale / 2);
    cam.target.y = player.pos.y*scale - ((WINDOW_HEIGHT * scale) / 2) + (PLAYER_SPRITE_HEIGHT * scale / 2);

    
    cam.target.x = Clamp(cam.target.x, 0, (map_to_load.width*scale) - (WINDOW_WIDTH * scale));
    cam.target.y = Clamp(cam.target.y, 0, (map_to_load.height*scale) - (WINDOW_HEIGHT * scale));
    if (requested_map != WRONG_MAP) {
        if(current_map != requested_map){
            load_map(requested_map, requested_player_pos);
        }
        requested_map = WRONG_MAP;
    }
}

void draw_all(){
    BeginMode2D(cam);
    draw_map();
    for (auto& e : entities){
        e->draw();
    } 
    
    draw_player();
    for (auto& e : entities){
        if(e->rect.y>player.normal_hitbox.y){
            e->draw();
            
        }
    } 
    
        
    EndMode2D();
};
