#include "entities_npc.hpp"

Village_questgiver_1::Village_questgiver_1()
{
    pos = VILLAGE_QUESTGIVER_1_POS;
    current_animation_frame = 0;
    current_animation_arr = village_questgiver_idle;
    rect = {pos.x+VILLAGE_QUESTGIVER_1_HITBOX_OFFSET_X, pos.y+VILLAGE_QUESTGIVER_1_HITBOX_OFFSET_Y, VILLAGE_QUESTGIVER_1_HITBOX_WIDTH, VILLAGE_QUESTGIVER_1_HITBOX_HEIGHT};
    interact_rect = {pos.x+22, pos.y+45, 19, 15};
    add_collisions({rect});
}

Village_questgiver_1::~Village_questgiver_1()
{
    if(tex.id != 0){
        UnloadTexture(tex);
    }
}

void Village_questgiver_1::load()
{
    tex = get_texture(VILLAGE_QUESTGIVER_1_PATH);
}

void Village_questgiver_1::update()
{
    if(IsKeyPressed(KEY_INTERACT) && CheckCollisionRecs(interact_rect, player.collision_rect) && !gui.global_textbox.is_textbox_open){
        if(!is_text_finished(VILLAGE_QUESTGIVER_1_FOUND_ITEM_TEXT)){
            for (int i = 0; i < 28; i++) {
                if (inventory_slots[i].filled_with->name== Item_names::SACRED_BARK) {
                    found_wanted_item = true;
                    break;
                };
            };
        }
        if(!is_text_finished(VILLAGE_QUESTGIVER_1_STORY_TEXT)){
            set_textbox_indice_text(0, {"Well, well, well.", NONE});
            set_textbox_indice_text(1, {"Now look what they did.", NONE});
            set_textbox_indice_text(2, {"Ruining our ground, and their reputation.", NONE});
            set_textbox_indice_text(3, {"They claimed to have possible accidents under control, but I still believe it's stupid to put a bulldozer factory in the sky.", NONE});
            set_textbox_indice_text(4, {"Like, how do they get them down from there?", NONE});
            set_textbox_indice_text(5, {"I guess . . . they found one way.", NONE});
            set_textbox_indice_text(6, {"Anyways, who are you?", NONE});
            set_textbox_indice_text(7, {"Ah, I see, the Chosen.", NONE});
            set_textbox_indice_text(8, {"Well, I don't see anything changing, even with you, but I could help you out.", NONE});
            set_textbox_indice_text(9, {"See, there is this gigantic tree, used to be the base of some group.", NONE});
            set_textbox_indice_text(10, {"I said used to because it was recently taken over by the Regrown.", NONE});
            set_textbox_indice_text(11, {"'What's that', ah, I'll tell you what, once you kill it.", NONE});
            set_textbox_indice_text(12, {"You're going to need to go into the Dark Forest just south of here and bring back some sort of proof that you did away with that thing.", NONE});
            set_textbox_indice_text(13, {"'What do I need', oh, I just need a little bit of bark from the tree, found only at the very top . . .", NONE});
            setup_textbox(14, VILLAGE_QUESTGIVER_1);
            add_finished_text(VILLAGE_QUESTGIVER_1_STORY_TEXT);
            //TODO: figure out what this guy is actually going to say
        }
        else if(is_text_finished(VILLAGE_QUESTGIVER_1_STORY_TEXT) && !found_wanted_item){
            set_textbox_indice_text(0, {"Now, what are you waiting for! Get a move on!", NONE});
            set_textbox_indice_text(1, {"I don't have all day! (or do I?)", NONE});
            setup_textbox(2, VILLAGE_QUESTGIVER_1);
        }
        
        else if(is_text_finished(VILLAGE_QUESTGIVER_1_STORY_TEXT) && !is_text_finished(VILLAGE_QUESTGIVER_1_FOUND_ITEM_TEXT) && found_wanted_item){
            set_textbox_indice_text(0, {"Oh! I wasn't expecting you to have actually done that! I guess my initial judgement of you was a bit harsh . . .", NONE});
            set_textbox_indice_text(1, {"Good job, in fact, you can keep that piece of bark, I just wanted that Regrown dead.", NONE});
            set_textbox_indice_text(2, {"Ah! You want to learn more about the Regrown? I'll tell you then!", NONE});
            set_textbox_indice_text(3, {"It is an evil tree spirit, mentally connected to every single Forest Scourge everywhere. At all times.", NONE});
            set_textbox_indice_text(4, {"You don't even know what a Forest Scourge is? I won't go too in-depth with them, just know that those little guys with the spears are what I'm talking about.", NONE});
            set_textbox_indice_text(5, {"But essentially, the Regrown controls them all, and by killing it, you have given them a taste of Freedom.", NONE});
            set_textbox_indice_text(6, {"Which could be good, as they could join our side, but who knows.", NONE});
            set_textbox_indice_text(7, {"Anyways, I've been talking too long, you had better be on your way, go do something!", NONE}); //right here make ties to other people in the village once the demo's out
            setup_textbox(8, VILLAGE_QUESTGIVER_1);
            add_finished_text(VILLAGE_QUESTGIVER_1_FOUND_ITEM_TEXT);
        }
        else{
            set_textbox_indice_text(0, {"Well, thanks for helping, but you're going to need to do more than just that to 'save the world'", NONE});
            set_textbox_indice_text(1, {"Go find someone in need of help, I'm sure you can. It's not perfect around here.", NONE});
            setup_textbox(2, VILLAGE_QUESTGIVER_1);
        }
        
    }
    
}

void Village_questgiver_1::draw()
{
    DrawTexturePro(tex, current_animation_arr[current_animation_frame], {pos.x, pos.y, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT}, {0, 0}, 0, WHITE);
}