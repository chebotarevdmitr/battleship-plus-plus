# 🎮 Battleship++ — Дневник разработки

Здесь я записываю свои шаги, наблюдения и пояснения по проекту.

---

## 📅 2026-10-29: Этап 1 — Класс `Coordinate` и инфраструктура сборки

### ✅ Что сделано

- [x] Создан класс `battleship::core::Coordinate` с валидацией координат
- [x] Настроен `CMakeLists.txt` с поддержкой C++20, vcpkg, санитайзеров и clang-tidy
- [x] Подключена библиотека Google Test через vcpkg
- [x] Написаны модульные тесты для класса `Coordinate` (3 тест-кейса)
- [x] Исправлены все предупреждения clang-tidy (trailing return type, magic numbers, identifier length)
- [x] Добавлены операторы сравнения `==` и `!=`
- [x] Запрещён конструктор по умолчанию через `= delete`
- [x] Код закоммичен и отправлен на GitHub

battleship-plus-plus on 🌿 main [*4] 🔺 v4.2.3 🚀 v15.2.0 🕙 23:21:21
❯ mkdir -p build && cd build
mkdir: created directory 'build'

battleship-plus-plus/build on 🌿 main [*4] 🕙 23:23:08
❯ cmake .. -DCMAKE_BUILD_TYPE=Debug
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- ⚠️ Режим Debug: предупреждения компилятора будут считаться ошибками (-Werror)
-- 🛡️ Enabling AddressSanitizer and UndefinedBehaviorSanitizer
-- ✅ vcpkg toolchain found: /home/dmitriy/vcpkg
-- ✅ clang-tidy enabled
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- 🚢 Battleship++ configured successfully!
-- 💡 Подсказка: Для сборки используй: cmake --build build --config Debug
-- Configuring done (0.5s)
-- Generating done (0.0s)
-- Build files have been written to: /home/dmitriy/cpp_project/battleship-plus-plus/build

battleship-plus-plus/build on 🌿 main [*4] 🔺 v4.2.3 🚀 v15.2.0 🕙 23:23:40
❯ make
[ 16%] Building CXX object CMakeFiles/battleship_core.dir/src/core/Coordinate.cpp.o
[ 33%] Linking CXX static library libbattleship_core.a
[ 33%] Built target battleship_core
[ 50%] Building CXX object CMakeFiles/battleship_tests.dir/tests/test_coordinate.cpp.o
[ 66%] Linking CXX executable battleship_tests
[ 66%] Built target battleship_tests
[ 83%] Building CXX object CMakeFiles/battleship_cli.dir/src/main.cpp.o
[100%] Linking CXX executable battleship_cli
[100%] Built target battleship_cli

battleship-plus-plus/build on 🌿 main [*4] 🔺 v4.2.3 🚀 v15.2.0 🕙 23:24:29
❯ ctest --output-on-failure
Test project /home/dmitriy/cpp_project/battleship-plus-plus/build
    Start 1: CoordinateTest.ValidCoordinates
1/3 Test #1: CoordinateTest.ValidCoordinates ...................   Passed    0.02 sec
    Start 2: CoordinateTest.InvalidCoordinatesThrowException
2/3 Test #2: CoordinateTest.InvalidCoordinatesThrowException ...   Passed    0.02 sec
    Start 3: CoordinateTest.EqualityOperators
3/3 Test #3: CoordinateTest.EqualityOperators ..................   Passed    0.02 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =   0.07 sec

