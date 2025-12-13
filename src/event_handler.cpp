#include "event_handler.hpp"

void init_all(){
    init_map();
    init_player();
    load_map(0);
    cam.target = { 0.0f, 0.0f };
    cam.offset = {0, 0};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;    
}

void update_all(){
    
    update_map();
    update_player();
    
}

void draw_all(){
    BeginMode2D(cam);
    draw_map();
    draw_player();
};
