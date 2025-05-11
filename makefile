# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -Itest/include

# Папки
SRC_DIR = src
TEST_SRC_DIR = test/src
BIN_DIR = bin
TEST_BIN_DIR = test/bin
INC_DIR = include

# Основные исходники и объектные файлы
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)
# Все объектные файлы без main.o
OBJS_NO_MAIN = $(filter-out $(BIN_DIR)/main.o, $(OBJS))


# Тестовые исходники и объектные файлы
TEST_SRCS = $(wildcard $(TEST_SRC_DIR)/*.c)
TEST_OBJS = $(TEST_SRCS:$(TEST_SRC_DIR)/%.c=$(TEST_BIN_DIR)/%.o)

# Цели
TARGET = $(BIN_DIR)/main.exe
TEST_TARGET = $(TEST_BIN_DIR)/test.exe

# Сборка основной программы
all: $(TARGET)

# Линковка основной программы
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Компиляция исходников
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция тестов
$(TEST_BIN_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	@mkdir -p $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Сборка и запуск тестов
test: $(OBJS_NO_MAIN) $(TEST_OBJS)
	@mkdir -p $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $^ -lm
	./$(TEST_TARGET)


# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Очистка
clean:
	$(RM) $(BIN_DIR)/*.o
	$(RM) $(TARGET)
	$(RM) $(TEST_BIN_DIR)/*.o
	$(RM) $(TEST_TARGET)

.PHONY: all clean run test
