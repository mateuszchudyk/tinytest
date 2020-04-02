#include "tinytest.h"

TINY_TEST(passed_test) {
    TINY_CHECK(1, 1);
    TINY_CHECK_EPS(1.0f, 1.1f, 0.5f);

    int mem_expected1[] = {1, 2, 3};
    int mem_actual1[]   = {1, 2, 3};
    TINY_CHECK_MEM(mem_expected1, mem_actual1, sizeof(mem_expected1) / sizeof(mem_expected1[0]));

    float mem_expected2[] = {1.1f, 2.2f, 3.3f};
    float mem_actual2[]   = {1.2f, 2.0f, 3.5f};
    TINY_CHECK_MEM_EPS(mem_expected2, mem_actual2, sizeof(mem_expected2) / sizeof(mem_expected2[0]), 0.5f);
}

TINY_TEST(failed_test) {
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

int main() {
    return tinytest::run_all_tests();
}
