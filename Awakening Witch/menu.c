#include "menu.h"

void draw_menu() {
    // 배경 이미지 크기 맞추기
    al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
        0, 0, 1500, 900, 0);  // 화면 크기 1500x900으로 변경

    // 제목 텍스트는 여전히 가운데 정렬
    al_draw_text(title_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 220, ALLEGRO_ALIGN_CENTER, "Awakening Witch");

    // 버튼 크기와 위치 조정
    int button_width = 600;  // 버튼의 너비를 키움
    int button_height = 70;  // 버튼의 높이를 키움
    int button_x = 1500 / 2 - button_width / 2;  // 버튼을 가운데에 정렬
    int button_y = 400;  // 첫 번째 버튼의 y 좌표


    // 텍스트 크기 설정
    int text_size = 70;  // 텍스트 크기 키움

    // 텍스트 위치를 버튼 중앙에 맞추기 위해 버튼 중앙에 맞게 정렬
    al_draw_text(button_font, al_map_rgb(0, 0, 0), button_x + button_width / 2, button_y + button_height / 2 - text_size / 2, ALLEGRO_ALIGN_CENTER, "Play");
    al_draw_text(button_font, al_map_rgb(0, 0, 0), button_x + button_width / 2, button_y + button_height / 2 - text_size / 2 + 100, ALLEGRO_ALIGN_CENTER, "Rankings");
    al_draw_text(button_font, al_map_rgb(0, 0, 0), button_x + button_width / 2, button_y + button_height / 2 - text_size / 2 + 200, ALLEGRO_ALIGN_CENTER, "Exit");
}

bool is_button_clicked(int mouse_x, int mouse_y, int button_y_offset) {
    int button_width = 600;  // 버튼의 너비
    int button_height = 70;  // 버튼의 높이
    int button_x = 1500 / 2 - button_width / 2;  // 버튼의 X 좌표는 여전히 가운데로
    int button_y = 400 + button_y_offset;  // 버튼의 Y 좌표 (offset에 따라 조정)

    return mouse_x >= button_x && mouse_x <= button_x + button_width && mouse_y >= button_y && mouse_y <= button_y + button_height;
}

void show_rankings(ALLEGRO_FONT* font) {
    Player1 players[5];  // 최대 10명의 랭킹을 화면에 표시
    int num_players = read_rankings(players, 5);

    if (num_players == 0) {
        printf("No rankings to display.\n");
        return;
    }

    // 배경을 그립니다 (배경 이미지를 그릴 수도 있음)
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // 타이틀 그리기
    al_draw_text(font, al_map_rgb(255, 255, 255), 1500 / 2, 90, ALLEGRO_ALIGN_CENTER, "Rankings");

    // 랭킹 리스트 그리기
    for (int i = 0; i < num_players; i++) {
        char ranking_text[50];
        sprintf_s(ranking_text, sizeof(ranking_text), "%d. %s - %d", i + 1, players[i].name, players[i].score);

        // 각 랭킹을 화면에 그립니다.
        al_draw_text(font, al_map_rgb(255, 255, 255), 1500 / 2, 300 + (i * 70), ALLEGRO_ALIGN_CENTER, ranking_text);
    }

    al_flip_display();  // 화면에 그린 내용을 표시
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

    // 순위 표시
    for (int i = 0; i < num_players; i++) {
        char rank_text[40];
        sprintf_s(rank_text, sizeof(rank_text), "%d. %s - %d", i + 1, players[i].name, players[i].score);
        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 150 + i * 40, ALLEGRO_ALIGN_CENTER, rank_text);
    }

    // "Back" 버튼
    al_draw_filled_rectangle(300, 500, 500, 550, al_map_rgb(255, 255, 255));
    al_draw_rectangle(300, 500, 500, 550, al_map_rgb(0, 0, 0), 3);
    al_draw_text(font, al_map_rgb(0, 0, 0), 400, 510, ALLEGRO_ALIGN_CENTER, "Back");
}

int read_rankings(Player1 players[], int max_players) {
    FILE* file;
    fopen_s(&file, "Resource/rank_db/rank.txt", "r");
    if (!file) {
        printf("파일 열기 실패!\n");
        return 0;
    }

    Player1 all_players[100]; // 최대 100명까지 저장 가능하도록 설정 (필요하면 조절 가능)
    int num_players = 0;

    // 모든 데이터를 읽어들임
    while (fscanf_s(file, "%19s %d", all_players[num_players].name,
        (unsigned)_countof(all_players[num_players].name),
        &all_players[num_players].score) == 2) {
        num_players++;
        if (num_players >= 100) break; // 100명을 초과하면 중단
    }

    fclose(file);

    // 점수 기준으로 내림차순 정렬
    qsort(all_players, num_players, sizeof(Player1), compare_players);

    // 상위 max_players명만 저장
    int limit = (num_players < max_players) ? num_players : max_players;
    for (int i = 0; i < limit; i++) {
        players[i] = all_players[i];
    }

    return limit;  // 최종적으로 저장된 플레이어 수 반환
}


// 점수 기준으로 내림차순으로 비교 함수
int compare_players(const void* a, const void* b) {
    Player1* playerA = (Player1*)a;
    Player1* playerB = (Player1*)b;

    return playerB->score - playerA->score;  // 내림차순 정렬
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
        fprintf(file, "%s %ld\n", player_name, score);  // 이름과 점수를 저장
        fclose(file);
    }
}

void name(ALLEGRO_FONT* font) {
    char name[20] = { 0 };  // 이름을 저장할 배열
    int index = 0;
    bool done = false;

    while (!done) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && index > 0) {
                name[--index] = '\0';  // 백스페이스 처리
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                done = true;  // 엔터 키를 누르면 입력 종료
            }
            else if (index < 19) {
                // 알파벳 A-Z 입력 처리
                if (event.keyboard.keycode >= ALLEGRO_KEY_A && event.keyboard.keycode <= ALLEGRO_KEY_Z) {
                    name[index++] = event.keyboard.keycode - ALLEGRO_KEY_A + 'A';  // 대문자 입력 처리
                }
                // 숫자 0-9 입력 처리
                else if (event.keyboard.keycode >= ALLEGRO_KEY_0 && event.keyboard.keycode <= ALLEGRO_KEY_9) {
                    name[index++] = event.keyboard.keycode - ALLEGRO_KEY_0 + '0';  // 숫자 입력 처리
                }
            }
        }


        al_clear_to_color(al_map_rgb(0, 0, 0));  // 배경을 검정색으로 설정

        al_draw_text(font, al_map_rgb(255, 0, 0), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3,
            ALLEGRO_ALIGN_CENTER, "GAME OVER");
        // 사각형 테두리 그리기 (입력창 테두리)
        //al_draw_rectangle(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - 50, SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 2 + 50, al_map_rgb(255, 255, 255), 3);

        // "이름을 입력하세요:" 문구 표시
        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2,
            ALLEGRO_ALIGN_CENTER, "Please enter your name:");

        // 현재 입력된 이름 표시
        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100,
            ALLEGRO_ALIGN_CENTER, name);

        al_flip_display();  // 화면 갱신
    }

    // 점수 저장
    save_score(name, score_display);
    printf("입력한 이름: %s, 점수: %ld\n", name, score_display);
}
