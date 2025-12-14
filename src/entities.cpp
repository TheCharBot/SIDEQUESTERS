#include "entities.hpp"






// std::vector<int> load_list;

Start_portal::Start_portal() {
    // optional: initial position
    pos = {float(START_PORTAL_X*scale), float(START_PORTAL_Y*scale)};
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
    // portal logic
}

void Start_portal::draw() {
    DrawTexture(tex, pos.x, pos.y, WHITE);
}