#ifndef ENTITIES_NPC_HPP
#define ENTITIES_NPC_HPP


#include "player.hpp"

class Village_questgiver_1 : public Entity{
    public:
        Village_questgiver_1();
        ~Village_questgiver_1() override;
        
        

        


        void load() override;
        void update() override;
        void draw() override;

    private:
        Rectangle *current_animation_arr = {};
        Rectangle interact_rect = {};
        Texture2D tex{};
        bool story_text_done = false;
        bool found_wanted_item = false;
        bool found_item_text_done = false;
};

#endif