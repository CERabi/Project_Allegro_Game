#include "object.h"

void move_player() {
	if (key[ALLEGRO_KEY_UP]) {
		player.y -= player.speed;
		player_direction = UP;
	}
	if (key[ALLEGRO_KEY_DOWN]) {
		player.y += player.speed;
		player_direction = DOWN;
	}
	if (key[ALLEGRO_KEY_LEFT]) {
		player.x -= player.speed;
		player_direction = LEFT;
		player.sees_left = true;
	}
	if (key[ALLEGRO_KEY_RIGHT]) {
		player.x += player.speed;
		player_direction = RIGHT;
		player.sees_left = false;
	}
	if (player.x < 100)
		player.x = 100;
	if (player.y < 230)
		player.y = 230;
	if (player.x > SCREEN_WIDTH - 100)
		player.x = SCREEN_WIDTH - 100;
	if (player.y > SCREEN_HEIGHT - 100)
		player.y = SCREEN_HEIGHT - 100;
}

void player_enhance_bu() {
    if (money_display < COST_ATT || player.bullets >= MAX_PLAYER_BULLETS) return;
    player.bullets += 1;
    money_display -= COST_ATT;
}

void player_enhance_sp() {
    if (money_display < COST_SPD || player.player_att_delay <= 0.01) return;
    player.player_att_delay -= 0.01;
    money_display -= COST_SPD;
}

void player_enhance_dm() {
    if (money_display < COST_BU) return;
    player.damage += 0.1;
    money_display -= COST_BU;
}

