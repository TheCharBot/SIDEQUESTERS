#ifndef HOSTILE_ENTITIES
#define HOSTILE_ENTITIES

#include "assets.hpp"
#include "config.hpp"

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
    private:
        
        Rectangle *current_anim_arr;
        Texture2D tex;
};

#endif