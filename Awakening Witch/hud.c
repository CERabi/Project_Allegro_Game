#include "hud.h"

// hud
void hud_init() {
	score_display = 0;
}

void hud_draw() {
	al_draw_scaled_bitmap(HUD_score, 0, 0, al_get_bitmap_width(HUD_score), al_get_bitmap_height(HUD_score),
		50, 55, 40, 40, 0);
	al_draw_scaled_bitmap(HUD_money, 0, 0, al_get_bitmap_width(HUD_money), al_get_bitmap_height(HUD_money),
		50, 105, 40, 40, 0);
	al_draw_scaled_bitmap(HUD_speed, 0, 0, al_get_bitmap_width(HUD_speed), al_get_bitmap_height(HUD_speed),
		50, 210, 40, 40, 0);
	al_draw_scaled_bitmap(HUD_damage, 0, 0, al_get_bitmap_width(HUD_damage), al_get_bitmap_height(HUD_damage),
		220, 210, 40, 40, 0);


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
	al_draw_textf(
		hud_font,
		al_map_rgb_f(1, 1, 1),
		270, 200,
		0,
		"%.1f",
		player.damage
	);
	if (player.player_att_delay <= 0.01) {
		al_draw_textf(
			hud_font,
			al_map_rgb_f(1, 1, 1),
			100, 200,
			0,
			"MAX"
		);
	}
	else {
		al_draw_textf(
			hud_font,
			al_map_rgb_f(1, 1, 1),
			100, 200,
			0,
			"%.2f",
			player.player_att_delay
		);
	}
	for (int i = 0; i < player.health; ++i) {
		al_draw_scaled_bitmap(HUD_life, 0, 0, al_get_bitmap_width(HUD_life), 
			al_get_bitmap_height(HUD_life), 50 + i * 50, 160, 40, 40, 0);
	}

	if (money_display >= 50) {
		al_draw_scaled_bitmap(SHOP_UP_ATT, 0, 0, al_get_bitmap_width(SHOP_UP_ATT),
			al_get_bitmap_height(SHOP_UP_ATT), 1295, 50, 55, 55, 0);
	}
	else {
		al_draw_scaled_bitmap(SHOP_UP_ATT_NO, 0, 0, al_get_bitmap_width(SHOP_UP_ATT_NO),
			al_get_bitmap_height(SHOP_UP_ATT_NO), 1295, 50, 55, 55, 0);
	}
	if (player.player_att_delay <= 0.01) {
		al_draw_scaled_bitmap(SHOP_UP_SPD_MAX, 0, 0, al_get_bitmap_width(SHOP_UP_SPD_MAX),
			al_get_bitmap_height(SHOP_UP_SPD_MAX), 1350, 50, 55, 55, 0);
	}
	else if (money_display >= 50) {
		al_draw_scaled_bitmap(SHOP_UP_SPD, 0, 0, al_get_bitmap_width(SHOP_UP_SPD),
			al_get_bitmap_height(SHOP_UP_SPD), 1350, 50, 55, 55, 0);
	}
	else {
		al_draw_scaled_bitmap(SHOP_UP_SPD_NO, 0, 0, al_get_bitmap_width(SHOP_UP_SPD_NO),
			al_get_bitmap_height(SHOP_UP_SPD_NO), 1350, 50, 55, 55, 0);
	}
}