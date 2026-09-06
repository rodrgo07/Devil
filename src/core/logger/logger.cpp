#include "logger.hpp"

#include <array>
#include <cstdio>

namespace core::logger {

namespace {

constexpr std::array<const char*, 3> kLevelTag = {
    "INFO",
    "WARN",
    "ERROR",
};

}  // namespace

bool Logger::start() {
    if (running_) {
        return true;
    }
    running_ = true;
    return true;
}

void Logger::stop() {
    running_ = false;
}

void Logger::log(Level level, std::string_view message) {
    if (!running_) {
        return;
    }
    const auto index = static_cast<std::size_t>(level);
    std::fprintf(stderr, "[%s] %.*s\n",
                 kLevelTag[index],
                 static_cast<int>(message.size()),
                 message.data());
}

}  // namespace core::logger