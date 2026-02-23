#include "sfx.hpp"



std::unordered_map<SFX, Sound> sound_effects;

void init_sfx()
{

    


    sound_effects[SFX::PLAYER_SWING_SWORD] = LoadSound("sfx/player/swing_sword.wav"); //TODO: MACROS
    sound_effects[SFX::PLAYER_FOOTSTEPS] = LoadSound("sfx/player/footsteps.wav");
    sound_effects[SFX::INV_CURSOR_PICKUP] = LoadSound("sfx/gui/inv_cursor_pickup.wav");
    sound_effects[SFX::INV_CURSOR_SELECT] = LoadSound("sfx/gui/inv_cursor_select.wav");
    sound_effects[SFX::DAMAGE_PLAYER] = LoadSound("sfx/player/hit.wav");
    sound_effects[SFX::UNLOCK_DOOR] = LoadSound("sfx/world/unlock_door.wav");
    sound_effects[SFX::PICKUP_ITEM] = LoadSound("sfx/player/pickup_item.wav");
    sound_effects[SFX::THE_REGROWN_FALL] = LoadSound("sfx/entities/regrown/regrown_fall.wav");
    sound_effects[SFX::THE_REGROWN_GROUND_ATTACK] = LoadSound("sfx/entities/regrown/ground_shake_attack.wav");
    sound_effects[SFX::THE_REGROWN_DIE] = LoadSound("sfx/entities/regrown/death.wav");
    sound_effects[SFX::THE_REGROWN_ARM_ATTACK] = LoadSound("sfx/entities/regrown/arm_attack.wav");
    sound_effects[SFX::GLOB_SWING_SWORD] = LoadSound("sfx/world/swing_sword.wav");
}



void update_sfx()
{
    // if(!IsSoundPlaying(sound_effects[SFX::PLAYER_SWING_SWORD])){
    //     PlaySound(sound_effects[SFX::PLAYER_SWING_SWORD]);
    // }
}
