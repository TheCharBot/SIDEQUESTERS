#include "sfx.hpp"



std::unordered_map<SFX_ids, Sound> sfx_manager;

void init_sfx()
{

    


    sfx_manager[SFX_ids::PLAYER_SWING_SWORD] = LoadSound("sfx/player/swing_sword.wav"); //TODO: MACROS
    sfx_manager[SFX_ids::PLAYER_FOOTSTEPS] = LoadSound("sfx/player/footsteps.wav");
    sfx_manager[SFX_ids::INV_CURSOR_PICKUP] = LoadSound("sfx/gui/inv_cursor_pickup.wav");
    sfx_manager[SFX_ids::INV_CURSOR_SELECT] = LoadSound("sfx/gui/inv_cursor_select.wav");
    sfx_manager[SFX_ids::DAMAGE_PLAYER] = LoadSound("sfx/player/hit.wav");
    sfx_manager[SFX_ids::UNLOCK_DOOR] = LoadSound("sfx/world/unlock_door.wav");
    sfx_manager[SFX_ids::PICKUP_ITEM] = LoadSound("sfx/player/pickup_item.wav");
    sfx_manager[SFX_ids::THE_REGROWN_FALL] = LoadSound("sfx/entities/regrown/regrown_fall.wav");
    sfx_manager[SFX_ids::THE_REGROWN_GROUND_ATTACK] = LoadSound("sfx/entities/regrown/ground_shake_attack.wav");
    sfx_manager[SFX_ids::THE_REGROWN_DIE] = LoadSound("sfx/entities/regrown/death.wav");
    sfx_manager[SFX_ids::THE_REGROWN_ARM_ATTACK] = LoadSound("sfx/entities/regrown/arm_attack.wav");
    sfx_manager[SFX_ids::GLOB_SWING_SWORD] = LoadSound("sfx/world/swing_sword.wav");
}



void update_sfx()
{
    // if(!IsSoundPlaying(sound_effects[SFX_ids::PLAYER_SWING_SWORD])){
    //     PlaySound(sound_effects[SFX_ids::PLAYER_SWING_SWORD]);
    // }
}
