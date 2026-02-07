#ifndef ITEM_DATA_HPP
#define ITEM_DATA_HPP

//just #defines for item data such as damage, speed, etc
//for damage, it should be "name"_"damage" and then damage
#define STICK_DAMAGE 1

//for speed, do the same as damage but with speed
#define STICK_SPEED 1

//then rects in the image (if the size of the image gets too big ill probably split it, but its still always loaded in vram, so im kinda stuck)
#define STICK_SPRITE_RECT {0, 0, ITEM_SPRITE_WIDTH, ITEM_SPRITE_HEIGHT}
#define SACRED_BARK_SPRITE_RECT {32, 0, ITEM_SPRITE_WIDTH, ITEM_SPRITE_HEIGHT}
#define DUNGEON_KEY_SPRITE_RECT {64, 0, ITEM_SPRITE_WIDTH, ITEM_SPRITE_HEIGHT}

//other assorted thingys
#define BIG_TREE_LEVEL_1_STICK_POS {152, 128}
#define BIG_TREE_LEVEL_2_KEY_POS {144, 80}



#endif