battleship-plus-plus/build on 🌿 main [*4] 🔺 v4.2.3 🚀 v15.2.0 🕙 23:25:00
❯ ./battleship_tests
Running main() from ./googletest/src/gtest_main.cc
[==========] Running 3 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 3 tests from CoordinateTest
[ RUN      ] CoordinateTest.ValidCoordinates
[       OK ] CoordinateTest.ValidCoordinates (0 ms)
[ RUN      ] CoordinateTest.InvalidCoordinatesThrowException
[       OK ] CoordinateTest.InvalidCoordinatesThrowException (0 ms)
[ RUN      ] CoordinateTest.EqualityOperators
[       OK ] CoordinateTest.EqualityOperators (0 ms)
[----------] 3 tests from CoordinateTest (1 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (1 ms total)
[  PASSED  ] 3 tests.

battleship-plus-plus/build on 🌿 main [*4] 🔺 v4.2.3 🚀 v15.2.0 🕙 23:25:40
❯ ./battleship
zsh: no such file or directory: ./battleship

battleship-plus-plus/build on 🌿 main [*4] 🔺 v4.2.3 🚀 v15.2.0 🕙 23:26:10
❯ ./battleship_cli
🚢 Battleship++ Console Version is starting...

✅ Coordinate created successfully at (5, 5)

🧪 Testing invalid coordinates...
✅ Exception caught correctly: Координаты должны быть в диапазоне от 0 до 9. Получено: (15, 5)

battleship-plus-plus/build on 🌿 main [*4] 🔺 v4.2.3 🚀 v15.2.0 🕙 23:26:59
❯

battleship-plus-plus/build on 🌿 main 🔺 v4.2.3 🚀 v15.2.0 🕙 23:31:42

### 🎯 План на следующий этап

- [ ] Реализовать класс `Ship` (корабль) — размер, координаты, состояние
- [ ] Реализовать класс `Board` (игровое поле 10×10)
- [ ] Добавить логику размещения кораблей с проверкой пересечений
- [ ] Реализовать логику обработки выстрелов (попадание/промах/убил)
- [ ] Создать класс `Game` для управления игровым процессом
- [ ] Начать работу над консольным интерфейсом (CLI)

### 💡 Заметки и принятые решения

- **Архитектура:** Использую пространство имён `battleship::core` для изоляции логики от UI
- **Структура папок:** `include/` для заголовков, `src/` для реализации, `tests/` для тестов
- **Валидация:** Класс `Coordinate` сам проверяет свои границы — это принцип "fail fast"
- **Тестирование:** Покрываю тестами не только "счастливый путь", но и граничные значения, и исключения
- **Санитайзеры:** В Debug-сборке включены AddressSanitizer и UndefinedBehaviorSanitizer для раннего обнаружения ошибок памяти
- **Строгий режим:** Флаг `-Werror` в Debug заставляет исправлять все предупреждения сразу, не откладывая

### ❓ Вопросы и проблемы текущего этапа

- Как лучше спроектировать класс `Ship`: хранить ли ему список `Coordinate` или достаточно начальной точки + ориентации?
- Нужен ли отдельный класс `Shot` для выстрела или достаточно `Coordinate`?
- Как организовать размещение кораблей: автоматически или с возможностью ручного выбора игроком?

### 📚 Что узнал нового

- **`= delete`** — современный способ запретить конструкторы/операторы в C++
- **`[[nodiscard]]`** — атрибут, заставляющий компилятор предупреждать, если возвращаемое значение проигнорировано
- **`noexcept`** — указание, что функция не выбрасывает исключения; помогает компилятору оптимизировать код
- **Trailing return type** (`auto func() -> int`) — современный синтаксис возврата типа, который требует clang-tidy
- **`NOLINTBEGIN` / `NOLINTEND`** — директивы для точечного отключения предупреждений clang-tidy
- **`add_compile_options` / `add_link_options`** — современный способ добавления флагов в CMake 3.20+
- **Google Test** — фреймворк для модульного тестирования; макросы `EXPECT_EQ`, `EXPECT_THROW`, `TEST`
- **Санитайзеры** — инструменты для поиска ошибок памяти и неопределённого поведения на этапе выполнения

---

## 📅 2026-10-03: Начало проекта

### ✅ Что сделано при создании проекта

- [x] Создана структура папок проекта
- [x] Инициализирован Git-репозиторий
- [x] Настроен `.gitignore`
- [x] Создан этот дневник

### 🎯 Что планирую дальше

- [x] Написать первый модуль (класс `Coordinate`) ← **выполнено 29.10**
- [x] Настроить `CMakeLists.txt` ← **выполнено 29.10**
- [x] Написать первые тесты ← **выполнено 29.10**
- [x] Подключить clang-tidy и clang-format ← **выполнено 29.10**

### 💡 Заметки и идеи

- Использовать паттерн MVC для разделения логики и интерфейса
- Начать с консольной версии, потом перейти к Qt
- Бот должен быть трёх уровней сложности

### ❓ Вопросы и проблемы

- (решено)

### 📚 Что узнал нового при создании проекта

- Основы структуры C++ проекта с CMake
- Как настроить `.gitignore` для C++ проектов
