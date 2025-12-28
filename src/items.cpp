#include "items.hpp"


Item Stick;

void init_stick(){
    Stick.img_rect = STICK_SPRITE_RECT;
    Stick.inventory_index = 23;
    Stick.type = COMBAT_MELEE;
    Stick.melee.damage = STICK_DAMAGE;
    Stick.melee.speed = STICK_SPEED;
    //uninitialized hitbox 
    Stick.melee.hitbox = {};
}

void init_items(){
    
    init_stick();
}

