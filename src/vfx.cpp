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

void start_hitstop(float duration){
    vfx.hitstop_time = duration;
    vfx.hitstop_duration = duration;
    
}

void pause_for_hitstop(){
    
    WaitTime(vfx.hitstop_duration/HITSTOP_TIMER_DAMAGE_DIVIDER);
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
    
    // pause_for_hitstop();
    if(vfx.hitstop_time > 0.0f){
        
        vfx.hitstop_time -= GetFrameTime();
        vfx.hitstop_duration = 0.0f;
    }
    cam.offset = shake_screen();
}
