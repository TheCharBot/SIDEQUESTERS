#include "sfx.hpp"




void init_sfx()
{

    


    game.sfx_manager[SFX_ids::PLAYER_SWING_SWORD] = LoadSound("sfx/player/swing_sword.wav"); //TODO: MACROS
    game.sfx_manager[SFX_ids::PLAYER_FOOTSTEPS] = LoadSound("sfx/player/footsteps.wav");
    game.sfx_manager[SFX_ids::INV_CURSOR_PICKUP] = LoadSound("sfx/gui/inv_cursor_pickup.wav");
    game.sfx_manager[SFX_ids::INV_CURSOR_SELECT] = LoadSound("sfx/gui/inv_cursor_select.wav");
    game.sfx_manager[SFX_ids::DAMAGE_PLAYER] = LoadSound("sfx/player/hit.wav");
    game.sfx_manager[SFX_ids::UNLOCK_DOOR] = LoadSound("sfx/world/unlock_door.wav");
    game.sfx_manager[SFX_ids::PICKUP_ITEM] = LoadSound("sfx/player/pickup_item.wav");
    game.sfx_manager[SFX_ids::THE_REGROWN_FALL] = LoadSound("sfx/entities/regrown/regrown_fall.wav");
    game.sfx_manager[SFX_ids::THE_REGROWN_GROUND_ATTACK] = LoadSound("sfx/entities/regrown/ground_shake_attack.wav");
    game.sfx_manager[SFX_ids::THE_REGROWN_DIE] = LoadSound("sfx/entities/regrown/death.wav");
    game.sfx_manager[SFX_ids::THE_REGROWN_ARM_ATTACK] = LoadSound("sfx/entities/regrown/arm_attack.wav");
    game.sfx_manager[SFX_ids::GLOB_SWING_SWORD] = LoadSound("sfx/world/swing_sword.wav");
}



void update_sfx()
{
    // if(!IsSoundPlaying(sound_effects[SFX_ids::PLAYER_SWING_SWORD])){
    //     PlaySound(sound_effects[SFX_ids::PLAYER_SWING_SWORD]);
    // }
}
