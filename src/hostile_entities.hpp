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
        //use static shared when there are multiple instances
        static Texture2D shared_tex;
        static bool texture_loaded;

        Enemy_forest_scourge();

        ~Enemy_forest_scourge() override;
        //load for loading texture data, dont load in constructor
        void load() override;
        void update() override;
        void draw() override;

        void take_damage(float damage, Vector2 hit_source_pos);
        void wander();
        void chase();
        void attack();
        void run_away();
        void decide_action();
    private:
        Direction direction;
        
        int random_index;
        Wander_directions wander_mode;
        int wander_state;
        Rectangle *current_anim_arr;
        Rectangle chase_detect_rect;
        Rectangle attack_detect_rect;
        Rectangle attack_hit_rect;
        float hit_flash_timer;
        float health;
        bool can_take_damage;
        float iframe_timer;
        Vector2 originial_pos;
};

class The_Regrown: public Entity{
    public:
        Vector2 pos{};
        
        int max_animation_frames;
        int current_animation_frame;
        int animation_frame_5;
        //use static shared when there are multiple instances
        

        The_Regrown();

        ~The_Regrown() override;
        //load for loading texture data, dont load in constructor
        void load() override;
        void update() override;
        void draw() override;
        

        void take_damage(float damage);
        void right_arm_attack();
        void left_arm_attack();
        void ground_shake_attack();
        void decide_action();
        void fall_down();
        void idle_animation();
    private:
        Texture2D tex;
        int random_index;
        Rectangle *current_anim_arr;
        Rectangle attack_detect_rect;
        Rectangle attack_hit_rect;
        float hit_flash_timer;
        float health;
        bool can_take_damage;
        float iframe_timer;
        Rectangle col_rect_1;
        Rectangle col_rect_2;
        Rectangle col_rect_3;
        bool loaded_rects;
        bool death_anim_started;
        Rectangle active_damaging_rect;
};




#endif