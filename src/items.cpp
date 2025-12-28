#include "items.hpp"


Item Stick;

void init_stick(){
    Stick.img_rect = STICK_RECT;
    Stick.inventory_index = 0;
    Stick.type = COMBAT_MELEE;
    Stick.melee.damage = STICK_DAMAGE;
    Stick.melee.speed = STICK_SPEED;
}

void init_items(){
    
    init_stick();
}

