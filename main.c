#include <ncurses.h>

int main() {
    int max_y, max_x;

    int ball_x = 40, ball_y = 10;
    int dir_x = 1, dir_y = 1;

    int paddle1_y = 10;
    int paddle2_y = 10;

    int score1 = 0;
    int score2 = 0;

    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    while (1) {
        clear();
        getmaxyx(stdscr, max_y, max_x);

        // 🧮 Score
        mvprintw(0, max_x/2 - 12, "Player 1: %d   Player 2: %d", score1, score2);

        // 🏓 Paddles (height = 3)
        for (int i = 0; i < 3; i++) {
            mvprintw(paddle1_y + i, 2, "|");
            mvprintw(paddle2_y + i, max_x - 3, "|");
        }

        // ⚽ Ball
        mvprintw(ball_y, ball_x, "O");

        // 🎮 Input
        int ch = getch();

        // Player 1 (W/S)
        if (ch == 'w' && paddle1_y > 1) paddle1_y--;
        if (ch == 's' && paddle1_y < max_y - 4) paddle1_y++;

        // Player 2 (Arrow keys)
        if (ch == KEY_UP && paddle2_y > 1) paddle2_y--;
        if (ch == KEY_DOWN && paddle2_y < max_y - 4) paddle2_y++;

        // ⚽ Move ball
        ball_x += dir_x;
        ball_y += dir_y;

        // bounce top/bottom
        if (ball_y <= 1 || ball_y >= max_y - 1) {
            dir_y *= -1;
        }

        // 🏓 Left paddle collision
        if (ball_x == 3) {
            if (ball_y >= paddle1_y && ball_y <= paddle1_y + 2) {
                dir_x = 1;
            }
        }

        // 🏓 Right paddle collision
        if (ball_x == max_x - 4) {
            if (ball_y >= paddle2_y && ball_y <= paddle2_y + 2) {
                dir_x = -1;
            }
        }

        // ❌ Missed left → Player 2 scores
        if (ball_x <= 0) {
            score2++;
            ball_x = max_x / 2;
            ball_y = max_y / 2;
            dir_x = 1;
        }

        // ❌ Missed right → Player 1 scores
        if (ball_x >= max_x - 1) {
            score1++;
            ball_x = max_x / 2;
            ball_y = max_y / 2;
            dir_x = -1;
        }

        napms(50);
        refresh();
    }

    endwin();
    return 0;
}
