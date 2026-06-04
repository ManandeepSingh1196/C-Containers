CC = gcc

BUILD_DIR = build

CFLAGS = \
	-Wall \
	-Wextra \
	-Wpedantic \
	-O0 \
	-g \
	-std=c11 \
	-fsanitize=address,undefined

TARGET = $(BUILD_DIR)/main
TEST_TARGET = $(BUILD_DIR)/tests

all: main

main: src/main.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) src/main.c

run: main
	./$(TARGET)

test: \
	tests/test_runner.c \
	tests/test_linked_list.c \
	tests/test_vector.c \
	tests/test_stack.c \
	tests/test_queue.c

	mkdir -p $(BUILD_DIR)

	$(CC) $(CFLAGS) \
		tests/test_runner.c \
		tests/test_linked_list.c \
		tests/test_vector.c \
		tests/test_stack.c \
		tests/test_queue.c \
		-o $(TEST_TARGET)

	./$(TEST_TARGET)

valgrind:
	$(CC) \
		-Wall \
		-Wextra \
		-Wpedantic \
		-O0 \
		-g \
		-std=c11 \
		tests/test_runner.c \
		tests/test_linked_list.c \
		tests/test_vector.c \
		tests/test_stack.c \
		tests/test_queue.c \
		-o $(TEST_TARGET)_vg

	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		./$(TEST_TARGET)_vg

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run test valgrind clean
