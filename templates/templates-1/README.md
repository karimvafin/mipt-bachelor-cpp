# Шаблоны (`templates-1`)

Этот каталог содержит вводные примеры по шаблонам в C++: сначала мотивация, затем шаблоны функций, шаблоны классов и отдельный минимальный пример шаблонного класса, вынесенного в `.h` / `.cpp`.

---

## Файлы в папке

### `00-problem.cpp` — зачем вообще нужны шаблоны

Показывает проблему дублирования кода без шаблонов:

- отдельные перегрузки `max` для `int`, `double`, `std::string`;
- ещё одна отдельная перегрузка для `MyStruct`;
- один и тот же алгоритм приходится переписывать для каждого типа.

Идея файла: шаблоны позволяют заменить такой набор почти одинаковых функций одной обобщённой реализацией.

### `01-function-templates.cpp` — шаблоны функций

Файл демонстрирует:

- объявление шаблона функции: `template <typename T>`;
- вывод типа `T` из аргументов функции;
- шаблоны с несколькими параметрами типа;
- передачу параметров через `T`, `T&`, `const T&`;
- случаи, где тип нужно указать явно: `my_max<double>(1, 2.5)`;
- нетиповые параметры шаблона: `template <std::size_t N, typename T, std::size_t Size>`;
- перегрузку шаблонных и нешаблонных функций;
- явную инстанциацию:
  `template int my_max<int>(int, int);`

Примеры из файла:

- `my_max<T>(T a, T b)` — простой шаблон функции;
- `print_pair<T, U>(const T&, const U&)` — два параметра типа;
- `my_swap(T& a, T& b)` — ссылка нужна, чтобы реально менять аргументы;
- `describe(const T&)` и `describe(const char*)` — перегрузки шаблонной и обычной функции.

### `02-class-templates.cpp` — шаблоны классов

Файл демонстрирует:

- шаблонный класс `Stack<T>`;
- шаблонный класс `Pair<T, U>`;
- шаблонный класс `Array<T, N>` с нетиповым параметром;
- определение методов шаблонного класса вне тела класса;
- частичную специализацию `Array<bool, N>`;
- исключения в шаблонных контейнерах (`std::underflow_error`, `std::out_of_range`).

Примеры из файла:

- `Stack<T>` хранит элементы в динамическом массиве и умеет `push`, `pop`, `top`;
- `Pair<T, U>` показывает класс с двумя параметрами типа;
- `Array<T, N>` показывает, что размер можно передать как параметр шаблона;
- `Array<bool, N>` печатает `true` / `false` вместо `1` / `0`.

### `Template.h`, `Template.cpp`, `main.cpp` — минимальный пример шаблонного класса

Эти три файла показывают простейший шаблонный класс:

- `Template.h` содержит объявление `Template<T>`;
- `Template.cpp` содержит определения конструктора и метода `print()`;
- `main.cpp` создаёт `Template<int>` и вызывает `print()`.

Этот пример полезен как иллюстрация, но у него есть важная особенность: шаблоны обычно нельзя бездумно выносить в `.cpp`, потому что код для конкретного типа генерируется только при инстанциации.

---

## Где писать `T`, `T&`, `const T&`

Эта тема напрямую встречается в `01-function-templates.cpp` и `02-class-templates.cpp`.

### `T`

```cpp
template <typename T>
void f(T x);
```

Используется, когда:

- нужна передача по значению;
- функция работает с копией;
- тип маленький и дешёвый в копировании.

Примеры в этой папке:

- `my_max(T a, T b)` в `01-function-templates.cpp`;
- `add(T a, T b)` в `01-function-templates.cpp`.

### `T&`

```cpp
template <typename T>
void f(T& x);
```

Используется, когда:

- нужно изменить аргумент;
- функция должна работать с исходным объектом без копии.

Примеры в этой папке:

- `my_swap(T& a, T& b)` в `01-function-templates.cpp`;
- `T& Array<T, N>::operator[](int index)` в `02-class-templates.cpp`.

### `const T&`

```cpp
template <typename T>
void f(const T& x);
```

Используется, когда:

- копировать объект не хочется;
- объект менять не нужно;
- нужно принимать и обычные объекты, и временные значения.

Примеры в этой папке:

- `print_pair(const T& first, const U& second)` в `01-function-templates.cpp`;
- `describe(const T& value)` в `01-function-templates.cpp`;
- `void Stack<T>::push(const T& value)` в `02-class-templates.cpp`;
- `const T& Stack<T>::top() const` в `02-class-templates.cpp`.

Короткое практическое правило:

- `T` — маленький тип или нужна копия;
- `T&` — нужно менять аргумент;
- `const T&` — объект большой, копировать дорого, менять не нужно.

---

## Почему шаблоны обычно держат в заголовках

Это объясняется прямо в `02-class-templates.cpp`.

Шаблон сам по себе не создаёт машинный код. Код появляется только тогда, когда компилятор видит конкретную инстанциацию, например:

```cpp
Stack<int> s;
```

Поэтому определения шаблонов обычно кладут в `.h` / `.hpp`, чтобы компилятор видел их в месте использования.

Из-за этого пример с `Template.h` и `Template.cpp` стоит воспринимать как учебный: в реальном коде определения методов шаблонного класса чаще всего тоже помещают в заголовочный файл.

