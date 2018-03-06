#define CTEST_MAIN

#include <funcs.h>
#include <board.h>

#include <ctest.h>

CTEST(Syntax, CorrectSyntaxCheck) {
    int result = CheckSyntax("e2-e4",0,1);
    int expected = 1;
    ASSERT_EQUAL(expected,result);
}

CTEST(Syntax, IncorrectSyntaxCheck) {
    int result = CheckSyntax("nb1-a3",0,0);
    int expected = 0;
    ASSERT_EQUAL(expected,result);
}

CTEST(PawnMove, Correct) {
    int result = MakeMove("d2-d3",0,1);
    int expected = 1;
    ASSERT_EQUAL(expected,result);
}

CTEST(PawnMove, Inorrect) {
    int result = MakeMove("e4-f4",0,1);
    int expected = 0;
    ASSERT_EQUAL(expected,result);
}

CTEST(KnightMove, Correct) {
    int result = MakeMove("Nb1-a3",0,0);
    int expected = 1;
    ASSERT_EQUAL(expected,result);
}

CTEST(KnightMove, Inorrect) {
    int result = MakeMove("g1-h3",0,1);
    int expected = 0;
    ASSERT_EQUAL(expected,result);
}

CTEST(BishopMove, Correct) {
    int result = MakeMove("Bc1-d2",0,0);
    int expected = 1;
    ASSERT_EQUAL(expected,result);
}

CTEST(BishopMove, Inorrect) {
    int result = MakeMove("Bg1-h2",0,0);
    int expected = 0;
    ASSERT_EQUAL(expected,result);
}

CTEST(QueenMove, Correct) {
    MakeMove("e2-e3",0,1);
    int result = MakeMove("Qd1-e2",0,0);
    int expected = 1;
    ASSERT_EQUAL(expected,result);
}

CTEST(QueenMove, Inorrect) {
    int result = MakeMove("Qd8-d7",0,0);
    int expected = 0;
    ASSERT_EQUAL(expected,result);
}

CTEST(Castling, Correct) {
    int result = Castling(1,1);
    int expected = 1;
    ASSERT_EQUAL(expected,result);
}

CTEST(Castling, Inorrect) {
    int result = Castling(0,0);
    int expected = 0;
    ASSERT_EQUAL(expected,result);
}

int main(int argc, const char** argv) {
    InitBoard();
    int test_res = ctest_main(argc, argv);
    ClearBoard();
    return test_res;
}
