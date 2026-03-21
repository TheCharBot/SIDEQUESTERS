#include "assets.hpp"

// this file is for image and other constant rects

KeyboardKey KEY_CONTROLS_UP = KEY_UP;
KeyboardKey KEY_CONTROLS_DOWN = KEY_DOWN;
KeyboardKey KEY_CONTROLS_RIGHT = KEY_RIGHT;
KeyboardKey KEY_CONTROLS_LEFT = KEY_LEFT;
KeyboardKey KEY_ITEM_HOTBAR_1 = KEY_A;
KeyboardKey KEY_ITEM_HOTBAR_2 = KEY_S;
KeyboardKey KEY_ITEM_HOTBAR_3 = KEY_D;
KeyboardKey KEY_OPEN_INVENTORY = KEY_TAB;
KeyboardKey KEY_INTERACT = KEY_X;
KeyboardKey KEY_SPEEDUP = KEY_Z;
KeyboardKey KEY_SAVE = KEY_ENTER;
KeyboardKey KEY_SPRINT = KEY_LEFT_SHIFT;


// 23, 24, 25
// IM SORRY. It couldnt be avoided.
Inventory_slot inventory_slots[28] = {
    {{48, 32}, 0, {}},
    {{80, 32}, 0, {}},
    {{112, 32}, 0, {}},
    {{147, 32}, 0, {}},
    {{182, 32}, 0, {}},
    {{214, 32}, 0, {}},
    {{246, 32}, 0, {}},
    {{48, 64}, 0, {}},
    {{80, 64}, 0, {}},
    {{112, 64}, 0, {}},
    {{147, 64}, 0, {}},
    {{182, 64}, 0, {}},
    {{214, 64}, 0, {}},
    {{246, 64}, 0, {}},
    {{48, 96}, 0, {}},
    {{80, 96}, 0, {}},
    {{112, 96}, 0, {}},
    {{147, 96}, 0, {}},
    {{182, 96}, 0, {}},
    {{214, 96}, 0, {}},
    {{246, 96}, 0, {}},
    {{48, 128}, 0, {}},
    {{80, 128}, 0, {}},
    {{112, 128}, 0, {}}, // hotbar Q
    {{147, 128}, 0, {}}, // hotbar E
    {{182, 128}, 0, {}}, // hotbar Z
    {{214, 128}, 0, {}},
    {{246, 128}, 0, {}},

};





Rectangle the_regrown_possible_destructable_tile_area = {48, 64, 224, 208};
Rectangle the_regrown_impossible_destructable_tile_area = {128, 144, 64, 64};