void fire_bullet() {
    double now = al_get_time();
    for (int i = 0; i < player.bullets; i++) {
        if (!bullets[i].active && now - last_att > player.player_att_delay) {
            al_play_sample(player_attack, 0.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            last_att = now;
            bullets[i].x = player.x;
            bullets[i].y = player.y;
            bullets[i].active = true;

            if (key[ALLEGRO_KEY_LEFT]) {
                player_direction = LEFT;
                bullets[i].direction_x = -1;
                bullets[i].direction_y = 0;
            }
            else if (key[ALLEGRO_KEY_RIGHT]) {
                player_direction = RIGHT;
                bullets[i].direction_x = 1;
                bullets[i].direction_y = 0;
            }
            else if (key[ALLEGRO_KEY_DOWN]) {
                player_direction = DOWN;
                bullets[i].direction_x = 0;
                bullets[i].direction_y = 1;
            }
            else if (key[ALLEGRO_KEY_UP]) {
                player_direction = UP;
                bullets[i].direction_x = 0;
                bullets[i].direction_y = -1;
            }
            else {
                switch (player_direction) {
                case LEFT:
                    bullets[i].direction_x = -1;
                    bullets[i].direction_y = 0;
                    break;
                case RIGHT:
                    bullets[i].direction_x = 1;
                    bullets[i].direction_y = 0;
                    break;
                case UP:
                    bullets[i].direction_x = 0;
                    bullets[i].direction_y = -1;
                    break;
                case DOWN:
                    bullets[i].direction_x = 0;
                    bullets[i].direction_y = 1;
                    break;
                }
            }
            break;
        }
    }
}

void move_summons() {
	// 적 이동 관련
	for (int i = 0; i < MAX_KNIGHTS; i++) {
		if (enemies[i].active && !enemies[i].matched) {
			float dx = player.x - enemies[i].x;
			float dy = player.y - enemies[i].y;
			float distance = sqrt(dx * dx + dy * dy);
			if (distance > 30) {
				enemies[i].x += dx / distance * enemies[i].speed;
				enemies[i].y += dy / distance * enemies[i].speed;
			}
		}
	}

	// 소환수 이동 관련
	for (int i = 0; i < MAX_SUMMONS; i++) {
		if (summons[i].active && !summons[i].matched) {
			float min_distance = SCREEN_WIDTH * SCREEN_HEIGHT;
			int closest_enemy = -1;
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
			if (closest_enemy != -1) {
				float dx = enemies[closest_enemy].x - summons[i].x;
				float dy = enemies[closest_enemy].y - summons[i].y;
				float distance = sqrt(dx * dx + dy * dy);
				if (distance > 1) {
					summons[i].x += dx / distance * summons[i].speed;
					summons[i].y += dy / distance * summons[i].speed;
				}
			}
		}
	}

}

void move_bullets() {
    for (int i = 0; i < player.bullets; i++) {
        if (bullets[i].active) {
            bullets[i].x += bullets[i].direction_x * BULLET_SPEED;
            bullets[i].y += bullets[i].direction_y * BULLET_SPEED;
            if (bullets[i].x < 0 || bullets[i].x > SCREEN_WIDTH || bullets[i].y < 0 || bullets[i].y > SCREEN_HEIGHT) {
                bullets[i].active = false;
            }
        }
    }
}

void spawn_summon(int number) {
    Summon* target_array = summons;
    int i;
    int temp;
    int health;
    int damage;
    int credit;
    int size;
    double speed;
    switch (number) {
    case 11:
        // 좀비
        i = 0;
        temp = MAX_ZOMBIES;
        health = ZOMBIE_MAX_HEALTH;
        damage = 1;
        credit = 50;
        speed = 1.7;
        size = 50;
        break;
    case 12:
        // 고블린
        i = MAX_ZOMBIES;
        temp = MAX_GOBLINS;
        health = GOBLIN_MAX_HEALTH;
        damage = 2;
        credit = 100;
        speed = 2.0;
        size = 50;
        break;
    case 13:
        // 박쥐
        i = MAX_ZOMBIES + MAX_GOBLINS;
        temp = MAX_BATS;
        health = BAT_MAX_HEALTH;
        damage = 1;
        credit = 100;
        speed = 5.0;
        size = 30;
        break;
    default:
        printf("잘못된 입력값: %d\n", number);
        return;  // 잘못된 값이면 함수 종료
    }
    int max_summons = i;

    for (; i < max_summons + temp; i++) {
        if (!target_array[i].active && money_display >= credit) {
            money_display -= credit;
            target_array[i].x = player.x + (rand() % 121 - 60);
            target_array[i].y = player.y + (rand() % 121 - 60);
            target_array[i].active = true;
            target_array[i].matched = false;
            target_array[i].health = health;
            target_array[i].damage = damage;
            target_array[i].speed = speed;
            target_array[i].invincible = 0;
            target_array[i].matched_enemy = -1;
            target_array[i].size = size;
            break;
        }
    }
}

void spawn_enermy(int number) {
    Summon* target_array = enemies;
    int i;
    double health;
    int damage;
    int credit;
    int score;
    int speed;
    int max_summons;
    int temp;
    int size;
    switch (number) {
    case 1:
        // knight
        i = 0;
        temp = 0;
        health = KNIGHT_MAX_HEALTH;
        damage = 1;
        credit = 50;
        score = 100;
        speed = 2.0;
        max_summons = 5;
        size = 35;
        break;
    case 2:
        // 보스
        i = MAX_KNIGHTS;
        temp = MAX_BOSSES;
        health = BOSS_MAX_HEALTH;
        damage = 1;
        credit = 200;
        score = 500;
        speed = 0;
        max_summons = 3;
        size = 80;
        break;
    default:
        return;  // 잘못된 값이면 함수 종료
    }
    const int SAFE_ZONE = 300;
    int max_enemies = MAX_KNIGHTS;

    for (; i < MAX_KNIGHTS + temp; i++) {
        if (!target_array[i].active) {
            if(i >= MAX_KNIGHTS)al_play_sample(boss_summon, 0.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            int x, y;
            bool safe_position = false;

            while (!safe_position) {
                x = rand() % SCREEN_WIDTH;
                y = rand() % (SCREEN_HEIGHT - 250) + 230;

                if (abs(x - player.x) > SAFE_ZONE || abs(y - player.y) > SAFE_ZONE) {
                    safe_position = true;
                }
            }

            target_array[i].x = x;
            target_array[i].y = y;
            target_array[i].active = true;
            target_array[i].matched = false;
            target_array[i].health = health;
            target_array[i].damage = damage;
            target_array[i].credit = credit;
            target_array[i].score = score;
            target_array[i].speed = speed;
            target_array[i].invincible = 0;
            target_array[i].matched_enemy = -1;
            target_array[i].size = size;
            break;
        }
    }
}


void clear_summons(int number) {
	Summon* target_array;
	Summon* target_array2;
	int max;
	int max2;
	switch (number) {
	case 1:
		target_array = enemies;
		target_array2 = summons;
		max = MAX_ENEMIES;
		max2 = MAX_SUMMONS;
		break;
	case 11:
		target_array = summons;
		target_array2 = enemies;
		max = MAX_SUMMONS;
		max2 = MAX_ENEMIES;
		break;
	default:
		return;
	}
	for (int i = 0; i < max; i++) {
		target_array[i].active = false;
		for (int k = 0; k < max2; k++) {
			if (target_array2[k].active && target_array2[k].matched && target_array2[k].matched_enemy == i) {
				target_array2[k].matched = false;
				target_array2[k].matched_enemy = -1;
				break;
			}
		}
	}
}

void Special_moves(int number) {
	Summon* target_array;
	Summon* target_array2;
	int max;
	int max2;
	switch (number) {
	case 1:
		target_array = enemies;
		target_array2 = summons;
		max = MAX_ENEMIES;
		max2 = MAX_SUMMONS;
		break;
	case 11:
		target_array = summons;
		target_array2 = enemies;
		max = MAX_SUMMONS;
		max2 = MAX_ENEMIES;
		break;
	default:
		return;
	}
	for (int i = 0; i < max; i++) {
		target_array[i].health -= 5;
		invincible_timer = 120;
		if (target_array[i].health <= 0) {
			target_array[i].active = false;
			for (int k = 0; k < max2; k++) {
				if (target_array2[k].active && target_array2[k].matched && target_array2[k].matched_enemy == i) {
					target_array2[k].matched = false;
					target_array2[k].matched_enemy = -1;
					break;
				}
			}
		}
	}
}

void check_collision() {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemies[i].active && !enemies[i].matched) {
			for (int j = 0; j < MAX_SUMMONS; j++) {
				if (summons[j].active && !summons[j].matched) {
					float dx = enemies[i].x - summons[j].x;
					float dy = enemies[i].y - summons[j].y;
					float distance = sqrt(dx * dx + dy * dy);
					if (distance < COLLISION_DISTANCE) {
						enemies[i].matched = true;
						enemies[i].matched_enemy = j;
						summons[j].matched = true;
						summons[j].matched_enemy = i;
					}
				}
			}
		}
	}
	for (int j = 0; j < MAX_SUMMONS; j++) {
		if (summons[j].matched_enemy != -1) {
			int i = summons[j].matched_enemy;
			if (enemies[i].invincible <= 0) {
				enemies[i].health -= summons[j].damage;
				summons[j].health -= enemies[i].damage;
				enemies[i].invincible = 120;
				if (enemies[i].health <= 0) {
					money_display += enemies[i].credit;
					score_display += enemies[i].score;
					enemies[i].active = false;
					enemies[i].matched = false;
					enemies[i].matched_enemy = -1;
					summons[j].matched = false;
					summons[j].matched_enemy = -1;
				}
				if (summons[j].health <= 0) {
					summons[j].active = false;
					enemies[i].matched = false;
					enemies[i].matched_enemy = -1;
					summons[j].matched = false;
					summons[j].matched_enemy = -1;
				}
			}
			if (enemies[i].invincible > 0) enemies[i].invincible--;
		}
	}
}

