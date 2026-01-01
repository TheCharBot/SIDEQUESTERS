#ifndef HOSTILE_ENTITIES
#define HOSTILE_ENTITIES

#include "assets.hpp"
#include "config.hpp"
#include "player.hpp"
#include "enemy_assets.hpp"

//Behavior Tree for now:
// Selector
// ├── Sequence (Patrol)
// │   ├── Condition (IsPatrolling)
// │   └── Action (Patrol)
// ├── Sequence (Chase)
// │   ├── Condition (IsPlayerInRange)
// │   └── Action (Chase)
// ├── Sequence (Attack)
// │   ├── Condition (IsPlayerInRange)
// │   └── Action (Attack)
// └── Sequence (Flee)
//     ├── Condition (IsHealthLow)
//     └── Action (Flee)

extern void unload_enemy_textures();

class Enemy_forest_scourge: public Entity{
    public:
        Vector2 pos{};
        
        int max_animation_frames;
        int current_animation_frame;
        int animation_frame_5;
        static Texture2D shared_tex;
        static bool texture_loaded;

        Enemy_forest_scourge();

        ~Enemy_forest_scourge() override;
        //load for loading texture data, dont load in constructor
        void load() override;
        void update() override;
        void draw() override;
        
        void wander();
        void chase();
        void attack();
        void run_away();
        void decide_action();
    private:
        Direction direction;
        int health;
        int random_index;
        Wander_directions wander_mode;
        int wander_state;
        Rectangle *current_anim_arr;
        
        //use static shared when there are multiple instances
        
        Vector2 originial_pos;
};




#endif