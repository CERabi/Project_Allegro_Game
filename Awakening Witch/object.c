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

void player_enhance_sp() {
    if (money_display < 50) return;
    player.speed += 5;
    money_display -= 50;
}

void player_enhance_dm() {
    if (money_display < 50) return;
    player.damage += 1;
    money_display -= 50;
}

void fire_bullet() {
    double now = al_get_time();
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active && now - last_att > ATTACK_DELAY) {
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
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active && !enemies[i].matched) {
            float dx = player.x - enemies[i].x;
            float dy = player.y - enemies[i].y;
            float distance = sqrt(dx * dx + dy * dy);
            if (distance > 1) {
                enemies[i].x += dx / distance * ENEMY_SPEED;
                enemies[i].y += dy / distance * ENEMY_SPEED;
            }
        }
    }

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
                    summons[i].x += dx / distance * SUMMON_SPEED;
                    summons[i].y += dy / distance * SUMMON_SPEED;
                }
            }
        }
    }
}

void move_bullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].x += bullets[i].direction_x * BULLET_SPEED;
            bullets[i].y += bullets[i].direction_y * BULLET_SPEED;
            if (bullets[i].x < 0 || bullets[i].x > SCREEN_WIDTH || bullets[i].y < 0 || bullets[i].y > SCREEN_HEIGHT) {
                bullets[i].active = false;
            }
        }
    }
}

void spawn_player(void) {
    invincible_timer = 0;
    player.x = SCREEN_WIDTH / 2;
    player.y = SCREEN_HEIGHT / 2;
    player.health = PLAYER_HEALTH;
    player.damage = BULLET_DAMAGE;
    player.speed = PLAYER_SPEED;
    player.sees_left = true;
}

void spawn_summon(int number) {
    Summon* target_array = summons;
    int max_summons = MAX_SUMMONS;

    for (int i = 0; i < max_summons; i++) {
        if (!target_array[i].active) {
            target_array[i].x = player.x + (rand() % 121 - 60);
            target_array[i].y = player.y + (rand() % 121 - 60);
            target_array[i].active = true;
            target_array[i].matched = false;
            target_array[i].health = ENEMY_HEALTH;
            target_array[i].invincible = 0;
            target_array[i].matched_enemy = -1;
            break;
        }
    }
}

void spawn_enermy(int number) {
    Summon* target_array;
    switch (number) {
    case 1:
        target_array = enemies;
        break;
    case 2:
        target_array = enemies_boss;
        break;
    default:
        printf("잘못된 입력값: %d\n", number);
        return;  // 잘못된 값이면 함수 종료
    }

    int max_summons = MAX_ENEMIES;
    const int SAFE_ZONE = 300;

    for (int i = 0; i < max_summons; i++) {
        if (!target_array[i].active) {
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
            target_array[i].health = ENEMY_HEALTH;
            target_array[i].invincible = 0;
            target_array[i].matched_enemy = -1;
            break;
        }
    }
}


void clear_summons(int number) {
    Summon* target_array;
    int max_summons;
    switch (number) {
    case 1:
        target_array = summons;
        max_summons = MAX_SUMMONS;
        break;
    case 11:
        target_array = enemies;
        max_summons = MAX_ENEMIES;
        break;
    default:
        printf("잘못된 입력값: %d\n", number);
        return;  // 잘못된 값이면 함수 종료
    }
    for (int i = 0; i < max_summons; i++) {
        target_array[i].active = false;
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
                enemies[i].health--;
                summons[j].health--;
                enemies[i].invincible = 120;
                printf("적 %d의 체력 : %d 소환수 %d의 체력 %d\n", i, enemies[i].health, j, summons[j].health);
                if (enemies[i].health <= 0) {
                    money_display += 50;
                    score_display += 100;
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


void check_player_collision() {
    for (int j = 0; j < MAX_ENEMIES; j++) {
        if (enemies[j].active) {
            float dx = player.x - enemies[j].x;
            float dy = player.y - enemies[j].y;
            float distance = sqrt(dx * dx + dy * dy);
            if (distance < COLLISION_DISTANCE) {
                if (invincible_timer <= 0) {
                    player.health -= BULLET_DAMAGE;
                    invincible_timer = 180;
                    printf("플레이어 남은 체력 : %d\n", player.health);
                    if (player.health <= 0) {
                        exit(0);
                    }
                }
            }
        }
    }
    if (invincible_timer > 0) invincible_timer--;
}

void check_bullet_collision() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            for (int j = 0; j < MAX_ENEMIES; j++) {
                if (enemies[j].active) {
                    float dx = bullets[i].x - enemies[j].x;
                    float dy = bullets[i].y - enemies[j].y;
                    float distance = sqrt(dx * dx + dy * dy);
                    if (distance < COLLISION_DISTANCE) {
                        enemies[j].health -= BULLET_DAMAGE;
                        if (enemies[j].health <= 0) {
                            score_display += 100;
                            money_display += 50;
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