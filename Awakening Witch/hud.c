#include "hud.h"
#include "object.h"
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

	for (int i = 0; i < player.health; ++i) {
		al_draw_scaled_bitmap(HUD_life, 0, 0, al_get_bitmap_width(HUD_life), al_get_bitmap_height(HUD_life),
			50 + i * 50, 160, 40, 40, 0);
	}


}