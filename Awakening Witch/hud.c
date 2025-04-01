#include "hud.h"

// hud
void hud_init() {
    score_display = 0;
}

void hud_draw() {
    al_draw_textf(
        hud_font,
        al_map_rgb_f(1, 1, 1),
        100, 50,
        0,
        "%06ld",
        score_display
    );
    al_draw_textf(
        hud_font,
        al_map_rgb_f(1, 1, 1),
        100, 100,
        0,
        "%06ld",
        money_display
    );
}