void update_animation() {
	for (int i = 0; i < MAX_SUMMONS; ++i) {
		if (summons[i].active && summons[i].matched) {
			current_time[i] = al_get_time();
			current_time[i] = al_get_time();
			if (current_time[i] - last_update_time[i] >= FRAME_DELAY) {
				current_frame[i] = (current_frame[i] + 1) % FRAME_COUNT;
				last_update_time[i] = current_time[i];
			}
		}
	}
}

void update_animation2() {
	for (int i = 0; i < MAX_KNIGHTS; ++i) {
		if (enemies[i].active && enemies[i].matched) {
			current_enemies_time[i] = al_get_time();
			current_enemies_time[i] = al_get_time();
			if (current_enemies_time[i] - last_update_enemies_time[i] >= FRAME_DELAY) {
				current_enemies_frame[i] = (current_enemies_frame[i] + 1) % FRAME_COUNT;
				last_update_enemies_time[i] = current_enemies_time[i];
			}
		}
	}
}

void check_player_collision() {
	for (int j = 0; j < MAX_KNIGHTS; j++) {
		if (enemies[j].active) {
			float dx = player.x - enemies[j].x;
			float dy = player.y - enemies[j].y;
			float distance = sqrt(dx * dx + dy * dy);
			if (distance < COLLISION_DISTANCE) {
				if (invincible_timer <= 0) {
					player.health -= ENERMY_DAMAGE;
					invincible_timer = 180;

					if (player.health <= 0) {
						name(font);  // 이름 입력 받기
						break;
					}
				}
			}
		}
	}
	if (invincible_timer > 0) invincible_timer--;
}

