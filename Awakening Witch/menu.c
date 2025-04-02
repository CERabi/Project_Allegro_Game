#include "menu.h"

void draw_menu() {
    // ��� �̹��� ũ�� ���߱�
    al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
        0, 0, 1500, 900, 0);  // ȭ�� ũ�� 1500x900���� ����

    // ���� �ؽ�Ʈ�� ������ ��� ����
    al_draw_text(title_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 220, ALLEGRO_ALIGN_CENTER, "Awakening Witch");

    // ��ư ũ��� ��ġ ����
    int button_width = 600;  // ��ư�� �ʺ� Ű��
    int button_height = 70;  // ��ư�� ���̸� Ű��
    int button_x = 1500 / 2 - button_width / 2;  // ��ư�� ����� ����
    int button_y = 400;  // ù ��° ��ư�� y ��ǥ


    // �ؽ�Ʈ ũ�� ����
    int text_size = 70;  // �ؽ�Ʈ ũ�� Ű��

    // �ؽ�Ʈ ��ġ�� ��ư �߾ӿ� ���߱� ���� ��ư �߾ӿ� �°� ����
    al_draw_text(button_font, al_map_rgb(0, 0, 0), button_x + button_width / 2, button_y + button_height / 2 - text_size / 2, ALLEGRO_ALIGN_CENTER, "Play");
    al_draw_text(button_font, al_map_rgb(0, 0, 0), button_x + button_width / 2, button_y + button_height / 2 - text_size / 2 + 100, ALLEGRO_ALIGN_CENTER, "Rankings");
    al_draw_text(button_font, al_map_rgb(0, 0, 0), button_x + button_width / 2, button_y + button_height / 2 - text_size / 2 + 200, ALLEGRO_ALIGN_CENTER, "Exit");
}

bool is_button_clicked(int mouse_x, int mouse_y, int button_y_offset) {
    int button_width = 600;  // ��ư�� �ʺ�
    int button_height = 70;  // ��ư�� ����
    int button_x = 1500 / 2 - button_width / 2;  // ��ư�� X ��ǥ�� ������ �����
    int button_y = 400 + button_y_offset;  // ��ư�� Y ��ǥ (offset�� ���� ����)

    return mouse_x >= button_x && mouse_x <= button_x + button_width && mouse_y >= button_y && mouse_y <= button_y + button_height;
}

void show_rankings(ALLEGRO_FONT* font) {
    Player1 players[5];  // �ִ� 10���� ��ŷ�� ȭ�鿡 ǥ��
    int num_players = read_rankings(players, 5);

    if (num_players == 0) {
        printf("No rankings to display.\n");
        return;
    }

    // ����� �׸��ϴ� (��� �̹����� �׸� ���� ����)
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // Ÿ��Ʋ �׸���
    al_draw_text(font, al_map_rgb(255, 255, 255), 1500 / 2, 90, ALLEGRO_ALIGN_CENTER, "Rankings");

    // ��ŷ ����Ʈ �׸���
    for (int i = 0; i < num_players; i++) {
        char ranking_text[50];
        sprintf_s(ranking_text, sizeof(ranking_text), "%d. %s - %d", i + 1, players[i].name, players[i].score);

        // �� ��ŷ�� ȭ�鿡 �׸��ϴ�.
        al_draw_text(font, al_map_rgb(255, 255, 255), 1500 / 2, 300 + (i * 70), ALLEGRO_ALIGN_CENTER, ranking_text);
    }

    al_flip_display();  // ȭ�鿡 �׸� ������ ǥ��
}


void exit_game() {
    al_uninstall_system();
    exit(0);
}

void draw_rankings(ALLEGRO_FONT* font, ALLEGRO_BITMAP* background) {
    Player1 players[MAX_RANKS];
    int num_players = read_rankings(players, MAX_RANKS);

    if (num_players == 0) {
        al_draw_text(font, al_map_rgb(255, 0, 0), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "No rankings available.");
        return;
    }

    al_draw_bitmap(background, 0, 0, 0);
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 50, ALLEGRO_ALIGN_CENTER, "Rankings");

    // ���� ǥ��
    for (int i = 0; i < num_players; i++) {
        char rank_text[40];
        sprintf_s(rank_text, sizeof(rank_text), "%d. %s - %d", i + 1, players[i].name, players[i].score);
        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 150 + i * 40, ALLEGRO_ALIGN_CENTER, rank_text);
    }

    // "Back" ��ư
    al_draw_filled_rectangle(300, 500, 500, 550, al_map_rgb(255, 255, 255));
    al_draw_rectangle(300, 500, 500, 550, al_map_rgb(0, 0, 0), 3);
    al_draw_text(font, al_map_rgb(0, 0, 0), 400, 510, ALLEGRO_ALIGN_CENTER, "Back");
}

