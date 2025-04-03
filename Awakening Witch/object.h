#ifndef OBJ_H
#define OBJ_H
#include <allegro5/allegro_image.h>
#include <math.h>

#include "resource.h"
#include "keyboard.h"
#include "menu.h"

typedef struct Player {
    float x, y;
    int speed;
    double player_att_delay;
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
    int damage;
    int credit;
    int score;
    int size;
    double speed;
    int invincible; // 몬스터 소환수 무적 시간
} Summon;

typedef struct Bullet {
    float x, y;
    bool active;
    float direction_x, direction_y;
} Bullet;

Player player;
Summon enemies[MAX_KNIGHTS+MAX_BOSSES];
Summon summons[MAX_ZOMBIES+MAX_GOBLINS];
Bullet bullets[MAX_BULLETS];
Bullet boss_bullets[MAX_BOSSES][MAX_BULLETS];

void move_player();
void player_enhance_sp(void);
void player_enhance_dm(void);
void fire_bullet();
void boss_shoot(int);
void move_summons();
void move_bullets();
void move_boss_bullets(void);
void attack_boss(void);
void spawn_summon(int);
void spawn_enermy(int);
void clear_summons(int);
void check_collision(); 
void check_bullet_collision();
void check_player_collision();
#endif