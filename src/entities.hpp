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



#endif