void check_bullet_collision() {
    for (int i = 0; i < player.bullets; i++) {
        if (bullets[i].active) {
            for (int j = 0; j < MAX_ENEMIES; j++) {
                if (enemies[j].active) {
                    float dx = bullets[i].x - enemies[j].x;
                    float dy = bullets[i].y - enemies[j].y;
                    float distance = sqrt(dx * dx + dy * dy);
                    if (distance < enemies[j].size) {
                        enemies[j].health -= player.damage;
                        al_play_sample(monster_hit, 0.6, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                        if (enemies[j].health <= 0) {
                            score_display += enemies[j].score;
                            money_display += enemies[j].credit;
                            enemies[j].active = false;
                            enemies[j].matched_enemy = -1;

                            for (int k = 0; k < MAX_SUMMONS; k++) {
                                if (summons[k].active && summons[k].matched && summons[k].matched_enemy == j) {
                                    summons[k].matched = false;
                                    summons[k].matched_enemy = -1;
                                    break;
                                }
                            }
                        }
                        bullets[i].active = false;
                    }
                }
            }
        }
    }
}

void check_boss_bullet_collision(void) {
    for (int j = 0; j < MAX_BOSSES; ++j) {
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (boss_bullets[j][i].active) {
                for (int k = 0; k < MAX_SUMMONS; k++) {
                    if (summons[k].active) {
                        float dx = boss_bullets[j][i].x - summons[k].x;
                        float dy = boss_bullets[j][i].y - summons[k].y;
                        float distance = sqrt(dx * dx + dy * dy);
                        if (distance < summons[k].size) {
                            summons[k].health -= enemies[MAX_KNIGHTS+j].damage;
                            al_play_sample(monster_hit, 0.6, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                            if (summons[k].health <= 0) {
                                summons[k].active = false;
                                summons[k].matched_enemy = -1;

                                for (int l = 0; l < MAX_SUMMONS; l++) {
                                    if (enemies[l].active && enemies[l].matched && enemies[l].matched_enemy == k) {
                                        enemies[l].matched = false;
                                        enemies[l].matched_enemy = -1;
                                        break;
                                    }
                                }
                            }
                            boss_bullets[j][i].active = false;
                        }
                    }
                }
            }
            if (boss_bullets[j][i].active) {
                float dx = boss_bullets[j][i].x - player.x;
                float dy = boss_bullets[j][i].y - player.y;
                float distance = sqrt(dx * dx + dy * dy);
                if (distance < BULLET_COLLISION_DISTANCE) {
                    if (invincible_timer <= 0) {
                        player.health--;
                        invincible_timer = 180;
                        al_play_sample(monster_hit, 0.6, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    if (player.health <= 0) {
                        name(font);  // 이름 입력 받기
                        break;
                    }
                    boss_bullets[j][i].active = false;
                }
            }
        }
    }
}

void boss_shoot(int j) {
	int k = j + MAX_KNIGHTS;
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (!boss_bullets[j][i].active && enemies[k].active) {
			boss_bullets[j][i].x = enemies[k].x;
			boss_bullets[j][i].y = enemies[k].y;
			boss_bullets[j][i].active = true;
			float dx = player.x - enemies[k].x;
			float dy = player.y - enemies[k].y;
			float length = sqrt(dx * dx + dy * dy);
			if (length != 0) {
				boss_bullets[j][i].direction_x = (dx / length) * 5;
				boss_bullets[j][i].direction_y = (dy / length) * 5;
			}
			else {
				boss_bullets[j][i].direction_x = 0;
				boss_bullets[j][i].direction_y = 0;
			}

			break;
		}
	}
}

void move_boss_bullets() {
	for (int j = 0; j < MAX_BOSSES; ++j) {
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (boss_bullets[j][i].active) {
				boss_bullets[j][i].x += boss_bullets[j][i].direction_x;
				boss_bullets[j][i].y += boss_bullets[j][i].direction_y;
				if (boss_bullets[j][i].x < 0 || boss_bullets[j][i].x > SCREEN_WIDTH ||
					boss_bullets[j][i].y < 0 || boss_bullets[j][i].y > SCREEN_HEIGHT) {
					boss_bullets[j][i].active = false;
				}
			}
		}
	}
}



void attack_boss() {
	for (int i = 0; i < MAX_BOSSES; ++i) {
		if (enemies[i + MAX_KNIGHTS].active) {
			boss_shoot_timer[i]++;
			if (boss_shoot_timer[i] > boss_attack_delay) {
				boss_shoot(i);
				boss_shoot_timer[i] = 0;
			}
		}
	}
}
