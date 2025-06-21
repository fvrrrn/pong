#include <stdio.h>
/* This is crazy-short version of Ping-Pong.
 * It was made this way to meet the following criteria:
 * 1. Function length does not exceed 42 characters;
 * 2. Only stdio is used;
 * 3. No structs;
 * 4. No dynamic memory;
 * 5. Only 1 return;
 * 6. No break/continue;
 * 7. No goto;
 * 8. No pointers;
 */
#define W 80
#define H 25
#define PS 3
#define P1X 2
#define P2X (W - 3)
#define S 5
void clear_screen() { printf("\033[2J\033[H"); }
void draw(int paddle1_y, int paddle2_y, int ball_x, int ball_y, int score1, int score2) {
    clear_screen();
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (x == 0 && y >= paddle1_y && y < paddle1_y + PS) {
                // left paddle
                printf("\u2588");
            } else if (x == W - 1 && y >= paddle2_y && y < paddle2_y + PS) {
                // right paddle
                printf("\u2588");
            } else if (x == ball_x && y == ball_y) {
                // ball
                printf("\u23fa");
            } else if (x == W / 2) {
                // net
                printf("\u2591");
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }
    printf("Score: Player1=%d | Player2=%d\n", score1, score2);
}
int main() {
    int s1 = 0, s2 = 0, p1y = H / 2 - PS / 2, p2y = H / 2 - PS / 2, bx = W / 2, by = H / 2, bdx = 1, bdy = -1;
    while (s1 < S && s2 < S) {
        draw(p1y, p2y, bx, by, s1, s2);
        char key = getchar();
        if (key == 'a' && p1y > 0) --p1y;
        if (key == 'z' && p1y + PS < H) ++p1y;
        if (key == 'k' && p2y > 0) --p2y;
        if (key == 'm' && p2y + PS < H) ++p2y;
        int next_x = bx + bdx;
        int next_y = by + bdy;
        if (next_y <= 0 || next_y >= H - 1) {
            bdy *= -1;
        } else if (next_x == P1X && next_y >= p1y && next_y < p1y + PS) {
            bdx *= -1;
        } else if (next_x == P2X && next_y >= p2y && next_y < p2y + PS) {
            bdx *= -1;
        } else if (next_x <= 0) {
            s2++;
            bx = W / 2;
            by = H / 2;
            bdx = 1;
            bdy = -1;
        } else if (next_x >= W - 1) {
            s1++;
            bx = W / 2;
            by = H / 2;
            bdx = -1;
            bdy = -1;
        } else {
            bx += bdx;
            by += bdy;
        }
    }
    s1 >= S ? printf("Player 1 wins!\n") : printf("Player 2 wins!\n");
    return 0;
}
