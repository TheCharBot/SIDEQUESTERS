#include "vfx.hpp"

VFX vfx;

void init_vfx(){
    
   
};

void start_screen_shake(float duration, float magnitude)
{
    vfx.shake_time = duration;
    vfx.shake_duration = duration;
    vfx.shake_magnitude = magnitude;
}
Vector2 shake_screen(){
    if (vfx.shake_time <= 0.0f) return {0, 0};

    float strength = vfx.shake_magnitude * (vfx.shake_time / vfx.shake_duration);

    return {
        GetRandomValue(-100, 100) / 100.0f * strength,
        GetRandomValue(-100, 100) / 100.0f * strength
    };
}

void update_vfx()
{
    if (vfx.shake_time > 0.0f)
    {
        vfx.shake_time -= GetFrameTime();
    }
    cam.offset = shake_screen();
}
