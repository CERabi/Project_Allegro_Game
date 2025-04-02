#ifndef RES_H
#define RES_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 900
#define PLAYER_SPEED 5
#define ENEMY_SPEED 1.5f
#define SUMMON_SPEED 1.7f
#define MAX_ENEMIES 5
#define MAX_SUMMONS 5
#define MAX_BULLETS 10
#define COLLISION_DISTANCE 50
#define BULLET_DAMAGE 1
#define ENERMY_DAMAGE 1
#define ENEMY_HEALTH 3
#define PLAYER_HEALTH 5
#define BULLET_SPEED 7
#define ATTACK_DELAY 0.5

ALLEGRO_BITMAP* background;
ALLEGRO_BITMAP* summon_img_l;
ALLEGRO_BITMAP* summon_img_r;
ALLEGRO_BITMAP* enermy_img_l;
ALLEGRO_BITMAP* enermy_img_r;
ALLEGRO_BITMAP* enemy_boss_img_l;
ALLEGRO_BITMAP* enemy_boss_img_r;
ALLEGRO_BITMAP* player_img_l;
ALLEGRO_BITMAP* player_img_r;
ALLEGRO_BITMAP* fireball_img;
ALLEGRO_BITMAP* fireball_boss_img;
ALLEGRO_BITMAP* HUD_score;
ALLEGRO_BITMAP* HUD_money;
ALLEGRO_BITMAP* HUD_life;


ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_DISPLAY* display;
ALLEGRO_TIMER* timer;
ALLEGRO_TIMER* spawn_timer;
ALLEGRO_FONT* font;
ALLEGRO_FONT* title_font;
ALLEGRO_FONT* button_font;
ALLEGRO_FONT* hud_font;

float player_x;
float player_y;
float player_size; 
int player_health;
int invincible_timer;
double last_att;
char state[20];
long score_display;
int money_display;
int boss_shoot_timer[MAX_ENEMIES];
int boss_attack_delay;

void load_resource(void);
void destroy_resource(void);
#endif