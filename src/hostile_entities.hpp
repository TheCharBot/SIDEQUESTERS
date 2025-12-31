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


class Enemy_forest_scourge: public Entity{
    public:
        Vector2 pos{};
        Rectangle rect;
        int max_animation_frames;
        int current_animation_frame;
        int animation_frame_5;

        Enemy_forest_scourge();

        ~Enemy_forest_scourge() override;
        //load for loading texture data, dont load in constructor
        void load() override;
        void update() override;
        void draw() override;
        
        void wander_patrol();
        void chase();
        void attack();
        void run_away();
    private:
        int health;
        int random_index;
        Rectangle *current_anim_arr;
        Rectangle hitbox;
        Texture2D tex;
};

#endif