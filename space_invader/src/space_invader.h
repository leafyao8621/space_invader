#ifndef _SPACE_INVADER_H_
#define _SPACE_INVADER_H_

struct Object {
    unsigned row : 8;
    unsigned col : 8;
    int dir : 8;
    unsigned typ : 8;
};

extern struct Object ship, enemy[100], bullet[100], del[100], *enemy_end, *bullet_end, *del_end;
void init(int w, int h);
void move_ship(int dir);
void fire(struct Object* object);
void gen_enemy(int rcnt);
void proceed(int rcnt);
int get_score(void);
_Bool get_lost(void);
void reset_del(void);
#endif