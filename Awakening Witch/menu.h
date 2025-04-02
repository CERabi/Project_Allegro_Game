#ifndef MENU_H
#define MENU_H
#define _CRT_SECURE_NO_WARNINGS
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "resource.h"

#define MAX_RANKS 5  // ���� 5�� ǥ��

typedef struct {
    char name[20];
    int score;
} Player1;


void draw_menu(void);
bool is_button_clicked(int mouse_x, int mouse_y, int button_y_offset);
void show_rankings(ALLEGRO_FONT* font);
void exit_game();
void draw_rankings(ALLEGRO_FONT* font, ALLEGRO_BITMAP* background);
int read_rankings(Player1 players[], int max_players);
int compare_players(const void* a, const void* b);
void rank(void);
void name(ALLEGRO_FONT*);
void save_score(const char*, long);
#endif
