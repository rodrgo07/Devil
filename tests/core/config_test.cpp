#include "test_harness.hpp"

#include "../../src/core/config/config.hpp"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>

namespace {

using core::config::ConfigLoader;
namespace detail = core::config::detail;

constexpr const char* kConfigFile = "ironclad.ini";

struct ConfigFileGuard {
    explicit ConfigFileGuard(const std::string& content) {
        std::ofstream out(kConfigFile, std::ios::trunc);
        if (out.is_open()) {
            out << content;
        }
    }

    ~ConfigFileGuard() {
        std::remove(kConfigFile);
    }

    ConfigFileGuard(const ConfigFileGuard&) = delete;
    ConfigFileGuard& operator=(const ConfigFileGuard&) = delete;
};

void ensure_absent() {
    std::remove(kConfigFile);
}

}  // namespace

TEST(config_missing_file_uses_defaults) {
    ensure_absent();
    ConfigLoader loader;
    EXPECT_TRUE(loader.load());
    EXPECT_TRUE(loader.config().log_file.empty());
}

TEST(config_valid_log_file) {
    ConfigFileGuard guard("log_file=out.log\n");
    ConfigLoader loader;
    EXPECT_TRUE(loader.load());
    EXPECT_TRUE(loader.config().log_file == "out.log");
}

TEST(config_surrounding_whitespace_trimmed) {
    ConfigFileGuard guard("  log_file  =  out.log  \n");
    ConfigLoader loader;
    EXPECT_TRUE(loader.load());
    EXPECT_TRUE(loader.config().log_file == "out.log");
}

TEST(config_blank_lines_and_comments_ignored) {
    ConfigFileGuard guard("# comment\n\n   # indented comment\nlog_file=out.log\n\n");
    ConfigLoader loader;
    EXPECT_TRUE(loader.load());
    EXPECT_TRUE(loader.config().log_file == "out.log");
}

TEST(config_unknown_key_tolerated) {
    ConfigFileGuard guard("future_key=1\nlog_file=out.log\n");
    ConfigLoader loader;
    EXPECT_TRUE(loader.load());
    EXPECT_TRUE(loader.config().log_file == "out.log");
}

TEST(config_malformed_line_rejected) {
    ConfigFileGuard guard("this is not key=value\n");
    ConfigLoader loader;
    EXPECT_FALSE(loader.load());
}

TEST(config_empty_value_accepted) {
    ConfigFileGuard guard("log_file=\n");
    ConfigLoader loader;
    EXPECT_TRUE(loader.load());
    EXPECT_TRUE(loader.config().log_file.empty());
}

TEST(config_repeated_load_reflects_changed_file) {
    {
        ConfigFileGuard guard("log_file=first.log\n");
        ConfigLoader loader;
        EXPECT_TRUE(loader.load());
        EXPECT_TRUE(loader.config().log_file == "first.log");
    }
    {
        ConfigFileGuard guard("log_file=second.log\n");
        ConfigLoader loader;
        EXPECT_TRUE(loader.load());
        EXPECT_TRUE(loader.config().log_file == "second.log");
    }
}

TEST(config_malformed_does_not_partially_update) {
    ConfigFileGuard guard("log_file=out.log\nbroken line without equals\n");
    ConfigLoader loader;
    EXPECT_FALSE(loader.load());
    EXPECT_TRUE(loader.config().log_file.empty());
}

TEST(config_oversized_file_rejected) {
    std::ofstream out(kConfigFile, std::ios::trunc | std::ios::binary);
    const std::string big(1024, 'x');
    for (int i = 0; i < 70; ++i) {
        out << big << "\n";
    }
    out.close();

    ConfigLoader loader;
    EXPECT_FALSE(loader.load());
    std::remove(kConfigFile);
}

TEST(config_reload_after_failure_restores_defaults) {
    ConfigFileGuard guard("broken line\n");
    ConfigLoader loader;
    EXPECT_FALSE(loader.load());
    EXPECT_TRUE(loader.config().log_file.empty());
}

TEST(config_directory_as_file_rejected) {
    ensure_absent();
    std::error_code ec;
    std::filesystem::create_directory(kConfigFile, ec);
    if (ec) {
        return;
    }

    ConfigLoader loader;
    EXPECT_FALSE(loader.load());
    std::filesystem::remove(kConfigFile, ec);
}

TEST(parse_line_blank_input) {
    std::string_view key;
    std::string_view value;
    EXPECT_TRUE(detail::parse_line("   ", key, value) == detail::ParseResult::Skip);
}

TEST(parse_line_comment) {
    std::string_view key;
    std::string_view value;
    EXPECT_TRUE(detail::parse_line("# comment", key, value) == detail::ParseResult::Skip);
}

TEST(parse_line_without_equals) {
    std::string_view key;
    std::string_view value;
    EXPECT_TRUE(detail::parse_line("nokeyhere", key, value) == detail::ParseResult::Malformed);
}