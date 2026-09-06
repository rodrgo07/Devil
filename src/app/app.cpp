#include "app.hpp"

#include "../core/config/config.hpp"
#include "../core/logger/logger.hpp"
#include "../core/runtime/runtime.hpp"
#include "../platform/windows/console.hpp"

namespace app {

namespace {

using core::config::ConfigLoader;
using core::logger::Logger;
using core::runtime::Runtime;

}  // namespace

int run() {
    platform::windows::prepare_console();

    Logger logger;
    if (!logger.start()) {
        return 1;
    }

    ConfigLoader config;
    if (!config.load()) {
        logger.log(core::logger::Level::Error, "failed to load configuration");
        logger.stop();
        return 1;
    }

    Runtime runtime;
    if (!runtime.initialize()) {
        logger.log(core::logger::Level::Error, "failed to initialize runtime");
        logger.stop();
        return 1;
    }

    if (!runtime.run()) {
        logger.log(core::logger::Level::Error, "failed to run runtime");
        runtime.stop();
        logger.stop();
        return 1;
    }
    logger.log(core::logger::Level::Info, "runtime running");

    if (!runtime.stop()) {
        logger.log(core::logger::Level::Error, "failed to stop runtime");
        logger.stop();
        return 1;
    }
    logger.log(core::logger::Level::Info, "runtime stopped");
    logger.stop();

    return 0;
}

}  // namespace app