# Быстрый старт

## За 5 минут до первого окна

### 1. Установите SFML

**macOS:**
```bash
brew install sfml
```

**Linux:**
```bash
sudo apt-get install libsfml-dev
```

**Windows:**

**Быстрый способ (готовые бинарники):**
1. Скачайте SFML с https://www.sfml-dev.org/download.php
   - Выберите версию для вашего компилятора (Visual Studio 2022 или MinGW)
2. Распакуйте в `C:\SFML`
3. Установите переменную окружения (опционально):
   ```cmd
   set SFML_ROOT=C:\SFML
   ```

**Или через vcpkg (если установлен):**
```cmd
vcpkg install sfml:x64-windows
```

### 2. Перейдите в пример 1

**macOS/Linux:**
```bash
cd example1-basic-window
mkdir build
cd build
cmake ..
make
./Example1_BasicWindow
```

**Windows (Visual Studio):**
```cmd
cd example1-basic-window
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
copy C:\SFML\bin\*.dll Release\
Release\Example1_BasicWindow.exe
```

**Windows (MinGW):**
```cmd
cd example1-basic-window
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
copy C:\SFML\bin\*.dll .
Example1_BasicWindow.exe
```

### 3. Готово! 🎉

Вы должны увидеть окно с темно-синим фоном. Закройте его или нажмите ESC.

## Что дальше?

1. **Пример 1** (10 мин) - Базовое окно и события
2. **Пример 2** (20 мин) - Текстуры и спрайты  
3. **Пример 3** (20 мин) - Интерактивные кнопки

Начните с [README.md](README.md) для полного руководства.

## Проблемы?

### SFML не найден

**macOS/Linux:**
```bash
# Укажите путь явно
cmake -DCMAKE_PREFIX_PATH=/opt/homebrew ..
```

**Windows:**
```cmd
# Укажите путь явно
cmake .. -DCMAKE_PREFIX_PATH=C:/SFML

# Или установите переменную окружения
set SFML_ROOT=C:\SFML
cmake ..
```

### DLL не найдены (Windows)

Скопируйте DLL файлы из `C:\SFML\bin` в папку с исполняемым файлом:
```cmd
copy C:\SFML\bin\*.dll Release\
```

### Ошибки компиляции
Убедитесь, что используете SFML 3.0 синтаксис (см. README.md)

### Изображения не загружаются
Проверьте пути к файлам относительно исполняемого файла
