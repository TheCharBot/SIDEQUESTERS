#ifndef HOSTILE_ENTITIES
#define HOSTILE_ENTITIES

#include "assets.hpp"
#include "config.hpp"
#include "player.hpp"
#include "enemy_assets.hpp"
#include "vfx.hpp"

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
        
        
        //use static shared when there are multiple instances
        
        

        Enemy_forest_scourge();

        ~Enemy_forest_scourge() override;
        //load for loading texture data, dont load in constructor
        void load() override;
        void update() override;
        void draw() override;

        void take_damage(float damage, Vector2 hit_source_pos, int strength);
        void wander();
        void chase();
        void attack();
        void run_away();
        void decide_action();
        void update_knockback();
        void rect_rebuild();
    private:
        Texture2D tex = {};
        int random_index = 0;
        int wander_state = 0;
        Rectangle *current_anim_arr = {};
        Rectangle chase_detect_rect = {};
        Rectangle attack_detect_rect = {};
        Rectangle attack_hit_rect = {};
        float hit_flash_timer = 0;
        float health = 0;
        bool can_take_damage = 0;
        float iframe_timer = 0;
        float wander_timer = 0.0f;
        Vector2 wander_dir = {0, 0};
        Vector2 move = {};
        Vector2 vel = {};
        enum Behavior_mode{
            ATTACK,
            CHASE,
            WANDER,
            DIE
        };
        Enemy_forest_scourge::Behavior_mode behavior_mode = {};
        Vector2 knockback_vel = {};
        float knockback_time = 0;
};

class Boss_The_Regrown: public Entity{
    public:
        Vector2 pos{};
        
        
        //use static shared when there are multiple instances
        

        Boss_The_Regrown();

        ~Boss_The_Regrown() override;
        //load for loading texture data, dont load in constructor
        void load() override;
        void update() override;
        void draw() override;
        
        void init_item_drop();

        void take_damage(float damage);
        void right_arm_attack();
        void left_arm_attack();
        void ground_shake_attack();
        void decide_action();
        void fall_down();
        void idle_animation();
        void break_random_floor_tiles(int amount);
        
    private:
        Texture2D tex = {};
        int random_index = 0;
        Rectangle *current_anim_arr = {};
        Rectangle attack_detect_rect = {};
        Rectangle attack_hit_rect = {};
        float hit_flash_timer = 0;
        float health = 0;
        bool can_take_damage = 0;
        float iframe_timer = 0;
        Rectangle col_rect_1 = {};
        Rectangle col_rect_2 = {};
        Rectangle col_rect_3 = {};
        bool started_fight = 0;
        bool death_anim_started = 0;
        Rectangle active_damaging_rect = {};
        float ground_attack_cooldown = 0;
        bool can_use_ground_attack = 0;
        Ground_item item_drop = {};
        enum Behavior_mode{
            RIGHT_ATTACK,
            LEFT_ATTACK,
            GROUND_ATTACK,
            IDLE,
        };
        Boss_The_Regrown::Behavior_mode behavior_mode = {};
};




#endif