#include <stdlib.h>
#include <string.h>
#include "space_invader.h"

struct Object ship, enemy[100], bullet[100], del[100], *enemy_end, *bullet_end, *del_end;

static int width, height, score;
static _Bool lost;

void init(int w, int h) {
    width = w;
    height = h;
    ship.row = 2;
    ship.col = 0;
    ship.dir = 1;
    enemy_end = enemy;
    bullet_end = bullet;
    del_end = del;
    score = 0;
    lost = 0;
}

void fire(struct Object* object) {
    bullet_end->row = object->row;
    bullet_end->col = object->col + object->dir * 3;
    bullet_end->dir = object->dir;
    bullet_end++;
}

void move_ship(int dir) {
    if (ship.row + dir >= 2 && ship.row + dir < height) {
        ship.row += dir;
    }
}

void gen_enemy(int rcnt) {
    enemy_end->row = rand() % (height - 2) + 2;
    enemy_end->col = width - 1;
    enemy_end->dir = -1;
    enemy_end->typ = 0;
    enemy_end++;
}

void proceed(int rcnt) {
    if (!(rcnt % 4)) {
        for (struct Object* i = enemy; i != enemy_end; i++) {
            i->col += i->dir;
            if (i->col == 1) {
                lost = 1;
                return;
            }
        }
    }
    for (struct Object* i = bullet; i != bullet_end; i++) {
        i->col += i->dir;
        if (i->dir == 1) {
            for (struct Object* j = enemy; j != enemy_end; j++) {
                if (j->row == i->row && j->col - i->col <= 1) {
                    score++;
                    bullet_end--;
                    *(del_end++) = *i;
                    memmove(i, i + 1, 99);
                    enemy_end--;
                    *(del_end++) = *j;
                    memmove(j, j + 1, 99);
                }
            }
        }
        if (i->col == width - 1) {
            bullet_end--;
            *(del_end++) = *i;
            memmove(i, i + 1, 99);
        }
        if (i == bullet_end) break;
    }
    
}

int get_score(void) {
    return score;
}

void reset_del(void) {
    del_end = del;
}

_Bool get_lost(void) {
    return lost;
}