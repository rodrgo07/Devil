#pragma once

#include <filesystem>
#include <string>
#include <string_view>

namespace core::config {

struct Config {
    std::string log_file;
};

class ConfigLoader {
public:
    bool load();

    const Config& config() const noexcept { return config_; }

private:
    bool load_from_file();

    Config config_;
    std::filesystem::path path_;
};

namespace detail {

enum class ParseResult {
    Skip,
    Ok,
    Malformed,
};

ParseResult parse_line(std::string_view line, std::string_view& key, std::string_view& value);

}  // namespace detail

}  // namespace core::config