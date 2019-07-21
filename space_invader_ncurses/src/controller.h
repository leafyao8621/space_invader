#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <ncurses.h>

extern WINDOW* w;
extern int x, y;
void initialize(void);
void main_loop(void);
void cleanup(void);
#endif