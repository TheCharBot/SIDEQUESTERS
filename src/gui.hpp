#ifndef GUI_HPP
#define GUI_HPP


#include "player.hpp"
#include "items.hpp"

extern void init_gui();
extern void inv_cursor_init();
extern void inv_cursor_update();
extern void health_bar_draw();
extern void update_gui();
extern void draw_gui();

#endif