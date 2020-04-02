#ifndef TINY_TEST_H
#define TINY_TEST_H

//------------------------------------------------------------------------------
// TinyTest information
//------------------------------------------------------------------------------

#define TINY_TEST_NAME                      "TinyTest"
#define TINY_TEST_VERSION                   "0.1.0"

//------------------------------------------------------------------------------
// You can define following macros by your own to customize TinyTest:
//   - TINY_TEST_MAX_TESTS                  - maximum number of tests
//   - TINY_TEST_PRINTF(format, ...)        - printing functions
//------------------------------------------------------------------------------

#ifndef TINY_TEST_MAX_TESTS
    #define TINY_TEST_MAX_TESTS             1000
#endif

#ifndef TINY_TEST_PRINTF
    #include <stdio.h>
    #define TINY_TEST_PRINTF(format, ...)   printf(format, __VA_ARGS__)
#endif

//------------------------------------------------------------------------------
// Macros you can use to create tests, checks, logs, etc.
//------------------------------------------------------------------------------

// Colors
#define TINY_DEFAULT                        "\x1b[0m"
#define TINY_GRAY                           "\x1b[90m"
#define TINY_RED                            "\x1b[91m"
#define TINY_GREEN                          "\x1b[92m"
#define TINY_YELLOW                         "\x1b[93m"
#define TINY_BLUE                           "\x1b[94m"
#define TINY_MAGENTA                        "\x1b[95m"
#define TINY_CYAN                           "\x1b[96m"
#define TINY_COLOR(color, text)             color text "\x1b[0m"

// Logs
#define TINY_LOG(color, ...)                __CHOOSE_WRAPPER(__TINY_LOG, __AT_LEAST_1_ARG(__VA_ARGS__), color, __VA_ARGS__)

// Test
#define TINY_TEST(test_name) \
    void test_name(tinytest::TestResult&); \
    static tinytest::TestAppender _tiny_wrapper_##test_name(#test_name " (" __FILE__ ")", test_name); \
    void test_name(tinytest::TestResult& _result_)

#define TINY_FAIL(...) \
    do { \
        TINY_LOG(TINY_RED, __VA_ARGS__); \
        _result_.passed = false; \
    } while (false)

#define TINY_CHECK(expected, actual) \
    do { \
        ++_result_.checks; \
        if ((expected) != (actual)) { \
            TINY_FAIL("values are different (expected = %d, actual = %d)", (expected), (actual)); \
             ++_result_.failed_checks; \
        } \
    } while (false)

#define TINY_CHECK_EPS(expected, actual, epsilon) \
    do { \
        ++_result_.checks; \
        if (__FABS((expected) - (actual)) > (epsilon)) { \
            TINY_FAIL("values differ by more then %f (expected = %f, actual = %f)", (epsilon), (expected), (actual)); \
             ++_result_.failed_checks; \
        } \
    } while (false)

#define TINY_CHECK_MEM(expected, actual, elements) \
    do { \
        ++_result_.checks; \
        bool failed = false; \
        for (unsigned i = 0; i < (elements); ++i) \
            if ((expected)[i] != (actual)[i]) { \
                TINY_FAIL("memories differ at %u-th position (expected = %d, actual = %d)", i, (expected)[i], (actual)[i]); \
                failed = true; \
            } \
        if (failed) \
            ++_result_.failed_checks; \
    } while (false)

#define TINY_CHECK_MEM_EPS(expected, actual, elements, epsilon) \
    do { \
        ++_result_.checks; \
        bool failed = false; \
        for (unsigned i = 0; i < (elements); ++i) \
            if (__FABS((expected)[i] - (actual)[i]) > (epsilon)) { \
                TINY_FAIL("memories differ at %u-th position by more then %f (expected = %f, actual = %f)", i, (epsilon), (expected)[i], (actual)[i]); \
                failed = true; \
            } \
        if (failed) \
            ++_result_.failed_checks; \
    } while (false)

//------------------------------------------------------------------------------
// TinyTest implementation detail. It's not important for you if you only
// want to use TinyTest.
//------------------------------------------------------------------------------