int read_rankings(Player1 players[], int max_players) {
    FILE* file;
    fopen_s(&file, "Resource/rank_db/rank.txt", "r");
    if (!file) {
        printf("���� ���� ����!\n");
        return 0;
    }

    Player1 all_players[100]; // �ִ� 100����� ���� �����ϵ��� ���� (�ʿ��ϸ� ���� ����)
    int num_players = 0;

    // ��� �����͸� �о����
    while (fscanf_s(file, "%19s %d", all_players[num_players].name,
        (unsigned)_countof(all_players[num_players].name),
        &all_players[num_players].score) == 2) {
        num_players++;
        if (num_players >= 100) break; // 100���� �ʰ��ϸ� �ߴ�
    }

    fclose(file);

    // ���� �������� �������� ����
    qsort(all_players, num_players, sizeof(Player1), compare_players);

    // ���� max_players�� ����
    int limit = (num_players < max_players) ? num_players : max_players;
    for (int i = 0; i < limit; i++) {
        players[i] = all_players[i];
    }

    return limit;  // ���������� ����� �÷��̾� �� ��ȯ
}


// ���� �������� ������������ �� �Լ�
int compare_players(const void* a, const void* b) {
    Player1* playerA = (Player1*)a;
    Player1* playerB = (Player1*)b;

    return playerB->score - playerA->score;  // �������� ����
}

void rank(void) {
    show_rankings(font);

    ALLEGRO_EVENT ranking_event;
    al_wait_for_event(event_queue, &ranking_event);

    if (ranking_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ||
        (ranking_event.type == ALLEGRO_EVENT_KEY_DOWN && ranking_event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
        strcpy(state, "menu");
    }
}

void save_score(const char* player_name, long score) {
    FILE* file = fopen("Resource/rank_db/rank.txt", "a");
    if (file) {
        fprintf(file, "%s %ld\n", player_name, score);  // �̸��� ������ ����
        fclose(file);
    }
}

void name(ALLEGRO_FONT* font) {
    char name[20] = { 0 };  // �̸��� ������ �迭
    int index = 0;
    bool done = false;

    while (!done) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && index > 0) {
                name[--index] = '\0';  // �齺���̽� ó��
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                done = true;  // ���� Ű�� ������ �Է� ����
            }
            else if (index < 19) {
                // ���ĺ� A-Z �Է� ó��
                if (event.keyboard.keycode >= ALLEGRO_KEY_A && event.keyboard.keycode <= ALLEGRO_KEY_Z) {
                    name[index++] = event.keyboard.keycode - ALLEGRO_KEY_A + 'A';  // �빮�� �Է� ó��
                }
                // ���� 0-9 �Է� ó��
                else if (event.keyboard.keycode >= ALLEGRO_KEY_0 && event.keyboard.keycode <= ALLEGRO_KEY_9) {
                    name[index++] = event.keyboard.keycode - ALLEGRO_KEY_0 + '0';  // ���� �Է� ó��
                }
            }
        }


        al_clear_to_color(al_map_rgb(0, 0, 0));  // ����� ���������� ����

        al_draw_text(font, al_map_rgb(255, 0, 0), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3,
            ALLEGRO_ALIGN_CENTER, "GAME OVER");
        // �簢�� �׵θ� �׸��� (�Է�â �׵θ�)
        //al_draw_rectangle(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - 50, SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 2 + 50, al_map_rgb(255, 255, 255), 3);

        // "�̸��� �Է��ϼ���:" ���� ǥ��
        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2,
            ALLEGRO_ALIGN_CENTER, "Please enter your name:");

        // ���� �Էµ� �̸� ǥ��
        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100,
            ALLEGRO_ALIGN_CENTER, name);

        al_flip_display();  // ȭ�� ����
    }

    // ���� ����
    save_score(name, score_display);
    printf("�Է��� �̸�: %s, ����: %ld\n", name, score_display);
}
