#pragma once

#include <filesystem>
#include <string>

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

}  // namespace core::config