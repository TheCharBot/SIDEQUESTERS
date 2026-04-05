#include "entities_npc.hpp"

NPC_Dan_Village::NPC_Dan_Village()
{
    pos = VILLAGE_QUESTGIVER_1_POS;
    current_animation_frame = 0;
    current_animation_arr = NPC_dan_village_idle;
    rect = {pos.x+DEFAULT_NPC_COLLISION_BOX_OFFSET_X, pos.y+DEFAULT_NPC_COLLISION_BOX_OFFSET_Y, DEFAULT_NPC_COLLISION_BOX_WIDTH, DEFAULT_NPC_COLLISION_BOX_WIDTH};
    interact_rect = {pos.x+DEFAULT_NPC_DOWN_INTERACT_RECT_OFFSET_X, pos.y+DEFAULT_NPC_DOWN_INTERACT_RECT_OFFSET_Y, DEFAULT_NPC_DOWN_INTERACT_RECT_WIDTH, DEFAULT_NPC_DOWN_INTERACT_RECT_HEIGHT};
    add_collisions({rect});
}

NPC_Dan_Village::~NPC_Dan_Village()
{
    if(tex.id != 0){
        UnloadTexture(tex);
    }
}

void NPC_Dan_Village::load()
{
    tex = get_texture(NPC_DAN_VILLAGE_TEX_PATH);
}

void NPC_Dan_Village::update()
{
    if(IsKeyPressed(KEY_INTERACT) && CheckCollisionRecs(interact_rect, player.collision_rect) && !gui.global_textbox.is_textbox_open){
        if(!is_text_finished(NPC_DAN_VILLAGE_FOUND_ITEM_TEXT)){
            for (int i = 0; i < 28; i++) {
                if (inventory_slots[i].filled_with->name== Item_names::SACRED_BARK) {
                    found_wanted_item = true;
                    break;
                };
            };
        }
        if(!is_text_finished(NPC_DAN_VILLAGE_STORY_TEXT)){
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
            setup_textbox(14, Entity_names::NPC_DAN_VILLAGE);
            add_finished_text(NPC_DAN_VILLAGE_STORY_TEXT);
            //TODO: figure out what this guy is actually going to say
            
        }
        else if(is_text_finished(NPC_DAN_VILLAGE_STORY_TEXT) && !found_wanted_item){
            set_textbox_indice_text(0, {"Now, what are you waiting for! Get a move on!", NONE});
            set_textbox_indice_text(1, {"I don't have all day! (or do I?)", NONE});
            setup_textbox(2, Entity_names::NPC_DAN_VILLAGE);
        }
        
        else if(is_text_finished(NPC_DAN_VILLAGE_STORY_TEXT) && !is_text_finished(NPC_DAN_VILLAGE_FOUND_ITEM_TEXT) && found_wanted_item){
            set_textbox_indice_text(0, {"Oh! I wasn't expecting you to have actually done that! I guess my initial judgement of you was a bit harsh . . .", NONE});
            set_textbox_indice_text(1, {"Good job, in fact, you can keep that piece of bark, I just wanted that Regrown dead.", NONE});
            set_textbox_indice_text(2, {"Ah! You want to learn more about the Regrown? I'll tell you then.", NONE});
            set_textbox_indice_text(3, {"It is an evil tree spirit, mentally connected to every single Forest Scourge everywhere. At all times.", NONE});
            set_textbox_indice_text(4, {"You don't even know what a Forest Scourge is? I won't go too in-depth with them, just know that those little guys with the spears are what I'm talking about.", NONE});
            set_textbox_indice_text(5, {"But essentially, the Regrown controls them all, and that is probably the only thing it is good at.", NONE});
            set_textbox_indice_text(6, {"Also, It is so good at making the Forest Scourges behave naturally, they haven't even noticed yet.", NONE});
            set_textbox_indice_text(7, {"Anyways, I've been talking too long, you had better be on your way, go do something!", NONE}); //right here make ties to other people in the village once the demo's out
            setup_textbox(8, Entity_names::NPC_DAN_VILLAGE);
            add_finished_text(NPC_DAN_VILLAGE_FOUND_ITEM_TEXT);
        }
        else{
            set_textbox_indice_text(0, {"Well, thanks for helping, but you're going to need to do more than just that to 'save the world'", NONE});
            set_textbox_indice_text(1, {"Go find someone in need of help, I'm sure you can. It's not perfect around here.", NONE});
            setup_textbox(2, Entity_names::NPC_DAN_VILLAGE);
        }
        
    }
    
}

