CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic
LDFLAGS  :=

BUILD_DIR := build

ifeq ($(BUILD),release)
  BUILD_TYPE := release
  CXXFLAGS  += -O2 -DNDEBUG
else
  BUILD_TYPE := debug
  CXXFLAGS  += -O0 -g
endif

SRC := \
  src/app/main.cpp \
  src/app/app.cpp \
  src/core/logger/logger.cpp \
  src/core/config/config.cpp \
  src/core/runtime/runtime.cpp \
  src/platform/windows/console.cpp

TEST_SRC := \
  tests/core/test_main.cpp \
  tests/core/config_test.cpp \
  tests/core/runtime_test.cpp \
  tests/core/logger_test.cpp \
  src/core/logger/logger.cpp \
  src/core/config/config.cpp \
  src/core/runtime/runtime.cpp

APP_OUT  := $(BUILD_DIR)/$(BUILD_TYPE)/ironclad
TEST_OUT := $(BUILD_DIR)/$(BUILD_TYPE)/ironclad_tests

.PHONY: all app test clean

all: app test

app: $(APP_OUT)

test: $(TEST_OUT)

$(APP_OUT): $(SRC)
	@if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	$(CXX) $(CXXFLAGS) -Isrc $(SRC) -o $@ $(LDFLAGS)

$(TEST_OUT): $(TEST_SRC)
	@if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	$(CXX) $(CXXFLAGS) -Itests/core $(TEST_SRC) -o $@ $(LDFLAGS)

clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)