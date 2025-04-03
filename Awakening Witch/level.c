#include "level.h"

void level_up(void) {
	rand() % 20;
	while(1) {
		hud_draw();
		al_draw_text(title_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 220, ALLEGRO_ALIGN_CENTER, "Select new debuff");
		al_flip_display();
	}
}