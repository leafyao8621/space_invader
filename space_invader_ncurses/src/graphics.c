#include <stdio.h>
#include "graphics.h"
#include "controller.h"
#include "../../space_invader/space_invader.h"

static const char* icon[] = {">-", "-<", "  "};
static const char* bul[] = {"-<", "   ", ">-"};
static const char** bull = bul + 1;

void draw(int row, int col, int t) {
    mvwprintw(w, row, col, "%s", icon[t]);
}

static void log_msg(char* msg) {
    FILE* fout = fopen(".log", "a");
    fprintf(fout, "%s", msg);
    fclose(fout);
}

void update(int rcnt) {
    mvwprintw(w, 0, 0, "Score:%4d", get_score());
    if (!(rcnt % 4)) {
        for (struct Object* i = enemy; i != enemy_end; i++) {
            mvwprintw(w, i->row, i->col - i->dir, "%s", *bull);
            mvwprintw(w, i->row, i->col, "%s", bull[i->dir]);
        }
    }
    for (struct Object* i = bullet; i != bullet_end; i++) {
        mvwprintw(w, i->row, i->col - i->dir, "%s", *bull);
        mvwprintw(w, i->row, i->col, "%s", bull[i->dir]);
    }
    
    for (struct Object* i = del; i != del_end; i++) {
        mvwprintw(w, i->row, i->col - i->dir, "%s", *bull);
    }
    reset_del();
}