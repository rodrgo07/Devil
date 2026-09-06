#include "test_harness.hpp"

#include "../../src/core/logger/logger.hpp"

using core::logger::Logger;

TEST(logger_start_stop) {
    Logger logger;
    EXPECT_TRUE(logger.start());
    EXPECT_TRUE(logger.running());
    logger.stop();
    EXPECT_FALSE(logger.running());
}

TEST(logger_start_twice_is_idempotent) {
    Logger logger;
    EXPECT_TRUE(logger.start());
    EXPECT_TRUE(logger.start());
    logger.stop();
}