#include "runtime.hpp"

#include "../logger/logger.hpp"

namespace core::runtime {

namespace {

bool can_transition(State from, State to) {
    switch (from) {
        case State::Created:
            return to == State::Initializing || to == State::Stopped;
        case State::Initializing:
            return to == State::Running || to == State::Stopped;
        case State::Running:
            return to == State::Stopping;
        case State::Stopping:
            return to == State::Stopped;
        case State::Stopped:
            return false;
    }
    return false;
}

}  // namespace

Runtime::Runtime() = default;

Runtime::~Runtime() {
    stop();
}

bool Runtime::transition(State target) {
    if (!can_transition(state_, target)) {
        return false;
    }
    state_ = target;
    return true;
}

bool Runtime::initialize() {
    if (!transition(State::Initializing)) {
        return false;
    }
    return true;
}

void Runtime::run() {
    if (!transition(State::Running)) {
        return;
    }
}

void Runtime::stop() {
    if (state_ == State::Stopped || state_ == State::Stopping) {
        return;
    }
    if (state_ == State::Created) {
        state_ = State::Stopped;
        return;
    }
    transition(State::Stopping);
    transition(State::Stopped);
}

}  // namespace core::runtime