#include "test_harness.hpp"

#include "../../src/core/runtime/runtime.hpp"

using core::runtime::Runtime;
using core::runtime::State;

TEST(runtime_valid_transitions) {
    Runtime rt;
    EXPECT_TRUE(rt.initialize());
    EXPECT_EQ(rt.state(), State::Initializing);

    rt.run();
    EXPECT_EQ(rt.state(), State::Running);

    rt.stop();
    EXPECT_EQ(rt.state(), State::Stopped);
}

TEST(runtime_invalid_initialize_twice) {
    Runtime rt;
    EXPECT_TRUE(rt.initialize());
    EXPECT_FALSE(rt.initialize());
    rt.stop();
}

TEST(runtime_run_before_initialize) {
    Runtime rt;
    rt.run();
    EXPECT_FALSE(rt.state() == State::Running);
    rt.stop();
}