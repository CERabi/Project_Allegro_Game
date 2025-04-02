#include "resource.h"

void load_resource(void) {
    player_x = SCREEN_WIDTH / 2;
    player_y = SCREEN_HEIGHT / 2;
    player_health = 5;
    player_size = 30;
    invincible_timer = 120;
    // ��� �̹��� �ε�
    background = al_load_bitmap("Resource/pic/battleback1.png");
    if (!background) {
        printf("�̹����� �ҷ����� ���߽��ϴ�!\n");
        return;
    }

    // ��ȯ�� �̹��� �ε�
    summon_img_l = al_load_bitmap("Resource/pic/zombie_l.png");
    if (!summon_img_l) {
        fprintf(stderr, "zombie_l.png �ε� ����!\n");
        return;
    }
    summon_img_r = al_load_bitmap("Resource/pic/zombie_r.png");
    if (!summon_img_r) {
        fprintf(stderr, "zombie_r.png �ε� ����!\n");
        return;
    }
    summon2_img_l = al_load_bitmap("Resource/pic/goblin_l.png");
    if (!summon_img_l) {
        fprintf(stderr, "goblin_l.png �ε� ����\n");
        return;
    }
    summon2_img_r = al_load_bitmap("Resource/pic/goblin_r.png");
    if (!summon_img_r) {
        fprintf(stderr, "goblin_r.png �ε� ����!\n");
        return;
    }
    enermy_img_l = al_load_bitmap("Resource/pic/knight_l.png");
    if (!enermy_img_l) {
        fprintf(stderr, "knight_l.png �ε� ����!\n");
        return;
    }
    enermy_img_r = al_load_bitmap("Resource/pic/knight_r.png");
    if (!enermy_img_r) {
        fprintf(stderr, "knight_r.png �ε� ����!\n");
        return;
    }
    enemy_boss_img_l = al_load_bitmap("Resource/pic/boss_l.png");
    if (!enemy_boss_img_l) {
        fprintf(stderr, "boss_l.png �ε� ����!\n");
        return;
    }
    enemy_boss_img_r = al_load_bitmap("Resource/pic/boss_r.png");
    if (!enemy_boss_img_r) {
        fprintf(stderr, "boss_r.png �ε� ����!\n");
        return;
    }


    // �÷��̾� �̹��� �ε�
    player_img_l = al_load_bitmap("Resource/pic/player_l.png");
    if (!player_img_l) {
        fprintf(stderr, "player_l.png �ε� ����!\n");
        return;
    }
    player_img_r = al_load_bitmap("Resource/pic/player_r.png");
    if (!player_img_r) {
        fprintf(stderr, "player_r.png �ε� ����!\n");
        return;
    }

    // ����ü �̹��� �ε�
    fireball_img = al_load_bitmap("Resource/pic/fireball.png");
    if (!fireball_img) {
        fprintf(stderr, "fireball.png �ε� ����!\n");
        return;
    }
    fireball_boss_img = al_load_bitmap("Resource/pic/fireball_boss.png");
    if (!fireball_boss_img) {
        fprintf(stderr, "fireball.png �ε� ����!\n");
        return;
    }

    // HUD �̹��� �ε�
    HUD_score = al_load_bitmap("Resource/pic/score.png");
    if (!HUD_score) {
        printf("�̹����� �ҷ����� ���߽��ϴ�!\n");
        return;
    }
    HUD_money = al_load_bitmap("Resource/pic/money.png");
    if (!HUD_money) {
        printf("�̹����� �ҷ����� ���߽��ϴ�!\n");
        return;
    }
    HUD_life = al_load_bitmap("Resource/pic/life.png");
    if (!HUD_life) {
        printf("�̹����� �ҷ����� ���߽��ϴ�!\n");
        return;
    }

    // ���� �̹��� �ε�
    SHOP_ORIGIN = al_load_bitmap("Resource/pic/shop_icon.png");
    SHOP_UP_ATT = al_create_sub_bitmap(SHOP_ORIGIN, 48, 0, 24, 24);
    SHOP_UP_SPD = al_create_sub_bitmap(SHOP_ORIGIN, 48, 48, 24, 24);
    SHOP_UP_ATT_NO = convert_to_grayscale(SHOP_UP_ATT);
    SHOP_UP_SPD_NO = convert_to_grayscale(SHOP_UP_SPD);

    // ��Ʈ �ε�
    font = al_load_ttf_font("Resource/font/DungGeunMo.otf", 70, 0);
    if (!font) {
        fprintf(stderr, "font �ε� ����!\n");
        return;
    }
    title_font = al_load_ttf_font("Resource/font/DungGeunMo.otf", 120, 0);
    if (!title_font) {
        fprintf(stderr, "title_font �ε� ����!\n");
        return;
    }
    button_font = al_load_ttf_font("Resource/font/DungGeunMo.otf", 70, 0);
    if (!button_font) {
        fprintf(stderr, "button_font �ε� ����!\n");
        return;
    }
    hud_font = al_load_ttf_font("Resource/font/DungGeunMo.otf", 50, 0);
    if (!hud_font) {
        fprintf(stderr, "hud_font �ε� ����!\n");
        return;
    }
}

void destroy_resource(void) {
    al_destroy_bitmap(background);
    al_destroy_bitmap(summon_img_l);
    al_destroy_bitmap(summon_img_r);
    al_destroy_bitmap(enermy_img_l);
    al_destroy_bitmap(enermy_img_r);
    al_destroy_bitmap(player_img_l);
    al_destroy_bitmap(player_img_r);
    al_destroy_bitmap(fireball_img);
    al_destroy_bitmap(HUD_score);
    al_destroy_bitmap(HUD_money);
    al_destroy_bitmap(HUD_life);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_font(font);
    al_destroy_font(title_font);
    al_destroy_font(button_font);
    al_destroy_font(hud_font);
}

ALLEGRO_BITMAP* convert_to_grayscale(ALLEGRO_BITMAP* original) {
    int width = al_get_bitmap_width(original);
    int height = al_get_bitmap_height(original);

    ALLEGRO_BITMAP* gray_bitmap = al_create_bitmap(width, height);
    if (!gray_bitmap) {
        printf("�׷��̽����� ��Ʈ�� ���� ����!\n");
        return NULL;
    }

    al_set_target_bitmap(gray_bitmap);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ALLEGRO_COLOR color = al_get_pixel(original, x, y);
            unsigned char r, g, b;
            al_unmap_rgb(color, &r, &g, &b);

            // ITU-R BT.601 ����ġ�� ������ �׷��̽����� ��ȯ
            unsigned char gray = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);

            al_put_pixel(x, y, al_map_rgb(gray, gray, gray));
        }
    }

    al_set_target_backbuffer(al_get_current_display());

    return gray_bitmap;
}
