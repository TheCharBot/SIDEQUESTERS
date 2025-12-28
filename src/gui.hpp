#ifndef GUI_HPP
#define GUI_HPP

#include "config.hpp"

#include "player.hpp"
#include "assets.hpp"
#include "items.hpp"

extern void gui_init();
extern void inv_cursor_init();
extern void inv_cursor_update();
extern void gui_update();
extern void gui_draw();

#endif