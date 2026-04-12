#ifndef MAP_OBJECTS_HPP
#define MAP_OBJECTS_HPP

#include "player.hpp"

class Village_windmill : public Entity{
    public:
        Village_windmill();
        ~Village_windmill() override;
        
        

        void load() override;
        void update() override;
        void draw() override;

    private:
        Texture2D tex{};
};

class Village_windmill_grinder : public Entity{
    public:
        Village_windmill_grinder();
        ~Village_windmill_grinder() override;
        
        

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
    bool fallen = 0;
    Texture2D tex{};
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


class Big_tree : public Entity {
    public:
        Big_tree();
        ~Big_tree() override;
        
        
        void load() override;
        void update() override;
        void draw() override;
    private:
        Rectangle rect1 = {};
        Rectangle rect2 = {};
        Rectangle rect3 = {};
        
        Texture2D tex = {};
};

class Big_tree_level_tree_trunk : public Entity {
    public:
        
        Big_tree_level_tree_trunk(int which_trunk);
        ~Big_tree_level_tree_trunk() override;
        
        
        void load() override;
        void update() override;
        void draw() override;
        
    private:
        
        float health = 0;
        Texture2D tex = {};
        bool can_take_damage = 0;
        float hit_flash_timer = 0;
        float iframe_timer = 0;
};



class Berry_bush : public Entity{
    public:
        Berry_bush(int index);
        ~Berry_bush();
        void load() override;
        void update() override;
        void draw() override;
        
    private:
        Texture2D tex = {};
        float health = 0;
        Ground_item item_drop = {};
        float flash_time = 0;
};

class Ground_pot : public Entity{
    public:
        Ground_pot(Vector2 wanted_pos);
        ~Ground_pot();
        void load() override;
        void update() override;
        void draw() override;
        void take_knockback(Vector2 origin, int strength);
        void update_knockback();
        void rect_rebuild();
        void pot_break();
    private:
        Texture2D tex = {};
        float health = 0;
        Ground_item item_drop = {};
        float flash_time = 0;
        Vector2 knockback_vel = {};
        float knockback_time = 0;
        bool broken = false;
};

class Message_board : public Entity {
    public:
        Message_board(int init_type_index);
        ~Message_board() override;
        
        
        void load() override;
        void update() override;
        void draw() override;
        enum Message_board_type{
            ARROW_KEYS,
            X_ACTION,
            Z_ACTION,
            SHIFT_ACTION,
            TAB_ACTION,
            HOTBAR_SLOT_ACTIONS,
            ENTER_ACTION,
            F10_ACTION,
            ESC_ACTION,
            REWRITE_ACTION
        };
    private:
        
        Message_board_type msg_brd_typ = {};
        Rectangle detect_and_appear_range = {};
        Rectangle img_rect;
        Texture2D tex = {};
        Color fade = {};
        int temp_fade = 0;
};



#endif