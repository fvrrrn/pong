CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 

BUILD_DIR = build

default: clean format analyze all run | $(BUILD_DIR)

all: $(BUILD_DIR)/pong_42 

pong_42: $(BUILD_DIR)/pong_42 | $(BUILD_DIR)

$(BUILD_DIR)/pong_42: src/pong_42.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(BUILD_DIR)/pong*

$(BUILD_DIR):
	mkdir -p build

format:
	find . -name "*.c" -o -name "*.h" | xargs clang-format -i

analyze:
	find . -name "*.c" -o -name "*.h" | xargs cppcheck --enable=all --suppress=missingIncludeSystem

.PHONY: pong_42 
