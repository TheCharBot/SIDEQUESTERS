#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <functional>
#include <iostream>
#include <memory>
#include <algorithm>

//this file is only for settings and global vars, use assets for specific things

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 180

#define VERSION_MAJOR 0
#define VERSION_MINOR 3
#define VERSION_PATCH 0



extern Camera2D cam;



#define ANIMATION_INTERVAL 5

#define TEN_EIGHTY_SCALE 6
#define FOURTEEN_FORTY_SCALE 8
#define FOUR_K_SCALE 12





extern int scale;

#endif