#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <functional>
#include <iostream>
#include <memory>
#include <algorithm>
#include <optional>
#include <fstream>
#include <cstdio>

// #include "dialog/dialog.hpp" TODO: Do IT (save for later right now)

//this file is only for settings and global vars, use assets for specific things






#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 180


//implement version major when a playable state is reached. add to version minor if a new map is made. add to version path if the game is released with bugs
#define VERSION_MAJOR 0
#define VERSION_MINOR 3
#define VERSION_PATCH 0

const int CONFIG_MAGIC = 0x43464731; // "CFG1"
const int CONFIG_VERSION = 1;


extern Camera2D cam;

//pretty important
//also, hear me out, this BELONGS here
enum Facing
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};



#define ANIMATION_INTERVAL 5

#define TEN_EIGHTY_SCALE 6
#define FOURTEEN_FORTY_SCALE 8
#define FOUR_K_SCALE 12





extern int scale;

#endif