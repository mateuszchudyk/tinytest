#include "tinytest.h"

TINY_TEST(tiny_test_passed) {
    TINY_CHECK(1, 1);
    TINY_CHECK_EPS(1.0f, 1.1f, 0.5f);

    int mem_expected1[] = {1, 2, 3};
    int mem_actual1[]   = {1, 2, 3};
    TINY_CHECK_MEM(mem_expected1, mem_actual1, sizeof(mem_expected1) / sizeof(mem_expected1[0]));

    float mem_expected2[] = {1.1f, 2.2f, 3.3f};
    float mem_actual2[]   = {1.2f, 2.0f, 3.5f};
    TINY_CHECK_MEM_EPS(mem_expected2, mem_actual2, sizeof(mem_expected2) / sizeof(mem_expected2[0]), 0.5f);
}

TINY_TEST(tiny_test_failed) {
    TINY_CHECK(1, 2);
    TINY_CHECK_EPS(1.0f, 1.1f, 0.001f);

    int mem_expected1[] = {1, 2, 3};
    int mem_actual1[]   = {1, 3, 3};
    TINY_CHECK_MEM(mem_expected1, mem_actual1, sizeof(mem_expected1) / sizeof(mem_expected1[0]));

    float mem_expected2[] = {1.1f, 2.2f, 3.3f};
    float mem_actual2[]   = {1.1f, 2.0f, 3.3f};
    TINY_CHECK_MEM_EPS(mem_expected2, mem_actual2, sizeof(mem_expected2) / sizeof(mem_expected2[0]), 0.001f);
}

TINY_TEST(tiny_fail) {
    TINY_FAIL("This test always fails");
}

TINY_TEST(tiny_log) {
    TINY_LOG(TINY_DEFAULT, "Hello world!");
    TINY_LOG(TINY_DEFAULT, "This is the %d. log.", 2);
    TINY_LOG(TINY_YELLOW, "You can specify a color for a whole log...");
    TINY_LOG(TINY_DEFAULT, "...or only for a " TINY_COLOR(TINY_YELLOW, "part") " of it using TINY_COLOR macro.");
    TINY_LOG(TINY_DEFAULT, "Built-in colors:");
    TINY_LOG(TINY_GRAY, "TINY_GRAY");
    TINY_LOG(TINY_RED, "TINY_RED");
    TINY_LOG(TINY_GREEN, "TINY_GREEN");
    TINY_LOG(TINY_YELLOW, "TINY_YELLOW");
    TINY_LOG(TINY_BLUE, "TINY_BLUE");
    TINY_LOG(TINY_MAGENTA, "TINY_MAGENTA");
    TINY_LOG(TINY_CYAN, "TINY_CYAN");
}

TINY_PTEST(tiny_ptest, "N = %d", int N) {
    for (int i = 0; i < N; ++i)
        TINY_LOG(TINY_DEFAULT, "Example of TINY_PTEST");
}

TINY_PTEST_INSTANCE(tiny_ptest, 0);
TINY_PTEST_INSTANCE(tiny_ptest, 1);
TINY_PTEST_INSTANCE(tiny_ptest, 2);
TINY_PTEST_INSTANCE(tiny_ptest, 3);

int main() {
    // You can run only a certain test...
    // return TINY_TEST_RUN_TEST(tiny_log).passed;

    // ...or all tests.
    return TINY_TEST_RUN_ALL();
}
