#ifndef MAP_OBJECTS_HPP
#define MAP_OBJECTS_HPP

#include "config.hpp"




#include "map_loader.hpp"
#include "assets.hpp"





class Entity {
public:
    Vector2 pos{};
    Rectangle img_rect;
    Rectangle rect;
    virtual ~Entity() = default;

    virtual void load() {}
    virtual void update() = 0;
    virtual void draw() = 0;
};


class Start_portal : public Entity {
public:
    Start_portal();
    ~Start_portal() override;
    
    void load() override;
    void update() override;
    void draw() override;

private:
    Texture2D tex{};
};

extern std::vector<std::unique_ptr<Entity>> entities;

#endif