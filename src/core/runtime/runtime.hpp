#pragma once

namespace core::runtime {

enum class State {
    Created,
    Initializing,
    Running,
    Stopping,
    Stopped,
};

class Runtime final {
public:
    Runtime();
    ~Runtime();

    Runtime(const Runtime&) = delete;
    Runtime& operator=(const Runtime&) = delete;

    bool initialize();
    bool run();
    bool stop();

    State state() const noexcept { return state_; }

private:
    bool transition(State target);

    State state_ = State::Created;
};

}  // namespace core::runtime