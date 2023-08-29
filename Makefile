SRC := $(shell find src -name "*.c" -or -name "*.h")

format:
	clang-format -i -style=file $(SRC)