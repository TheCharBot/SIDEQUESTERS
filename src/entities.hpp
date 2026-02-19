#ifndef MAP_OBJECTS_HPP
#define MAP_OBJECTS_HPP

#include "player.hpp"



class Village_windmill : public Entity{
    public:
        Village_windmill();
        ~Village_windmill() override;
        
        int max_animation_frames;
        int current_animation_frame;
        int animation_frame_5;

        void load() override;
        void update() override;
        void draw() override;

    private:
        Texture2D tex{};
};



class Start_bulldozer : public Entity {
public:
    Start_bulldozer();
    ~Start_bulldozer() override;
    
    void load() override;
    void update() override;
    void draw() override;

private:
    bool fallen;
    Texture2D tex{};
};


class Start_portal : public Entity {
public:
    Start_portal();
    ~Start_portal() override;
    int max_animation_frames;
    int current_animation_frame;
    int animation_frame_5;
    
    void load() override;
    void update() override;
    void draw() override;

private:
    
    Texture2D tex{};
};


class Big_tree : public Entity {
    public:
        Big_tree();
        ~Big_tree() override;
        int max_animation_frames;
        int current_animation_frame;
        int animation_frame_5;
        
        void load() override;
        void update() override;
        void draw() override;
    private:
        Rectangle rect1;
        Rectangle rect2;
        Rectangle rect3;
        
        Texture2D tex;
};

class Big_tree_level_tree_trunk : public Entity {
    public:
        
        Big_tree_level_tree_trunk(int which_trunk);
        ~Big_tree_level_tree_trunk() override;
        int max_animation_frames;
        int current_animation_frame;
        int animation_frame_5;
        
        void load() override;
        void update() override;
        void draw() override;
        
    private:
        
        float health;
        Texture2D tex;
        bool can_take_damage;
        float hit_flash_timer;
        float iframe_timer;
};

class Village_questgiver_1 : public Entity{
    public:
        Village_questgiver_1();
        ~Village_questgiver_1() override;
        
        int max_animation_frames;
        int current_animation_frame;
        int animation_frame_5;

        Rectangle *current_animation_arr;

        void load() override;
        void update() override;
        void draw() override;

    private:
        Texture2D tex{};
};


#endif