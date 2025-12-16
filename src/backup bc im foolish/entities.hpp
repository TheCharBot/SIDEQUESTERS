#ifndef MAP_OBJECTS_HPP
#define MAP_OBJECTS_HPP

#include "config.hpp"





#include "assets.hpp"
#include "player.hpp"




class Entity {
public:
    Vector2 pos{};
    Rectangle img_rect;
    Rectangle rect;
    int max_animation_frames;
    int current_animation_frame;
    int animation_frame_5;

    virtual ~Entity() = default;

    virtual void load() {}
    virtual void update() = 0;
    virtual void draw() = 0;
};

class Start_bulldozer : public Entity {
public:
    Start_bulldozer();
    ~Start_bulldozer() override;
    
    void load() override;
    void update() override;
    void draw() override;

private:
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

extern std::vector<std::unique_ptr<Entity>> entities;

#endif