#pragma once

#include <string_view>

namespace core::logger {

enum class Level {
    Info,
    Warning,
    Error,
};

class Logger {
public:
    Logger() = default;

    bool start();
    void stop();

    void log(Level level, std::string_view message);

    bool running() const noexcept { return running_; }

private:
    bool running_ = false;
};

}  // namespace core::logger