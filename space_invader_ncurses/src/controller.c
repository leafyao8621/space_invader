#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "controller.h"
#include "graphics.h"
#include "../../space_invader/space_invader.h"

WINDOW* w;
int x, y;


void initialize(void) {
    w = initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    getmaxyx(w, y, x);
    srand(time(0));
    _Bool xf, yf;
    xf = yf = 0;
    if (x > 100) {
        x = 100;
        xf = 1;
    }
    if (y > 100) {
        y = 100;
        yf = 0;
    }
    mvwhline(w, 1, 0, 0, x);
    init(x, y);
    mvwprintw(w, 0, 0, "Score:%4d", get_score());
    draw(2, 0, 0);
}

void main_loop(void) {
    nodelay(w, TRUE);
    int c;
    int rcnt = 0;
    int prev = 0;
    clock_t last = clock();
    while (!get_lost()) {
        c = getch();
        switch (c) {
        case KEY_UP:
        case 'W':
        case 'w':
            move_ship(-1);
            prev = 1;
            break;
        case KEY_DOWN:
        case 'S':
        case 's':
            move_ship(1);
            prev = -1;
            break;
        case ' ':
            fire(&ship);
            break;
        case 'Q':
        case 'q':
            return;
        }
        if (prev) {
            draw(ship.row + prev, ship.col, 2);
            draw(ship.row, ship.col, 0);
        }
        clock_t now = clock();
        if (now - last >= CLOCKS_PER_SEC / 10.0) {
            if (!(rcnt % 50)) {
                gen_enemy(rcnt);
            }
            proceed(rcnt);
            update(rcnt);
            now = clock();
            last = now;
            rcnt++;
        }
    }
}

void cleanup(void) {
    nodelay(w, FALSE);
    clear();
    mvwprintw(w, y >> 1, (x >> 1) - 4, "%s", "Game Over");
    mvwprintw(w, (y >> 1) + 1, (x >> 1) - 5, "Score:%4d", get_score());
    getch();
    endwin();
}