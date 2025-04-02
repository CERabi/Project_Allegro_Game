#define _CRT_SECURE_NO_WARNINGS


#include <string.h>
#include "init.h"
#include "gamescreen.h"
#include "menu.h"


int main(void) {
    init();
    bool running = true;
    bool redraw = true;  // ȭ�� ���� ����
    bool char_exists = false;

    while (true) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) running = false;
        if (ev.type == ALLEGRO_EVENT_TIMER) redraw = true;  // Ÿ�̸� �̺�Ʈ �߻� �� ȭ�� �ٽ� �׸���

        if (!strcmp(state, "game")) {
            reset_game_state();
            gamescreen();
            strcpy(state, "rank");
        }
        else if (!strcmp(state, "rank")) {
            rank();
        }
        else { // ���콺 �̺�Ʈ ������Ʈ
            if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                int x = ev.mouse.x;
                int y = ev.mouse.y;

                if (is_button_clicked(x, y, 0)) strcpy(state, "game");
                else if (is_button_clicked(x, y, 100)) strcpy(state, "rank");
                else if (is_button_clicked(x, y, 200)) exit_game();
            }

            if (redraw) {
                draw_menu();
                al_flip_display();
                redraw = false;
            }
        }
    }

    destroy_resource();

    return 0;
}