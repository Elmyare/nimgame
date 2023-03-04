#include <libnim/nim.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void matches_amount(char mode, int A[3])
{
    if (mode == '1') { // Random bunch generation
        A[0] = rand() % 40 + 10;
        A[1] = rand() % 40 + 10;
        A[2] = rand() % 40 + 10;
    } else if (mode == '2') {
        printw("\nEnter (like: \"12 31 11\", MAX = 100): ");
        scanw("%d %d %d", A, A + 1, A + 2);
        while (bunch_input(A)) {
            printw("Incorrect input, enter again: ");
            scanw("%d %d %d", A, A + 1, A + 2);
        }
    }
}

void print_matches(int A[3])
{
    printw("|---------------------------------|\n");
    printw("|                                 |\n");
    printw("|       N  N   III   M   M        |\n");
    printw("|       NN N    I    MM MM        |\n");
    printw("|       N NN    I    M M M        |\n");
    printw("|       N  N   III   M   M        |\n");
    printw("|                                 |\n");
    printw("|   GGGG    AAA    M   M   EEEEE  |\n");
    printw("|  G       A   A   MM MM   E      |\n");
    printw("|  G  GG   AAAAA   M M M   EEEEE  |\n");
    printw("|  G   G   A   A   M   M   E      |\n");
    printw("|   GGG    A   A   M   M   EEEEE  |\n");
    printw("|                                 |\n");
    printw("|  On board:  %3.d  %3.d  %3.d       |\n", A[0], A[1], A[2]);
    refresh();
}

int take_matches(int amount, int bunch, int A[3])
{
    int result = 1;
    A[bunch] -= amount;
    if (A[bunch] < 0)
        A[bunch] = 0;
    if (A[0] == 0 && A[1] == 0 && A[2] == 0)
        result = 0;
    return result;
}

void get_bunch_and_amount(int player, char* bunch, int* amount, int A[3])
{
    srand(time(NULL));
    *bunch = '0';
    if (player == 1 || player == 2) {
        printw("%d player, select bunch (1 - 3): ", player);
        *bunch = getch();
        while (get_bunch(*bunch, A) == 1) {
            printw("\nIncorrect input, try again: ");
            *bunch = getch();
        }
        if (*bunch != 27) {
            printw("\nEnter amount: ");

            while (scanw("%d", amount) != 1 || get_amount(*amount))
                printw("Incorrect input, try again: ");
            clear();
        }
    } else if (player == 3) {
        clear();
        printw("Computer's turn:\n");
        *bunch = rand() % 3 + '1';
        while (A[*bunch - '1'] <= 0) {
            srand(time(NULL));
            *bunch = rand() % 3 + '1';
        }
        *amount = rand() % (A[*bunch - '1']) + 1;
    }
}

int game_mode(char mode)
{
    int result = 1;
    if (mode == '1' || mode == '2')
        result = 0;
    if (mode == 27)
        result = 2;
    return result;
}

int get_bunch(char nim_bunch, int bunches[3])
{
    int result = 1;
    if (nim_bunch >= '1' && nim_bunch <= '3' && bunches[nim_bunch - '1'] != 0)
        result = 0;
    if (nim_bunch == 27)
        result = 2;
    return result;
}

int get_amount(int nim_amount)
{
    int result = 1;
    if (nim_amount > 0)
        result = 0;
    return result;
}

int bunch_input(int A[3])
{
    int result = 0;
    if (A[0] <= 0 || A[1] <= 0 || A[2] <= 0 || A[0] > 100 || A[1] > 100
        || A[2] > 100)
        result = 1;
    return result;
}

int get_matches_mode(char nim_matches_mode)
{
    int result = 1;
    if (nim_matches_mode == '1' || nim_matches_mode == '2')
        result = 0;
    if (nim_matches_mode == 27)
        result = 2;
    return result;
}