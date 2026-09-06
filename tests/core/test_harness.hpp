#pragma once

#include <cstdio>
#include <functional>
#include <string>
#include <vector>

namespace test {

struct Result {
    std::string name;
    bool passed;
};

inline std::vector<Result>& registry() {
    static std::vector<Result> results;
    return results;
}

inline int& failure_count() {
    static int count = 0;
    return count;
}

}  // namespace test

#define TEST(name)                                                       \
    [[maybe_unused]] static void name();                                  \
    namespace {                                                          \
    struct name##_registrar {                                            \
        name##_registrar() {                                             \
            test::registry().push_back(test::Result{#name, true});        \
        }                                                                \
    } name##_instance;                                                   \
    }                                                                     \
    static void name()

#define EXPECT_TRUE(expr)                                                \
    do {                                                                 \
        if (!(expr)) {                                                   \
            std::fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__,          \
                         __LINE__, #expr);                               \
            test::registry().back().passed = false;                      \
        }                                                                \
    } while (0)

#define EXPECT_FALSE(expr) EXPECT_TRUE(!(expr))

#define EXPECT_EQ(a, b) EXPECT_TRUE((a) == (b))

namespace test {

inline int run_all() {
    int failures = 0;
    for (const auto& r : registry()) {
        if (r.passed) {
            std::fprintf(stdout, "PASS %s\n", r.name.c_str());
        } else {
            std::fprintf(stdout, "FAIL %s\n", r.name.c_str());
            ++failures;
        }
    }
    return failures;
}

}  // namespace test