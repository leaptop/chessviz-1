#define CTEST_MAIN

#include <funcs.h>
#include <board.h>

#include <ctest.h>

CTEST(simple_suite, is_char_in_bounds_test) {
    const int result = InBounds('b','a','c');
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

int main(int argc, const char** argv) {
    return ctest_main(argc, argv);
}
