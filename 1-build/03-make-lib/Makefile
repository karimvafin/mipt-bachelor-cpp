# Компилятор C++.
CXX := g++
# Архиватор для статических библиотек.
AR := ar
# Флаги компиляции: стандарт, оптимизация, предупреждения.
CXXFLAGS := -std=c++20 -O2 -Wall -Wextra -pedantic
# Флаги препроцессора: путь к заголовкам.
CPPFLAGS := -Iinclude
# Каталог для объектных файлов.
BUILD_DIR := build
# Путь к статической библиотеке.
LIB := $(BUILD_DIR)/libcalc.a
# Путь к итоговому бинарнику.
TARGET := bin/app

# Исходники библиотеки.
LIB_SRCS := src/calc/calc.cpp
# Исходники приложения.
APP_SRCS := src/main.cpp
# Объекты библиотеки.
LIB_OBJS := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(LIB_SRCS))
# Объекты приложения.
APP_OBJS := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(APP_SRCS))

# Линковка приложения с библиотекой.
$(TARGET): $(LIB) $(APP_OBJS)
	# Создание директории для бинарника.
	@mkdir -p $(dir $@)
	# Линковка приложения с libcalc.a.
	$(CXX) $(CXXFLAGS) -o $@ $(APP_OBJS) $(LIB)

# Сборка статической библиотеки из объектов.
$(LIB): $(LIB_OBJS)
	# Создание директории для библиотеки.
	@mkdir -p $(dir $@)
	# Архивация объектных файлов в .a.
	$(AR) rcs $@ $^

# Шаблонное правило компиляции исходников в build/*.o.
$(BUILD_DIR)/%.o: src/%.cpp
	# Создание директории для объекта.
	@mkdir -p $(dir $@)
	# Компиляция одного исходника в объектный файл.
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

# Объявление фиктивных целей.
.PHONY: run clean
# Запуск собранной программы.
run: $(TARGET)
	# Запуск бинарника.
	./$(TARGET)

# Очистка артефактов сборки.
clean:
	# Удаление build/ и bin/ с артефактами.
	rm -rf $(BUILD_DIR) bin
