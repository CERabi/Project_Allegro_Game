#include "gamescreen.h"

void gamescreen(void) {
    while (player.health > 0) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        keyboard_update(&event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            // 적 생성
            if (key[ALLEGRO_KEY_Q]) spawn_enermy(1);
            if (key[ALLEGRO_KEY_W]) spawn_enermy(2);
            // 적 삭제
            if (key[ALLEGRO_KEY_E]) clear_summons(1);
            
            // 아군 생성
            if (key[ALLEGRO_KEY_A]) spawn_summon(11);
            if (key[ALLEGRO_KEY_S]) spawn_summon(12);
            // 아군 삭제
            if (key[ALLEGRO_KEY_D]) clear_summons(11);

            
            
            // 공격
            if (key[ALLEGRO_KEY_SPACE]) fire_bullet();

            // 본인 강화(상점)
            if (key[ALLEGRO_KEY_F]) player_enhance_dm();
            if (key[ALLEGRO_KEY_G]) player_enhance_sp();
        }

        if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == spawn_timer) {
            spawn_enermy(1);
        }

        if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == spawn_timer_boss) {
            spawn_enermy(2);
        }

        if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == timer) {
            move_player();
            move_bullets();
            move_summons();
            move_boss_bullets();
            check_collision();
            check_bullet_collision();
            check_player_collision();
            attack_boss();
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
            0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        al_draw_scaled_bitmap(HUD_score, 0, 0, al_get_bitmap_width(HUD_score), al_get_bitmap_height(HUD_score),
            50, 55, 40, 40, 0);
        al_draw_scaled_bitmap(HUD_money, 0, 0, al_get_bitmap_width(HUD_money), al_get_bitmap_height(HUD_money),
            50, 105, 40, 40, 0);
        al_draw_scaled_bitmap(HUD_speed, 0, 0, al_get_bitmap_width(HUD_speed), al_get_bitmap_height(HUD_speed),
            50, 210, 40, 40, 0);
        al_draw_scaled_bitmap(HUD_damage, 0, 0, al_get_bitmap_width(HUD_damage), al_get_bitmap_height(HUD_damage),
            140, 210, 40, 40, 0);

        
        int player_size = 80;
        if (invincible_timer > 0) {
            if ((invincible_timer / 15) % 2 == 0) {
                if (player.sees_left) {
                    al_draw_scaled_bitmap(player_img_l, 0, 0, al_get_bitmap_width(player_img_l), al_get_bitmap_height(player_img_l),
                        player.x - player_size / 2, player.y - player_size / 2, player_size, player_size, 0);
                }
                else {
                    al_draw_scaled_bitmap(player_img_r, 0, 0, al_get_bitmap_width(player_img_r), al_get_bitmap_height(player_img_r),
                        player.x - player_size / 2, player.y - player_size / 2, player_size, player_size, 0);
                }
            }
        }
        else {
            if (player.sees_left) {
                al_draw_scaled_bitmap(player_img_l, 0, 0, al_get_bitmap_width(player_img_l), al_get_bitmap_height(player_img_l),
                    player.x - player_size / 2, player.y - player_size / 2, player_size, player_size, 0);
            }
            else {
                al_draw_scaled_bitmap(player_img_r, 0, 0, al_get_bitmap_width(player_img_r), al_get_bitmap_height(player_img_r),
                    player.x - player_size / 2, player.y - player_size / 2, player_size, player_size, 0);
            }
        }

        int enemy_size = 100;

        for (int i = 0; i < MAX_KNIGHTS; i++) {
            if (enemies[i].active) {
                if (enemies[i].matched_enemy == -1 && enemies[i].x < player.x) {
                    al_draw_scaled_bitmap(enermy_img_r, 0, 0, al_get_bitmap_width(enermy_img_r), al_get_bitmap_height(enermy_img_r),
                        enemies[i].x - enemy_size / 2, enemies[i].y - enemy_size / 2, enemy_size, enemy_size, 0);
                }
                else if (enemies[i].matched_enemy == -1 && enemies[i].x >= player.x) {
                    al_draw_scaled_bitmap(enermy_img_l, 0, 0, al_get_bitmap_width(enermy_img_l), al_get_bitmap_height(enermy_img_l),
                        enemies[i].x - enemy_size / 2, enemies[i].y - enemy_size / 2, enemy_size, enemy_size, 0);
                }
                else if (enemies[i].x >= summons[enemies[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(enermy_img_l, 0, 0, al_get_bitmap_width(enermy_img_l), al_get_bitmap_height(enermy_img_l),
                        enemies[i].x - enemy_size / 2, enemies[i].y - enemy_size / 2, enemy_size, enemy_size, 0);
                }
                else {
                    al_draw_scaled_bitmap(enermy_img_r, 0, 0, al_get_bitmap_width(enermy_img_r), al_get_bitmap_height(enermy_img_r),
                        enemies[i].x - enemy_size / 2, enemies[i].y - enemy_size / 2, enemy_size, enemy_size, 0);
                }
            }
        }

        for (int i = MAX_KNIGHTS; i < MAX_ENEMIES; i++) {
            if (enemies[i].active) {
                if (enemies[i].matched_enemy == -1 && enemies[i].x < player.x) {
                    al_draw_scaled_bitmap(enemy_boss_img_r, 0, 0, al_get_bitmap_width(enemy_boss_img_r), al_get_bitmap_height(enemy_boss_img_r),
                        enemies[i].x - 50, enemies[i].y - 100, 200, 200, 0);
                }
                else if (enemies[i].matched_enemy == -1 && enemies[i].x >= player.x) {
                    al_draw_scaled_bitmap(enemy_boss_img_l, 0, 0, al_get_bitmap_width(enemy_boss_img_l), al_get_bitmap_height(enemy_boss_img_l),
                        enemies[i].x - 50, enemies[i].y - 100, 200, 200, 0);
                }
                else if (enemies[i].x >= summons[enemies[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(enemy_boss_img_l, 0, 0, al_get_bitmap_width(enemy_boss_img_l), al_get_bitmap_height(enemy_boss_img_l),
                        enemies[i].x - 50, enemies[i].y - 100, 200, 200, 0);
                }
                else {
                    al_draw_scaled_bitmap(enemy_boss_img_r, 0, 0, al_get_bitmap_width(enemy_boss_img_r), al_get_bitmap_height(enemy_boss_img_r),
                        enemies[i].x - 50, enemies[i].y - 100, 200, 200, 0);
                }
            }
        }
        int summon_size = 90;
        for (int i = 0; i < MAX_ZOMBIES; i++) {
            if (summons[i].active) {
                int closest_enemy = -1;
                float min_distance = SCREEN_WIDTH * SCREEN_HEIGHT;
                for (int j = 0; j < MAX_ENEMIES; j++) {
                    if (enemies[j].active && !enemies[j].matched) {
                        float dx = summons[i].x - enemies[j].x;
                        float dy = summons[i].y - enemies[j].y;
                        float distance = sqrt(dx * dx + dy * dy);
                        if (distance < min_distance) {
                            min_distance = distance;
                            closest_enemy = j;
                        }
                    }
                }
                if (summons[i].matched_enemy != -1 && summons[i].x < enemies[summons[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(summon_img_r, 0, 0, al_get_bitmap_width(summon_img_r), al_get_bitmap_height(summon_img_r),
                        summons[i].x - summon_size / 2, summons[i].y - summon_size / 2, summon_size, summon_size, 0);
                }
                else if (summons[i].matched_enemy != -1 && summons[i].x >= enemies[summons[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(summon_img_l, 0, 0, al_get_bitmap_width(summon_img_l), al_get_bitmap_height(summon_img_l),
                        summons[i].x - summon_size / 2, summons[i].y - summon_size / 2, summon_size, summon_size, 0);
                }
                else if (closest_enemy != -1 && summons[i].x < enemies[closest_enemy].x) {
                    al_draw_scaled_bitmap(summon_img_r, 0, 0, al_get_bitmap_width(summon_img_r), al_get_bitmap_height(summon_img_r),
                        summons[i].x - summon_size / 2, summons[i].y - summon_size / 2, summon_size, summon_size, 0);
                }
                else {
                    al_draw_scaled_bitmap(summon_img_l, 0, 0, al_get_bitmap_width(summon_img_l), al_get_bitmap_height(summon_img_l),
                        summons[i].x - summon_size / 2, summons[i].y - summon_size / 2, summon_size, summon_size, 0);
                }
            }
        }
        int summon_size1 = 120;
        for (int i = MAX_ZOMBIES; i < MAX_ZOMBIES+MAX_GOBLINS; i++) {
            if (summons[i].active) {
                int closest_enemy = -1;
                float min_distance = SCREEN_WIDTH * SCREEN_HEIGHT;
                for (int j = 0; j < MAX_ENEMIES; j++) {
                    if (enemies[j].active && !enemies[j].matched) {
                        float dx = summons[i].x - enemies[j].x;
                        float dy = summons[i].y - enemies[j].y;
                        float distance = sqrt(dx * dx + dy * dy);
                        if (distance < min_distance) {
                            min_distance = distance;
                            closest_enemy = j;
                        }
                    }
                }
                if (summons[i].matched_enemy != -1 && summons[i].x < enemies[summons[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(summon2_img_r, 0, 0, al_get_bitmap_width(summon2_img_r), al_get_bitmap_height(summon2_img_r),
                        summons[i].x - summon_size1/2, summons[i].y - summon_size1/2, summon_size1, summon_size1, 0);
                }
                else if (summons[i].matched_enemy != -1 && summons[i].x >= enemies[summons[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(summon2_img_l, 0, 0, al_get_bitmap_width(summon2_img_l), al_get_bitmap_height(summon2_img_l),
                        summons[i].x - summon_size1/2, summons[i].y - summon_size1/2, summon_size1, summon_size1, 0);
                }
                else if (closest_enemy != -1 && summons[i].x < enemies[closest_enemy].x) {
                    al_draw_scaled_bitmap(summon2_img_r, 0, 0, al_get_bitmap_width(summon2_img_r), al_get_bitmap_height(summon2_img_r),
                        summons[i].x - summon_size1/2, summons[i].y - summon_size1/2, summon_size1, summon_size1, 0);
                }
                else {
                    al_draw_scaled_bitmap(summon2_img_l, 0, 0, al_get_bitmap_width(summon2_img_l), al_get_bitmap_height(summon2_img_l),
                        summons[i].x - summon_size1/2, summons[i].y - summon_size1/2, summon_size1, summon_size1, 0);
                }
            }
        }

        int bullet_size = 80;
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                al_draw_scaled_bitmap(fireball_img, 0, 0, al_get_bitmap_width(fireball_img), al_get_bitmap_height(fireball_img),
                    bullets[i].x - bullet_size / 2, bullets[i].y - bullet_size / 2, bullet_size, bullet_size, 0);
            }
        }

        for (int j = 0; j < MAX_BOSSES; ++j) {
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (boss_bullets[j][i].active) {
                    al_draw_scaled_bitmap(fireball_boss_img, 0, 0, al_get_bitmap_width(fireball_boss_img), al_get_bitmap_height(fireball_boss_img),
                        boss_bullets[j][i].x - 35, boss_bullets[j][i].y - 35, 70, 70, 0);
                }
            }
        }
        hud_draw();
        al_flip_display();
    }
}