---

## Команды компиляции

```bash
g++ -std=c++17 -Wall -Wextra -o 00-problem            00-problem.cpp
g++ -std=c++17 -Wall -Wextra -o 01-function-templates 01-function-templates.cpp
g++ -std=c++17 -Wall -Wextra -o 02-class-templates    02-class-templates.cpp
```

Для минимального примера с `Template<T>` будут проблемы линковки, если оставлять определения шаблона только в `Template.cpp`. Это и есть одна из причин, почему шаблоны обычно реализуют в заголовочных файлах.

---

## Практические задания

### 1. Обобщённая функция `my_min`

Напишите шаблонную функцию:

```cpp
template <typename T>
T my_min(T a, T b);
```

Требования:

- функция должна возвращать меньший из двух аргументов;
- проверьте её на `int`, `double` и `std::string`;
- отдельно попробуйте вызвать её с аргументами разных типов, например `my_min(1, 2.5)`, и объясните, почему в таком случае может понадобиться явное указание типа шаблона.

### 2. Шаблонный `swap` и выбор между `T` и `T&`

Реализуйте две функции:

```cpp
template <typename T>
void swap_by_value(T a, T b);

template <typename T>
void swap_by_reference(T& a, T& b);
```

Требования:

- сравните поведение этих функций на `int`;
- покажите, почему `swap_by_value` не меняет переменные снаружи;
- объясните, почему для настоящего обмена нужен именно `T&`.

### 3. Шаблонный класс `Box<T>`

Реализуйте класс:

```cpp
template <typename T>
class Box {
public:
    explicit Box(const T& value);
    void set(const T& value);
    const T& get() const;
    void print() const;
};
```

Требования:

- класс должен хранить один объект типа `T`;
- метод `get()` должен возвращать `const T&`;
- проверьте класс на `int`, `double` и `std::string`;
- попробуйте сначала вынести определения методов в `.cpp`, а потом объясните, почему для шаблонов такой способ обычно неудобен.

### 4. Массив фиксированного размера `FixedArray<T, N>`

Реализуйте упрощённый шаблонный массив:

```cpp
template <typename T, int N>
class FixedArray {
public:
    T& operator[](int index);
    const T& operator[](int index) const;
    int size() const;
    void fill(const T& value);
};
```

Требования:

- `N` должен быть нетиповым параметром шаблона;
- добавьте проверку выхода за границы и выбрасывайте `std::out_of_range`;
- проверьте класс на `FixedArray<int, 5>` и `FixedArray<std::string, 3>`;
- сравните свою реализацию с `Array<T, N>` из `02-class-templates.cpp`.

### 5. Шаблонный кольцевой буфер `CircularBuffer<T, N>` (нужен `FixedArray<T, N>`)
Ссылка: https://ru.wikipedia.org/wiki/%D0%9A%D0%BE%D0%BB%D1%8C%D1%86%D0%B5%D0%B2%D0%BE%D0%B9_%D0%B1%D1%83%D1%84%D0%B5%D1%80

Реализуйте кольцевой буфер:

```cpp
template <typename T, int N>
class CircularBuffer {
public:
    void push(const T& value);
    void pop();
    const T& front() const;
    const T& back() const;
    bool empty() const;
    bool full() const;
    int size() const;
};
```

Требования:

- `N` должен быть нетиповым параметром шаблона;
- используйте внутренний массив фиксированного размера, а не `std::vector`;
- при `push()` в полный буфер и при `pop()` / `front()` / `back()` из пустого буфера выбрасывайте исключение;
- проверьте реализацию на `int` и `std::string`;

### 6. Шаблонный контейнер `StaticStack<T, N>` (нужен `FixedArray<T, N>`)

Реализуйте стек с фиксированной вместимостью:

```cpp
template <typename T, int N>
class StaticStack {
public:
    void push(const T& value);
    void pop();
    const T& top() const;
    bool empty() const;
    bool full() const;
    int size() const;
};
```

Требования:

- используйте `FixedArray<T, N>`;
- при переполнении выбрасывайте `std::overflow_error`;
- при обращении к пустому стеку выбрасывайте `std::underflow_error`;
- проверьте реализацию на нескольких типах;
- сравните `StaticStack<T, N>` с динамическим `Stack<T>` из `02-class-templates.cpp`: в чём плюсы и минусы фиксированного размера?

### 7. Собственная очередь `SimpleQueue<T>` на сыром массиве с правилом пяти

Реализуйте шаблонную очередь:

```cpp
template <typename T>
class SimpleQueue {
public:
    SimpleQueue();
    ~SimpleQueue();
    SimpleQueue(const SimpleQueue& other);
    SimpleQueue(SimpleQueue&& other);
    SimpleQueue& operator=(const SimpleQueue& other);
    SimpleQueue& operator=(SimpleQueue&& other);

    void push(const T& value);
    void pop();
    const T& front() const;
    bool empty() const;
};
```

Требования:

- нужно использовать динамический массив внутри (RAII);
- при `pop()` и `front()` на пустой очереди выбрасывайте `std::underflow_error`;
- проверьте очередь на `int` и `std::string`;
- реализуйте правило пяти
