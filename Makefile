SRC := $(shell find src -name "*.c" -or -name "*.h")
BENCHMARKS := $(shell find benchmarks -name "*.c" -or -name "*.h")
TESTS := $(shell find tests -name "*.c" -or -name "*.h")

format:
	clang-format -i -style=file $(SRC) $(BENCHMARKS) $(TESTS)