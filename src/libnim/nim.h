#pragma once

#ifndef NIM_H
#define NIM_H

void matches_amount(char mode, int A[3]);

void print_matches(int A[3]);

int take_matches(int amount, int bunch, int A[3]);

void get_bunch_and_amount(int player, char* bunch, int* amount, int A[3]);

int game_mode(char mode);

int get_bunch(char nim_bunch, int bunches[3]);

int get_amount(int nim_amount);

int bunch_input(int A[3]);

int get_matches_mode(char nim_matches_mode);

#endif