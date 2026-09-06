cmake_minimum_required(VERSION 3.16)

project(ironclad LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(IRONCLAD_SOURCES
  src/app/main.cpp
  src/app/app.cpp
  src/core/logger/logger.cpp
  src/core/config/config.cpp
  src/core/runtime/runtime.cpp
  src/platform/windows/console.cpp
)

add_executable(ironclad ${IRONCLAD_SOURCES})
target_include_directories(ironclad PRIVATE src)

if(MSVC)
  target_compile_options(ironclad PRIVATE /W4)
else()
  target_compile_options(ironclad PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()

set(IRONCLAD_TEST_SOURCES
  tests/core/test_main.cpp
  tests/core/config_test.cpp
  tests/core/runtime_test.cpp
  tests/core/logger_test.cpp
  src/core/logger/logger.cpp
  src/core/config/config.cpp
  src/core/runtime/runtime.cpp
)

add_executable(ironclad_tests ${IRONCLAD_TEST_SOURCES})
target_include_directories(ironclad_tests PRIVATE tests/core src)
add_test(NAME ironclad_tests COMMAND ironclad_tests)