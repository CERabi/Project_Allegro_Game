#include "init.h"

void reset_game_state() {
    // �÷��̾� �ʱ�ȭ
    player.health = PLAYER_HEALTH;
    //player.health = 1;
    player.damage = BULLET_DAMAGE;
    player.speed = PLAYER_SPEED;
    player.sees_left = true;
    player.x = SCREEN_WIDTH / 2;
    player.y = SCREEN_HEIGHT / 2;
    invincible_timer = 0;
    /*for (int i = 0; i < ALLEGRO_KEY_MAX; ++i) {
        key[i] = 0;
    }*/
    memset(key, 0, sizeof(key));

    // ���� �� ��ȭ �ʱ�ȭ
    score_display = 0;
    money_display = 0;
    boss_attack_delay = 20;

    // ��ü ���� ��
    MAX_SUMMONS = MAX_ZOMBIES + MAX_GOBLINS;
    MAX_ENEMIES = MAX_KNIGHTS + MAX_BOSSES;

    // ���� �ʱ�ȭ
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = false;  // ��� �� ��Ȱ��ȭ
      // ��� �� ���� 
        enemies[i].matched_enemy = -1;
    }

    // ��ȯ�� �ʱ�ȭ
    for (int i = 0; i < MAX_SUMMONS; i++) {
        summons[i].active = false;  // ��� ��ȯ�� ��Ȱ��ȭ
        summons[i].matched_enemy = -1;
    }

    // ����ü ���� �ʱ�ȭ
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = false;
    }
    for (int i = 0; i < MAX_BOSSES; i++) {
        for (int j = 0; j < MAX_BULLETS; j++) {
            boss_bullets[i][j].active = false;
        }
    }

    // �÷��̾� ���� ���� �ʱ�ȭ
    last_att = 0;  // ���� Ÿ�̹� �ʱ�ȭ
}

void init(void) {
    strcpy(state, "menu");
    srand(time(NULL));

    if (!al_init()) {
        fprintf(stderr, "Allegro �ʱ�ȭ ����!\n");
        return;
    }
    last_att = -1.0f;

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        fprintf(stderr, "���÷��� ���� ����!\n");
        return;
    }
    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Allegro primitives �ʱ�ȭ ����!\n");
        return;
    }
    if(!al_init_image_addon()) {
        fprintf(stderr, "Allegro image �ʱ�ȭ ����!\n");
        return;
    }
    if (!al_install_mouse()) {
        fprintf(stderr, "Allegro mouse �ʱ�ȭ ����!\n");
        return;
    }
    if(!al_install_keyboard()) {
        fprintf(stderr, "Allegro keyboard �ʱ�ȭ ����!\n");
        return;
    }
    if(!al_init_font_addon()) {
        fprintf(stderr, "Allegro font �ʱ�ȭ ����!\n");
        return;
    }
    if(!al_init_ttf_addon()) {
        fprintf(stderr, "Allegro ttf �ʱ�ȭ ����!\n");
        return;
    }
    if (!al_install_audio()) {
        fprintf(stderr, "Allegro audio �ʱ�ȭ ����!\n");
        return;
    }
    if (!al_init_acodec_addon()) {
        fprintf(stderr, "Allegro audio �ʱ�ȭ ����!\n");
        return;
    }

    for (int i = 0; i < MAX_SUMMONS; i++) enemies[i].matched_enemy = -1;
    for (int i = 0; i < MAX_SUMMONS; i++) summons[i].matched_enemy = -1;

    al_reserve_samples(16);
    load_resource();
    hud_init();

    timer = al_create_timer(1.0 / 60.0);
    spawn_timer = al_create_timer(3.0);
    spawn_timer_boss = al_create_timer(12.0);
    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(spawn_timer));
    al_register_event_source(event_queue, al_get_timer_event_source(spawn_timer_boss));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());    
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);
    al_start_timer(spawn_timer);
    al_start_timer(spawn_timer_boss);

    al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
        0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    al_flip_display();
}