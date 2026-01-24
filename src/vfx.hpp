#ifndef VFX_HPP
#define VFX_HPP

#include "assets.hpp"
#include "config.hpp"

//visual effects such as screen shake and stuff, or really any GUI that needs to be drawn before camera mode is turned off

extern VFX vfx;
extern void init_vfx();
extern void start_screen_shake(float duration, float magnitude);
extern void start_hitstop(float duration);
extern void pause_for_hitstop();
extern Vector2 shake_screen();
extern void update_vfx();


#endif