#include "init.h"

void init(void) {
    strcpy(state, "menu");
    srand(time(NULL));

    if (!al_init()) {
        fprintf(stderr, "Allegro 초기화 실패!\n");
        return;
    }
    last_att = -1.0f;

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        fprintf(stderr, "디스플레이 생성 실패!\n");
        return;
    }
    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Allegro primitives 초기화 실패!\n");
        return;
    }
    if(!al_init_image_addon()) {
        fprintf(stderr, "Allegro image 초기화 실패!\n");
        return;
    }
    if (!al_install_mouse()) {
        fprintf(stderr, "Allegro mouse 초기화 실패!\n");
        return;
    }
    if(!al_install_keyboard()) {
        fprintf(stderr, "Allegro keyboard 초기화 실패!\n");
        return;
    }
    if(!al_init_font_addon()) {
        fprintf(stderr, "Allegro font 초기화 실패!\n");
        return;
    }
    if(!al_init_ttf_addon()) {
        fprintf(stderr, "Allegro ttf 초기화 실패!\n");
        return;
    }

    for (int i = 0; i < MAX_SUMMONS; i++) enemies[i].matched_enemy = -1;
    for (int i = 0; i < MAX_SUMMONS; i++) summons[i].matched_enemy = -1;

    load_resource();
    hud_init();

    timer = al_create_timer(1.0 / 60.0);
    spawn_timer = al_create_timer(3.0);
    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(spawn_timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());    
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);
    al_start_timer(spawn_timer);

    al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
        0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    al_flip_display();
}