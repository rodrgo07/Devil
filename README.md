# Ironclad

C++20 security engineering foundation.

## Build requirements

- LLVM-MinGW toolchain with GNU Make 4.4.1 (`g++`, `mingw32-make`).
- No third-party libraries.

## Build commands

Debug (default):

```
mingw32-make
```

Release:

```
mingw32-make BUILD=release
```

Clean:

```
mingw32-make clean
```

Output lands in `build/debug/` or `build/release/`.

## Test commands

```
mingw32-make test
build/debug/ironclad_tests
```

## Project structure

```
src/app/        entry point and application runner
src/core/       logger, config, runtime
src/platform/   platform-specific code (windows only, isolated)
tests/core/     unit tests (header-only harness)
```

## Architectural dependency direction

```
app
 ↓
runtime
 ↓
config / logger
```

Platform code lives only under `src/platform/windows/` and never leaks into core modules.