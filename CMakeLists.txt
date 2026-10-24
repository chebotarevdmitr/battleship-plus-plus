cmake_minimum_required(VERSION 3.20)
project(BattleshipPlusPlus VERSION 0.1.0 LANGUAGES CXX)

# === Настройки компилятора ===
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # 🔥 Критически важно для clangd в VS Code

# === 🛡️ Кибербезопасность: Санитайзеры для Debug-сборки ===
# AddressSanitizer (ошибки памяти) и UndefinedBehaviorSanitizer (неопределенное поведение)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "🛡️ Enabling AddressSanitizer and UndefinedBehaviorSanitizer")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address,undefined")
endif()

# === Автоматическое подключение vcpkg ===
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    message(STATUS "✅ vcpkg toolchain found: $ENV{VCPKG_ROOT}")
endif()

# === clang-tidy (статический анализ кода) ===
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
if(CLANG_TIDY_EXECUTABLE)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXECUTABLE}
        -checks=-*,bugprone-*,modernize-*,performance-*,readability-*
        -header-filter=.*
    )
    message(STATUS "✅ clang-tidy enabled")
else()
    message(WARNING "⚠️ clang-tidy not found")
endif()

# === Библиотека с основной логикой игры (Этап 1: Coordinate) ===
# Позже мы добавим сюда board.cpp, ship.cpp и т.д.
add_library(battleship_core STATIC
    src/core/Coordinate.cpp
)
target_include_directories(battleship_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# === Тесты (Используем GTest из vcpkg) ===
find_package(GTest CONFIG REQUIRED)
enable_testing()

add_executable(battleship_tests
    tests/test_coordinate.cpp
)
target_link_libraries(battleship_tests PRIVATE
    battleship_core
    GTest::gtest
    GTest::gtest_main
)
# Регистрируем тесты для запуска через ctest
include(GoogleTest)
gtest_discover_tests(battleship_tests)

# === Консольное приложение (пока минимальное) ===
add_executable(battleship_cli
    src/main.cpp
)
target_link_libraries(battleship_cli PRIVATE
    battleship_core
)

message(STATUS "🚢 Battleship++ configured successfully!")