# AGENTS.md

## Project

This is a C++ project built through an iterative vibe-coding workflow.

The repository must remain simple, modular, testable, and buildable.

## Core Rules

1. Inspect the existing code before changing it.
2. Never invent files, APIs, variables, dependencies, or behavior.
3. Preserve working behavior unless the task explicitly requires changing it.
4. Prefer the smallest correct implementation.
5. Do not introduce abstractions without a concrete need.
6. Every modification must leave the project buildable.
7. Every bug fix must identify:
   - broken behavior
   - root cause
   - correction
   - regression test
8. Do not silently change architecture.
9. Do not duplicate existing functionality.
10. Remove dead code instead of working around it.

## Workflow

### ANALYZE

Inspect:

- repository tree
- build system
- dependencies
- entry points
- existing modules
- compiler configuration
- tests
- logs/errors

Do not modify code during analysis.

### PLAN

Produce:

- objective
- affected files
- implementation order
- risks
- validation strategy

Keep the plan proportional to the task.

### IMPLEMENT

Implement the smallest complete solution.

Rules:

- follow existing conventions
- keep modules isolated
- avoid unnecessary dependencies
- validate inputs
- handle failures explicitly
- do not leave TODO implementations
- do not leave placeholder code

### TEST

After implementation:

1. Build the project.
2. Run existing tests.
3. Add tests for changed behavior.
4. Test failure paths.
5. Check for regressions.

### DEBUG

For every failure identify:

- exact failure
- reproduction
- root cause
- affected component
- correction
- validation

Never hide errors with suppression.

### REVIEW

Review:

- correctness
- architecture
- memory safety
- concurrency
- error handling
- performance
- security
- dead code
- duplicated logic
- build reproducibility

### FINALIZE

Before finishing:

- build succeeds
- tests pass
- warnings are reviewed
- temporary files are removed
- debug code is removed
- documentation matches implementation
- changed files are listed
- remaining known issues are explicit

## C++ Rules

Prefer:

- C++20
- RAII
- smart pointers where ownership requires them
- `std::expected`-style error handling where appropriate
- `std::string_view` for non-owning string parameters
- `enum class`
- `constexpr`
- `std::span`
- strong types

Avoid:

- raw owning pointers
- global mutable state
- macros when a language feature exists
- unnecessary singletons
- duplicated implementations
- exceptions used as normal control flow

## Build

The project must have one reproducible build path.

The agent must never assume that a build works.

It must actually compile and test after meaningful changes.

## Security Boundary

Security research must remain within authorized laboratory or defensive environments.

Do not implement mechanisms whose primary purpose is bypassing anti-cheat controls, concealing unauthorized software, or evading security detection.

Research detection surfaces through controlled test harnesses instead.

## Communication

Be direct.

Report:

- what changed
- why it changed
- what was tested
- what failed
- what remains

Never claim a test passed without running it.