#ifndef OBJ_H
#define OBJ_H
#include <allegro5/allegro_image.h>
#include <math.h>

#include "resource.h"
#include "keyboard.h"

typedef struct Player {
    float x, y;
    int speed;
    int damage;
    int health;
    bool sees_left;
} Player;

typedef struct Summon {
    float x, y;
    bool active;
    bool matched;
    int number;
    int matched_enemy;
    int health;
    int invincible; // 몬스터 소환수 무적 시간
} Summon;

typedef struct Bullet {
    float x, y;
    bool active;
    float direction_x, direction_y;
} Bullet;

Player player;
Summon enemies[MAX_ENEMIES];
Summon enemies_boss[MAX_ENEMIES];
Summon summons[MAX_SUMMONS];
Bullet bullets[MAX_BULLETS];

void move_player();
void fire_bullet();
void move_summons();
void move_bullets();
void spawn_player(void);
void spawn_summon(int);
void spawn_enermy(int);
void clear_summons(int);
void check_collision(); 
void check_bullet_collision();
void check_player_collision();
#endif