cmake_minimum_required(VERSION 3.20)
project(BattleshipPlusPlus VERSION 0.1.0 LANGUAGES CXX)

# ==============================================================================
# 1. Настройки компилятора
# ==============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Запрещаем специфичные для компилятора расширения (например, gnu++20)

# 🔥 Критически важно для работы плагина clangd в VS Code (подсветка ошибок, автодополнение)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ==============================================================================
# 2. Гарантированный тип сборки (Build Type)
# ==============================================================================
# Если пользователь забыл указать тип сборки, по умолчанию ставим Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    message(STATUS "🔧 Тип сборки не был указан. Устанавливаем по умолчанию: ${CMAKE_BUILD_TYPE}")
endif()

# ==============================================================================
# 3. Флаги предупреждений компилятора (Строгий режим)
# ==============================================================================
# Включаем основные предупреждения. Это первая линия обороны от ошибок!
add_compile_options(-Wall -Wextra -Wpedantic)

# В режиме Debug превращаем предупреждения в ошибки, чтобы сразу их исправлять,
# а не игнорировать. В Release это можно отключить.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Werror)
    message(STATUS "⚠️ Режим Debug: предупреждения компилятора будут считаться ошибками (-Werror)")
endif()

# ==============================================================================
# 4. 🛡️ Кибербезопасность: Санитайзеры для Debug-сборки
# ==============================================================================
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "🛡️ Enabling AddressSanitizer and UndefinedBehaviorSanitizer")
    # Флаги компиляции
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    # Флаги линковки (обязательно должны совпадать с флагами компиляции для санитайзеров)
    add_link_options(-fsanitize=address,undefined)
endif()

# ==============================================================================
# 5. Автоматическое подключение vcpkg
# ==============================================================================
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    message(STATUS "✅ vcpkg toolchain found: $ENV{VCPKG_ROOT}")
endif()

# ==============================================================================
# 6. clang-tidy (статический анализ кода)
# ==============================================================================
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
if(CLANG_TIDY_EXECUTABLE)
    # Настраиваем проверки. '-*' отключает все, а затем мы включаем нужные группы.
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXECUTABLE}
        -checks=-*,bugprone-*,modernize-*,performance-*,readability-*
        -header-filter=.* # Анализировать и заголовочные файлы
    )
    message(STATUS "✅ clang-tidy enabled")
else()
    message(WARNING "⚠️ clang-tidy not found. Установите его: sudo apt install clang-tidy")
endif()

# ==============================================================================
# 7. Цели сборки (Targets)
# ==============================================================================

# --- A. Библиотека с основной логикой игры ---
add_library(battleship_core STATIC
    src/core/Coordinate.cpp
    # Позже добавишь сюда: src/core/Board.cpp, src/core/Ship.cpp и т.д.
)
# PUBLIC означает, что любой, кто подключит эту библиотеку, автоматически 
# получит доступ к этим заголовочным файлам.
target_include_directories(battleship_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# --- B. Тесты (Используем GTest из vcpkg) ---
find_package(GTest CONFIG REQUIRED)
enable_testing() # Включаем поддержку CTest

add_executable(battleship_tests
    tests/test_coordinate.cpp # Убедись, что имя файла совпадает с реальным!
)
target_link_libraries(battleship_tests PRIVATE
    battleship_core       # Подключаем нашу логику
    GTest::gtest          # Сам фреймворк
    GTest::gtest_main     # Основная функция main() для тестов
)

# Регистрируем тесты для удобного запуска через команду `ctest`
include(GoogleTest)
gtest_discover_tests(battleship_tests)

# --- C. Консольное приложение (CLI) ---
add_executable(battleship_cli
    src/main.cpp
)
target_link_libraries(battleship_cli PRIVATE
    battleship_core
)

# ==============================================================================
# 8. Завершение
# ==============================================================================
message(STATUS "🚢 Battleship++ configured successfully!")
message(STATUS "💡 Подсказка: Для сборки используй: cmake --build build --config Debug")