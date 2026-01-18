#ifndef VFX_HPP
#define VFX_HPP

#include "assets.hpp"
#include "config.hpp"

extern VFX vfx;
extern void init_vfx();
void start_screen_shake(float duration, float magnitude);
Vector2 shake_screen();

#endif