// Floating point absolute value
#define __FABS(a)   ((a) < 0 ? -(a) : (a))

// Workaround for unsupported optional arguments in variadic macros. Works if
// number of arguments passed in __VA_ARGS__ is not greater then 100.
#define __AT_LEAST_1_ARG_INNER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, \
    _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
    _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, \
    _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, \
    _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, \
    _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, \
    ARG, ...)  ARG

#define __AT_LEAST_1_ARG(...) \
    __AT_LEAST_1_ARG_INNER(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)

#define __CHOOSE_WRAPPER_INNER(name, more_then_one, ...) \
    name##_##more_then_one(__VA_ARGS__)

#define __CHOOSE_WRAPPER(name, version, ...) \
    __CHOOSE_WRAPPER_INNER(name, version, __VA_ARGS__)

#define __TINY_LOG_0(color, format)         TINY_TEST_PRINTF("[      ] " TINY_COLOR(color, "Line #%d: " format "\n"), __LINE__)
#define __TINY_LOG_1(color, format, ...)    TINY_TEST_PRINTF("[      ] " TINY_COLOR(color, "Line #%d: " format "\n"), __LINE__, __VA_ARGS__)

#define __PRINTLN_0(format)                 TINY_TEST_PRINTF(format "%c", '\n')
#define __PRINTLN_1(format, ...)            TINY_TEST_PRINTF(format "\n", __VA_ARGS__)
#define __PRINTLN(...)                      __CHOOSE_WRAPPER(__PRINTLN, __AT_LEAST_1_ARG(__VA_ARGS__), __VA_ARGS__)

struct tinytest {
    struct TestResult {
        bool passed;
        unsigned checks;
        unsigned failed_checks;
    };

    struct TestAppender {
        TestAppender(const char* name, void(*body)(TestResult&)) {
            *tinytest::all_tests_it++ = (Test){name, body};
        }
    };

    static bool run_all_tests() {
        __PRINTLN(
            "================================================================================\n"
            TINY_TEST_NAME " v" TINY_TEST_VERSION "\n"
            "================================================================================"
        );

        unsigned passed = 0;
        unsigned failed = 0;
        unsigned total_checks = 0;
        unsigned total_failed_checks = 0;
        for (const Test* it = all_tests; it != all_tests_it; ++it) {
            __PRINTLN("%c[ TEST ] %s", (it != all_tests ? '\n' : '\0'), it->name);

            TestResult result = {true, 0, 0};
            it->body(result);

            total_checks += result.checks;
            total_failed_checks += result.failed_checks;

            if (result.passed) {
                __PRINTLN("[------] " TINY_COLOR(TINY_GREEN, "Passed (%u/%u)"), result.checks, result.checks);
                ++passed;
            }
            else {
                __PRINTLN("[------] " TINY_COLOR(TINY_RED, "Failed (%u/%u)"), result.failed_checks, result.checks);
                ++failed;
            }
        }

        __PRINTLN(
            "================================================================================\n"
            TINY_COLOR(TINY_GREEN, "Passed   %u (%u/%u)\n")
            TINY_COLOR(TINY_RED, "Failed   %u (%u/%u)\n")
            "================================================================================",
            passed, total_checks - total_failed_checks, total_checks,
            failed, total_failed_checks, total_checks);

        if (failed == 0)
            __PRINTLN(TINY_COLOR(TINY_GREEN, "All tests passed!\n"));
        else
            __PRINTLN(TINY_COLOR(TINY_RED, "%d %s failed!\n"), failed, (failed == 1 ? "test" : "tests"));

        return failed == 0;
    }

private:
    struct Test {
        const char* name;
        void (*body)(TestResult&);
    };

    static Test all_tests[TINY_TEST_MAX_TESTS];
    static Test* all_tests_it;
};

tinytest::Test tinytest::all_tests[TINY_TEST_MAX_TESTS] = {};
tinytest::Test* tinytest::all_tests_it = tinytest::all_tests;

#endif