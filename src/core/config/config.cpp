#include "config.hpp"

namespace core::config {

namespace {

constexpr std::string_view kConfigFile = "ironclad.ini";

}  // namespace

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
    const bool regular = std::filesystem::is_regular_file(path_, ec);
    return regular && !ec;
}

}  // namespace core::config