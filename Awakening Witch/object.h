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
    double damage;
    int health;
    int bullets;
    bool sees_left;
} Player;

typedef struct Summon {
    float x, y;
    bool active;
    bool matched;
    int number;
    int matched_enemy;
    double health;
    int damage;
    int credit;
    int score;
    int size;
    double speed;
    int invincible;
} Summon;

typedef struct Bullet {
	float x, y;
	bool active;
	float direction_x, direction_y;
} Bullet;

Player player;
Summon enemies[MAX_KNIGHTS + MAX_BOSSES];
Summon summons[MAX_ZOMBIES + MAX_GOBLINS + MAX_BATS];
Bullet bullets[MAX_PLAYER_BULLETS];
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
void Special_moves(int);
void check_collision();
void check_bullet_collision();
void check_boss_bullet_collision(void);
void check_player_collision();
void update_animation();
void update_animation2();
#endif