void NPC_Dan_Village::draw()
{
    DrawTexturePro(tex, current_animation_arr[current_animation_frame], {pos.x, pos.y, DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT}, {0, 0}, 0, WHITE);
}

NPC_Bob_Village::NPC_Bob_Village()
{ //TODO: MACROS
    pos = {516, 69};
    current_animation_arr = NPC_bob_village_idle;
    current_animation_frame = 0;
    animation_frame_5 = 0;
    max_animation_frames = 4;
    rect = {pos.x+DEFAULT_NPC_COLLISION_BOX_OFFSET_X, pos.y+DEFAULT_NPC_COLLISION_BOX_OFFSET_Y, DEFAULT_NPC_COLLISION_BOX_WIDTH, DEFAULT_NPC_COLLISION_BOX_WIDTH};
    interact_rect = {pos.x+DEFAULT_NPC_DOWN_INTERACT_RECT_OFFSET_X, pos.y+DEFAULT_NPC_DOWN_INTERACT_RECT_OFFSET_Y, DEFAULT_NPC_DOWN_INTERACT_RECT_WIDTH, DEFAULT_NPC_DOWN_INTERACT_RECT_HEIGHT};
    add_collisions({rect});
}

NPC_Bob_Village::~NPC_Bob_Village()
{
}

void NPC_Bob_Village::load()
{
    tex = get_texture(NPC_BOB_VILLAGE_TEX_PATH);
}

void NPC_Bob_Village::update()
{
    if(IsKeyPressed(KEY_INTERACT) && CheckCollisionRecs(interact_rect, player.collision_rect) && !gui.global_textbox.is_textbox_open){
        if(!is_text_finished(NPC_BOB_STORY_TEXT)){
            set_textbox_indice_text(0, {"Hey you! You like trees?", NONE});
            set_textbox_indice_text(1, {"I really do, especially cutting them down and making things!", NONE});
            set_textbox_indice_text(2, {"Whenever I cut them down, I turn my back for one second, and there they are, as good as new!", NONE});
            set_textbox_indice_text(3, {"I'm interested to find out what that means, but in the meantime, Infinite Wood!", NONE});
            set_textbox_indice_text(4, {"Although, every once in a while, normally around when a new Chosen is chosen, they stop growing for a little bit.", NONE});
            set_textbox_indice_text(5, {"It's as if they're waiting for something to change, as if they don't like their seemingly infinite cycle of regrowth.", NONE});
            set_textbox_indice_text(6, {"Anyway, enough 'bout me, tell me about yourself.", NONE});
            set_textbox_indice_text(7, {"Oh, I see, You're the new Chosen. I guess that makes sense.", NONE});
            set_textbox_indice_text(8, {"Well, see ya 'round, and remember; I can help you here, I pretty much built this entire Village, so I could get you out of a bad spot here and there.", NONE});
            // set_textbox_indice_text(0, {"W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W", NONE});
            // set_textbox_indice_text(1, {"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", NONE});
            // set_textbox_indice_text(2, {"M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M M", NONE});
            // set_textbox_indice_text(3, {"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM", NONE}); //hehe testing stuff
            add_finished_text(NPC_BOB_STORY_TEXT);
            setup_textbox(9, NPC_BOB_VILLAGE);
        }
        else if(is_text_finished(NPC_BOB_STORY_TEXT)){
            set_textbox_indice_text(0, {"Well, I've got to wait here till the dang trees start to grow again", NONE});
            set_textbox_indice_text(1, {"Thanks for that.", NONE});
            set_textbox_indice_text(2, {"Maybe you could help me later . . . \n\nmaybe", NONE});
            setup_textbox(3, NPC_BOB_VILLAGE);
        }
    }
    animation_frame_5++;
    
    if (animation_frame_5 >= ANIMATION_INTERVAL*3)
    {
        current_animation_frame++;
        if (current_animation_frame >= max_animation_frames)
        {
            current_animation_frame = 0;
        }
        animation_frame_5 = 0;
    }
}

