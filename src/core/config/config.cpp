#include "config.hpp"

#include <cctype>
#include <fstream>
#include <string>

namespace core::config {

namespace {

constexpr std::string_view kConfigFile = "ironclad.ini";
constexpr std::uintmax_t kMaxConfigSize = 64 * 1024;

std::string_view trim(std::string_view sv) {
    while (!sv.empty() && std::isspace(static_cast<unsigned char>(sv.front()))) {
        sv.remove_prefix(1);
    }
    while (!sv.empty() && std::isspace(static_cast<unsigned char>(sv.back()))) {
        sv.remove_suffix(1);
    }
    return sv;
}

}  // namespace

namespace detail {

ParseResult parse_line(std::string_view line, std::string_view& key, std::string_view& value) {
    const std::string_view trimmed = trim(line);

    if (trimmed.empty() || trimmed.front() == '#') {
        return ParseResult::Skip;
    }

    const auto eq = trimmed.find('=');
    if (eq == std::string_view::npos) {
        return ParseResult::Malformed;
    }

    key = trim(trimmed.substr(0, eq));
    value = trim(trimmed.substr(eq + 1));

    if (key.empty()) {
        return ParseResult::Malformed;
    }
    return ParseResult::Ok;
}

}  // namespace detail

bool ConfigLoader::load() {
    config_ = Config{};

    path_ = std::filesystem::current_path() / kConfigFile;

    return load_from_file();
}

bool ConfigLoader::load_from_file() {
    if (!std::filesystem::exists(path_)) {
        return true;
    }

    std::error_code ec;
    const std::uintmax_t size = std::filesystem::file_size(path_, ec);
    if (ec) {
        return false;
    }
    if (size > kMaxConfigSize) {
        return false;
    }

    std::ifstream file(path_);
    if (!file.is_open()) {
        return false;
    }

    Config parsed{};

    std::string line;
    while (std::getline(file, line)) {
        std::string_view key;
        std::string_view value;
        const auto result = detail::parse_line(line, key, value);
        if (result == detail::ParseResult::Skip) {
            continue;
        }
        if (result == detail::ParseResult::Malformed) {
            return false;
        }
        if (key == "log_file") {
            parsed.log_file = std::string(value);
        }
    }

    if (file.bad()) {
        return false;
    }

    config_ = std::move(parsed);
    return true;
}

}  // namespace core::config