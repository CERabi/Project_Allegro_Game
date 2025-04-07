#include "menu.h"

void draw_menu() {
    // ��� �̹��� ũ�� ���߱�
    al_draw_scaled_bitmap(background[backstage], 0, 0, al_get_bitmap_width(background[backstage]), al_get_bitmap_height(background[backstage]),
        0, 0, 1500, 900, 0);  // ȭ�� ũ�� 1500x900���� ����

    // ���� �ؽ�Ʈ�� ������ ��� ����
    al_draw_text(title_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 220, ALLEGRO_ALIGN_CENTER, "Awaken Witch");

    // ��ư ũ��� ��ġ ����
    int button_width = 600;  // ��ư�� �ʺ� Ű��
    int button_height = 70;  // ��ư�� ���̸� Ű��
    int button_x = 1500 / 2 - button_width / 2;  // ��ư�� ����� ����
    int button_y = 400;  // ù ��° ��ư�� y ��ǥ


    // �ؽ�Ʈ ũ�� ����
    int text_size = 70;  // �ؽ�Ʈ ũ�� Ű��

    // �ؽ�Ʈ ��ġ�� ��ư �߾ӿ� ���߱� ���� ��ư �߾ӿ� �°� ����
    const char* button_labels[] = { "Play", "Rankings", "Exit" };
    int num_buttons = sizeof(button_labels) / sizeof(button_labels[0]);

    for (int i = 0; i < num_buttons; i++) {
        al_draw_text(button_font, al_map_rgb(0, 0, 0),
            button_x + button_width / 2,
            button_y + button_height / 2 - text_size / 2 + i * 100,
            ALLEGRO_ALIGN_CENTER, button_labels[i]);
    }
}

bool is_button_clicked(int mouse_x, int mouse_y, int button_y_offset) {
    int button_width = 600;  // ��ư�� �ʺ�
    int button_height = 70;  // ��ư�� ����
    int button_x = 1500 / 2 - button_width / 2;  // ��ư�� X ��ǥ�� ������ �����
    int button_y = 400 + button_y_offset;  // ��ư�� Y ��ǥ (offset�� ���� ����)

    return mouse_x >= button_x && mouse_x <= button_x + button_width && mouse_y >= button_y && mouse_y <= button_y + button_height;
}

void show_rankings(ALLEGRO_FONT* font) {
    Player1 players[5];  
    int num_players = read_rankings(players, 5);

    static bool has_displayed_message = false; // �޽��� �ߺ� ����

    if (num_players == 0 && !has_displayed_message) {
        printf("No rankings to display.\n");
        has_displayed_message = true; // �� ���� ����ϵ��� ����
        return;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 90, ALLEGRO_ALIGN_CENTER, "Rankings");

    for (int i = 0; i < num_players; i++) {
        char ranking_text[50];
        sprintf_s(ranking_text, sizeof(ranking_text), "%d. %s - %d", i + 1, players[i].name, players[i].score);
        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 300 + (i * 70), ALLEGRO_ALIGN_CENTER, ranking_text);
    }

    int button_width = 200;
    int button_height = 110;
    int last_rank_y = 300 + (num_players * 70);
    int button_x = SCREEN_WIDTH / 2 - button_width - 20;
    int button_y = last_rank_y + 50;

    // "Back" ��ư
    al_draw_filled_rectangle(button_x, button_y, button_x + button_width, button_y + button_height, al_map_rgb(255, 255, 255));
    al_draw_rectangle(button_x, button_y, button_x + button_width, button_y + button_height, al_map_rgb(0, 0, 0), 3);
    al_draw_text(font, al_map_rgb(0, 0, 0), button_x + button_width / 2, button_y + 15, ALLEGRO_ALIGN_CENTER, "Back");

    // "Clear" ��ư
    int clear_x = SCREEN_WIDTH / 2 + 20;
    al_draw_filled_rectangle(clear_x, button_y, clear_x + button_width, button_y + button_height, al_map_rgb(255, 0, 0));
    al_draw_rectangle(clear_x, button_y, clear_x + button_width, button_y + button_height, al_map_rgb(0, 0, 0), 3);
    al_draw_text(font, al_map_rgb(0, 0, 0), clear_x + button_width / 2, button_y + 15, ALLEGRO_ALIGN_CENTER, "Clear");

    al_flip_display();

    // ?? ��ư Ŭ�� �̺�Ʈ ���� �߰�
    bool running = true;
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            // Back ��ư Ŭ�� Ȯ��
            if (mouse_x >= button_x && mouse_x <= button_x + button_width &&
                mouse_y >= button_y && mouse_y <= button_y + button_height) {
                strcpy(state, "menu");
                running = false;  // ���� ���� �� �޴��� ���ư�
            }

            // Clear ��ư Ŭ�� Ȯ��
            if (mouse_x >= clear_x && mouse_x <= clear_x + button_width &&
                mouse_y >= button_y && mouse_y <= button_y + button_height) {
                clear_rankings();  // ��ŷ �ʱ�ȭ
                running = false;  // ���� ���� �� �޴��� ���ư�
            }
        }

        // ESC Ű �Է� �� �޴��� ���ư���
        if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            strcpy(state, "menu");
            running = false;
        }
    }
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
    FILE* file;
    fopen_s(&file, "Resource/rank_db/rank.txt", "a");
    if (file) {
        fprintf(file, "%s %ld\n", player_name, score);
        fclose(file);
    }
    else {
        printf("���� ���� ����!\n");
    }
}

void clear_rankings() {
    FILE* file;
    fopen_s(&file, "Resource/rank_db/rank.txt", "w");
    if (file) {
        fclose(file);
        printf("��ŷ ������ �ʱ�ȭ �Ϸ�!\n");
    }
    else {
        printf("��ŷ �ʱ�ȭ ����!\n");
    }
}

void name(ALLEGRO_FONT* font) {
    char name[20] = { 0 };
    int index = 0;
    bool done = false;

    while (!done) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && index > 0) {
                name[--index] = '\0';
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                done = true;
            }
            else if (index < sizeof(name) - 1) {  // �迭 �����÷ο� ����
                if (event.keyboard.keycode >= ALLEGRO_KEY_A && event.keyboard.keycode <= ALLEGRO_KEY_Z) {
                    name[index++] = event.keyboard.keycode - ALLEGRO_KEY_A + 'A';
                }
                else if (event.keyboard.keycode >= ALLEGRO_KEY_0 && event.keyboard.keycode <= ALLEGRO_KEY_9) {
                    name[index++] = event.keyboard.keycode - ALLEGRO_KEY_0 + '0';
                }
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font, al_map_rgb(255, 0, 0), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, ALLEGRO_ALIGN_CENTER, "GAME OVER");
        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Please enter your name:");
        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTER, name);
        al_flip_display();
    }

    save_score(name, score_display);
    printf("�Է��� �̸�: %s, ����: %ld\n", name, score_display);
}

void exit_game() {
    al_uninstall_system();
    exit(0);
}