void NPC_Bob_Village::draw()
{
    DrawTextureRec(tex, current_animation_arr[current_animation_frame], pos, WHITE);
}

NPC_Clarence_Village::NPC_Clarence_Village()
{
    pos = {105, 26};
    current_animation_arr = NPC_clarence_village_idle;
    current_animation_frame = 0;
    animation_frame_5 = 0;
    max_animation_frames = 2; //TODO: MACROS
    rect = {pos.x+1, pos.y+38, 65, 39};
    interact_rect = {pos.x+14, pos.y+78, 54, 9};
    add_collisions({rect});
}

NPC_Clarence_Village::~NPC_Clarence_Village()
{
}

void NPC_Clarence_Village::load()
{
    tex = LoadTexture(NPC_CLARENCE_VILLAGE_TEX_PATH);
}

void NPC_Clarence_Village::update()
{
    if(IsKeyPressed(KEY_INTERACT) && CheckCollisionRecs(interact_rect, player.collision_rect) && !gui.global_textbox.is_textbox_open){
        if(!is_text_finished(NPC_CLARENCE_STORY_TEXT)){
            set_textbox_indice_text(0, {"What do you want?", NONE});
            set_textbox_indice_text(1, {"Can't you see I'm working?!", NONE});
            set_textbox_indice_text(2, {"Never come in like that again!", NONE});
            set_textbox_indice_text(3, {"It's already been predicted if you do . . .", NONE});
            set_textbox_indice_text(4, {"Fine. I'm sorry, I just got to a very important part in this old book", NONE});
            set_textbox_indice_text(5, {"I'm trying to learn everything there is to know, starting with before the Loop", NONE});
            set_textbox_indice_text(6, {"You wanna learn more about why you're here?", NONE});
            set_textbox_indice_text(7, {"Well, a long time ago, some idiots put some magnets together and stopped time, killing themselves in the process somehow.", NONE});
            set_textbox_indice_text(8, {"That's why there is a Time Loop, then the magic imbued in this world took a hold of the magnetic feild and created Similarity, an incredible force of evil.", NONE});
            set_textbox_indice_text(9, {"With the magnet's help, Similarity ravanged the lands, converting many to their goal of 'keeping the land perfect.'", NONE});
            set_textbox_indice_text(10, {"So, the few of us who still believed in change pooled together many forms of magic and created Difference, another strong force.", NONE});
            set_textbox_indice_text(11, {"You, as you should know, are fighting for difference, and so you must never repeat yourself in your actions.", NONE});
            set_textbox_indice_text(12, {"On top of that, try to help as many people out as possible.", NONE});
            set_textbox_indice_text(13, {"If you want, go talk to my friend Chad over in the house on the other side of the windmill. He knows more about the way all of it works", NONE});
            set_textbox_indice_text(14, {"I help him with some of his experiments, teaching him about how one type of magic interacts with another.", NONE});
            set_textbox_indice_text(15, {"Alright, glad you could say hi, but you've been too long, you must DO something now! Get yourself out there! GO!", NONE});
            add_finished_text(NPC_CLARENCE_STORY_TEXT);
            setup_textbox(16, NPC_CLARENCE_VILLAGE);
        }
        else if(is_text_finished(NPC_CLARENCE_STORY_TEXT)){
            set_textbox_indice_text(0, {"GO! GO! GO! YOU'RE WASTING TIME! GO TALK TO SOMEONE! HELP SOMEONE! KILL SOMETHING! JUST GO HAVE FUN AND MESS UP!!!!", NONE});
            setup_textbox(1, NPC_CLARENCE_VILLAGE);
        }
    }
    animation_frame_5++;
    
    if (animation_frame_5 >= ANIMATION_INTERVAL*10)
    {
        current_animation_frame++;
        if (current_animation_frame >= max_animation_frames)
        {
            current_animation_frame = 0;
        }
        animation_frame_5 = 0;
    }
}

void NPC_Clarence_Village::draw()
{
    DrawTextureRec(tex, current_animation_arr[current_animation_frame], pos, WHITE);
}
