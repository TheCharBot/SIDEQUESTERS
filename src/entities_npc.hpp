#ifndef ENTITIES_NPC_HPP
#define ENTITIES_NPC_HPP


#include "player.hpp"

class NPC_Dan_Village : public Entity{
    public:
        NPC_Dan_Village();
        ~NPC_Dan_Village() override;
        
        

        


        void load() override;
        void update() override;
        void draw() override;

    private:
        Rectangle interact_rect = {};
        Texture2D tex{};
        bool found_wanted_item = false;
};

class NPC_Bob_Village : public Entity{
    public:
        NPC_Bob_Village();
        ~NPC_Bob_Village() override;
        
        

        


        void load() override;
        void update() override;
        void draw() override;

    private:
        Rectangle interact_rect = {};
        Texture2D tex{};
        
};

class NPC_Clarence_Village : public Entity{
    public:
        NPC_Clarence_Village();
        ~NPC_Clarence_Village() override;
        
        

        


        void load() override;
        void update() override;
        void draw() override;

    private:
        Rectangle interact_rect = {};
        Texture2D tex{};
        
};

class NPC_Chad_Village : public Entity{
    public:
        NPC_Chad_Village();
        ~NPC_Chad_Village() override;
        
        

        


        void load() override;
        void update() override;
        void draw() override;

    private:
        Rectangle *next_anim_arr;
        Rectangle interact_rect = {};
        Texture2D tex{};
        
};

class NPC_fallen_hero_Village : public Entity{
    public:
        NPC_fallen_hero_Village();
        ~NPC_fallen_hero_Village() override;
        
        

        


        void load() override;
        void update() override;
        void draw() override;

    private:
        Rectangle *next_anim_arr;
        Rectangle interact_rect = {};
        Texture2D tex{};
        bool rolled_over = false;
        
};

#endif