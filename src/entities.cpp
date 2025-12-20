#include "entities.hpp"



Start_bulldozer::Start_bulldozer(){
    current_animation_frame = 0;
    pos = {START_BULLDOZER_X, START_BULLDOZER_Y};
    collided = false;
}

Start_bulldozer::~Start_bulldozer(){
    if (tex.id != 0) {
        UnloadTexture(tex);
    }
    rect = {};
    // pos = {START_BULLDOZER_X, START_BULLDOZER_Y};
}


void Start_bulldozer::load(){
    tex = LoadTexture(BULLDOZER_TEX_PATH);
}
void Start_bulldozer::update(){
    rect = {pos.x, pos.y, START_BULLDOZER_WIDTH, START_BULLDOZER_HEIGHT};
    if(player.normal_hitbox.y <= BULLDOZER_TRIGGER_Y){
        player.move_mode = 0;
        if(player.normal_hitbox.y>160){
            player.pos.y-=PLAYER_SPEED;
        }
        if(pos.x<MAX_BULLDOZER_X){
            pos.x+=BULLDOZER_SPEED;
        }
        if(CheckCollisionRecs(player.normal_hitbox, rect)){
            collided = true;
            
            
        }

    }
    
}
void Start_bulldozer::draw(){
    
    DrawTexturePro(tex, start_bulldozer_animation[current_animation_frame], {pos.x*scale, pos.y*scale, float(START_BULLDOZER_WIDTH*scale), float(START_BULLDOZER_HEIGHT*scale)}, {0, 0}, 0, WHITE);
    if(collided){
        DrawRectangle(0, 0, map_to_load.width*scale, map_to_load.height*scale, BLACK);
        collided = false;
        requested_map = 2;
        
    }
}



//portal stuff
Start_portal::Start_portal() {
    
    max_animation_frames = 4;
    current_animation_frame = 0;
    animation_frame_5 = 0;
    
    pos = {float(START_PORTAL_X), float(START_PORTAL_Y)};
}

Start_portal::~Start_portal() {
    if (tex.id != 0) {
        UnloadTexture(tex);
    }
    rect = {};
}

void Start_portal::load() {
    
    tex = LoadTexture(PORTAL_TEX_PATH);
}

void Start_portal::update() {
    animation_frame_5++;
    if(animation_frame_5 >= ANIMATION_INTERVAL){
        current_animation_frame++;
        if(current_animation_frame >= max_animation_frames){
            current_animation_frame = 0;
        }
        animation_frame_5 = 0;
    }
    
    // portal logic
}

void Start_portal::draw() {
    
    DrawTexturePro(tex, start_portal_animation[current_animation_frame], {pos.x*scale, pos.y*scale, float(START_PORTAL_WIDTH*scale), float(START_PORTAL_HEIGHT*scale)}, {0, 0}, 0, WHITE);
}

