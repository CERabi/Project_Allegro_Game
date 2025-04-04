#ifndef RES_H
#define RES_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h >
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>


#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 900
#define PLAYER_SPEED 5
#define ENEMY_SPEED 1.5f
#define SUMMON_SPEED 1.7f
#define MAX_KNIGHTS 5
#define MAX_BOSSES 3
#define MAX_BATS 5
#define MAX_ZOMBIES 5
#define MAX_GOBLINS 5
#define MAX_BULLETS 10
#define MAX_PLAYER_BULLETS 10
#define COLLISION_DISTANCE 50
#define BULLET_COLLISION_DISTANCE 30
#define BULLET_DAMAGE 1
#define ENERMY_DAMAGE 1
#define ENEMY_HEALTH 3
#define PLAYER_HEALTH 5
#define BULLET_SPEED 7
#define ATTACK_DELAY 0.5
#define FRAME_COUNT 3
#define FRAME_DELAY 0.2
#define KNIGHT_MAX_HEALTH 3.0f
#define BOSS_MAX_HEALTH 10.0f
#define BAT_MAX_HEALTH 2.0f
#define ZOMBIE_MAX_HEALTH 6.0f
#define GOBLIN_MAX_HEALTH 10.0f
#define COST_ATT 300
#define COST_SPD 100
#define COST_BU 500
#define COST_BAT 200
#define COST_ZOMBIE 300
#define COST_GOBLIN 400


ALLEGRO_BITMAP* background;
ALLEGRO_BITMAP* summon_img_l;
ALLEGRO_BITMAP* summon_img_r;
ALLEGRO_BITMAP* summon2_img_l;
ALLEGRO_BITMAP* summon2_img_r;
ALLEGRO_BITMAP* summon3_img_r;
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
ALLEGRO_BITMAP* HUD_speed;
ALLEGRO_BITMAP* HUD_damage;
ALLEGRO_BITMAP* HUD_bullets;
ALLEGRO_BITMAP* SHOP_ORIGIN;
ALLEGRO_BITMAP* SHOP_UP_ATT;
ALLEGRO_BITMAP* SHOP_UP_ATT_NO;
ALLEGRO_BITMAP* SHOP_UP_SPD;
ALLEGRO_BITMAP* SHOP_UP_SPD_NO;
ALLEGRO_BITMAP* SHOP_UP_SPD_MAX;
ALLEGRO_BITMAP* SHOP_UP_BU;
ALLEGRO_BITMAP* SHOP_UP_BU_NO;
ALLEGRO_BITMAP* SHOP_UP_BU_MAX;
ALLEGRO_BITMAP* SHOP_UP_BAT;
ALLEGRO_BITMAP* SHOP_UP_ZOMBIE;
ALLEGRO_BITMAP* SHOP_UP_GOBLIN;
ALLEGRO_BITMAP* SHOP_UP_X;

//ALLEGRO_BITMAP* SHOP_FRIENDLY;

ALLEGRO_BITMAP* goblin_sword[FRAME_COUNT];
ALLEGRO_BITMAP* bat_sword[FRAME_COUNT];
ALLEGRO_BITMAP* zombie_sword[FRAME_COUNT];
ALLEGRO_BITMAP* knight_sword[FRAME_COUNT];


ALLEGRO_EVENT_QUEUE* event_queue;

ALLEGRO_DISPLAY* display;

ALLEGRO_TIMER* timer;
ALLEGRO_TIMER* spawn_timer;
ALLEGRO_TIMER* spawn_timer_boss;

ALLEGRO_FONT* font;
ALLEGRO_FONT* title_font;
ALLEGRO_FONT* button_font;
ALLEGRO_FONT* hud_font;

ALLEGRO_SAMPLE* BGM;
ALLEGRO_SAMPLE* monster_hit;
ALLEGRO_SAMPLE* player_attack;
ALLEGRO_SAMPLE* boss_summon;


float player_x;
float player_y;
float player_size; 
int player_health;
int invincible_timer;
double last_att;
char state[20];
long score_display;
int money_display;
int boss_shoot_timer[MAX_BOSSES];
int boss_attack_delay;
int MAX_SUMMONS;
int MAX_ENEMIES;

int current_frame[MAX_ZOMBIES + MAX_GOBLINS + MAX_BATS];
double last_update_time[MAX_ZOMBIES + MAX_GOBLINS + MAX_BATS];
double current_time[MAX_ZOMBIES + MAX_GOBLINS + MAX_BATS];

int current_enemies_frame[MAX_KNIGHTS];
double last_update_enemies_time[MAX_KNIGHTS];
double current_enemies_time[MAX_KNIGHTS];



void load_resource(void);
void destroy_resource(void); 
ALLEGRO_BITMAP* convert_to_grayscale(ALLEGRO_BITMAP* original);
#endif