#include <ctest.h>
#include <ncurses.h>
#include <stdio.h>

#include <libnim/nim.h>

CTEST(input, get_amount_test)
{
    ASSERT_EQUAL(0, get_amount(100));
    ASSERT_EQUAL(0, get_amount(1));
    ASSERT_EQUAL(1, get_amount(0));
    ASSERT_EQUAL(1, get_amount(-1));
    ASSERT_EQUAL(1, get_amount(-100));
}

CTEST(input, game_mode_test)
{
    ASSERT_EQUAL(0, game_mode('1'));
    ASSERT_EQUAL(0, game_mode('2'));
    ASSERT_EQUAL(1, game_mode('0'));
    ASSERT_EQUAL(1, game_mode('3'));
    ASSERT_EQUAL(1, game_mode('s'));
}

CTEST(input, get_bunch_test)
{
    int A[3] = {10, 10, 10};
    ASSERT_EQUAL(0, get_bunch('1', A));
    ASSERT_EQUAL(0, get_bunch('2', A));
    ASSERT_EQUAL(0, get_bunch('3', A));

    int B[3] = {0, 0, 0};

    ASSERT_EQUAL(1, get_bunch('1', B));
    ASSERT_EQUAL(1, get_bunch('2', B));
    ASSERT_EQUAL(1, get_bunch('3', B));

    ASSERT_EQUAL(1, get_bunch('0', A));
    ASSERT_EQUAL(1, get_bunch('4', A));
    ASSERT_EQUAL(1, get_bunch('c', A));
}

CTEST(input, bunch_input_test)
{
    int A[3] = {1, 1, 1};
    ASSERT_EQUAL(0, bunch_input(A));

    A[0] = 0;
    ASSERT_EQUAL(1, bunch_input(A));

    A[1] = 0;
    ASSERT_EQUAL(1, bunch_input(A));

    A[2] = 0;
    ASSERT_EQUAL(1, bunch_input(A));

    A[0] = 1;
    ASSERT_EQUAL(1, bunch_input(A));

    A[1] = 1;
    ASSERT_EQUAL(1, bunch_input(A));

    A[2] = 1;
    A[1] = 0;
    ASSERT_EQUAL(1, bunch_input(A));

    A[1] = 101;
    ASSERT_EQUAL(1, bunch_input(A));

    A[0] = 101;
    ASSERT_EQUAL(1, bunch_input(A));

    A[2] = 101;
    ASSERT_EQUAL(1, bunch_input(A));

    A[0] = 1;
    ASSERT_EQUAL(1, bunch_input(A));

    A[1] = 1;
    ASSERT_EQUAL(1, bunch_input(A));

    A[2] = 1;
    A[1] = 0;
    ASSERT_EQUAL(1, bunch_input(A));
}

CTEST(input, get_matches_mode_test)
{
    ASSERT_EQUAL(0, get_matches_mode('1'));
    ASSERT_EQUAL(0, get_matches_mode('2'));
    ASSERT_EQUAL(1, get_matches_mode('0'));
    ASSERT_EQUAL(1, get_matches_mode('3'));
    ASSERT_EQUAL(1, get_matches_mode('s'));
}

CTEST(end_test, take_matches_test)
{
    int A[3] = {50, 50, 50};
    ASSERT_EQUAL(1, take_matches(50, 2, A));
    ASSERT_EQUAL(1, take_matches(50, 1, A));
    ASSERT_EQUAL(0, take_matches(50, 0, A));

    A[0] = 50;
    A[1] = 50;
    A[2] = 50;

    ASSERT_EQUAL(1, take_matches(51, 0, A));
    ASSERT_EQUAL(1, take_matches(51, 1, A));
    ASSERT_EQUAL(0, take_matches(51, 2, A));
}
