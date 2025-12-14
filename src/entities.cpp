#include "entities.hpp"






// std::vector<int> load_list;

Start_portal::Start_portal() {
    // optional: initial position
    max_animation_frames = 4;
    current_animation_frame = 0;
    animation_frame_5 = 0;
    
    pos = {float(START_PORTAL_X), float(START_PORTAL_Y)};
}

Start_portal::~Start_portal() {
    if (tex.id != 0) {
        UnloadTexture(tex);
    }
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