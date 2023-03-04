#include <libnim/nim.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main()
{
    srand(time(NULL));
    initscr();
    echo();
    nodelay(stdscr, FALSE);

    int A[3], amount, end, result = 0, exit = 0;
    char bunch, player_mode, matches_mode;

    printw("Choose player mode\n1 - 2 players\n2 - play with computer\nESC - "
           "Exit\n: ");
    player_mode = getch();
    while (game_mode(player_mode) == 1)
        printw("\nIncorrect input, enter again: ");
    end = 1;
    printw("\nChoose matches amount\n1 - random matches\n2 - Enter matches "
           "amount by yourself\nESC - Exit\n: ");
    refresh();
    matches_mode = getch();
    while (get_matches_mode(matches_mode) == 1) {
        printw("\nIncorrect input, enter again: ");
        matches_mode = getch();
    }
    if (matches_mode != 27 && player_mode != 27) {
        matches_amount(matches_mode, A);
        clear();
        print_matches(A);
        while (end) {
            refresh();
            get_bunch_and_amount(1, &bunch, &amount, A);
            if (bunch == 27) {
                exit = 1;
                break;
            }
            end = take_matches(amount, bunch - '1', A);
            print_matches(A);
            refresh();
            if (end == 0) {
                result = 1;
                break;
            }
            get_bunch_and_amount(player_mode - '0' + 1, &bunch, &amount, A);
            if (bunch == 27) {
                exit = 1;
                break;
            }
            end = take_matches(amount, bunch - '1', A);
            print_matches(A);
            refresh();
        }
    }
    if (exit || player_mode == 27 || matches_mode == 27) {
        printw("\n|              EXIT               |");
        refresh();
    } else if (player_mode - '0' == 1) {
        int player;
        if (result == 1)
            player = 1;
        else
            player = 2;
        printw("|          %d PLAYER WIN!          |", player);
        refresh();
    } else if (result == 1) {
        printw("|            YOU WIN!             |");
        refresh();
    } else {
        printw("|           GAME OVER!            |");
        refresh();
    }
    usleep(600000);
    endwin();
    return 0;
}