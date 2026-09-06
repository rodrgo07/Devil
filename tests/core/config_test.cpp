#include "test_harness.hpp"

#include "../../src/core/config/config.hpp"

TEST(config_defaults) {
    core::config::ConfigLoader loader;
    EXPECT_TRUE(loader.load());
    EXPECT_TRUE(loader.config().log_file.empty());
}

TEST(config_load_missing_file_uses_defaults) {
    core::config::ConfigLoader loader;
    EXPECT_TRUE(loader.load());
}