#include "test_harness.hpp"

#include "../../src/core/runtime/runtime.hpp"

using core::runtime::Runtime;
using core::runtime::State;

TEST(runtime_valid_transitions) {
    Runtime rt;
    EXPECT_TRUE(rt.initialize());
    EXPECT_EQ(rt.state(), State::Initializing);

    EXPECT_TRUE(rt.run());
    EXPECT_EQ(rt.state(), State::Running);

    EXPECT_TRUE(rt.stop());
    EXPECT_EQ(rt.state(), State::Stopped);
}

TEST(runtime_invalid_initialize_twice) {
    Runtime rt;
    EXPECT_TRUE(rt.initialize());
    EXPECT_FALSE(rt.initialize());
    EXPECT_EQ(rt.state(), State::Initializing);
    EXPECT_TRUE(rt.stop());
}

TEST(runtime_run_before_initialize_fails) {
    Runtime rt;
    EXPECT_FALSE(rt.run());
    EXPECT_EQ(rt.state(), State::Created);
    EXPECT_TRUE(rt.stop());
}

TEST(runtime_run_after_stopped_fails) {
    Runtime rt;
    EXPECT_TRUE(rt.initialize());
    EXPECT_TRUE(rt.run());
    EXPECT_TRUE(rt.stop());
    EXPECT_FALSE(rt.run());
    EXPECT_EQ(rt.state(), State::Stopped);
}

TEST(runtime_stop_from_created_succeeds) {
    Runtime rt;
    EXPECT_TRUE(rt.stop());
    EXPECT_EQ(rt.state(), State::Stopped);
}

TEST(runtime_repeated_stop_fails_cleanly) {
    Runtime rt;
    EXPECT_TRUE(rt.initialize());
    EXPECT_TRUE(rt.run());
    EXPECT_TRUE(rt.stop());
    EXPECT_FALSE(rt.stop());
    EXPECT_EQ(rt.state(), State::Stopped);
}