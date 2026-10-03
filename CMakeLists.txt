cmake_minimum_required(VERSION 3.20)
project(BattleshipPlusPlus VERSION 0.1.0 LANGUAGES CXX)

# === Настройки компилятора ===
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # Для clangd (автодополнение в VSCode)

# === Автоматическое подключение vcpkg ===
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    message(STATUS "✅ vcpkg toolchain found: $ENV{VCPKG_ROOT}")
endif()

# === clang-tidy (статический анализ) ===
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

# === Библиотека с основной логикой игры ===
add_library(battleship_core STATIC
    src/core/board.cpp
)
target_include_directories(battleship_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# === Тесты ===
find_package(GTest CONFIG REQUIRED)
enable_testing()

add_executable(battleship_tests
    tests/test_board.cpp
)
target_link_libraries(battleship_tests PRIVATE
    battleship_core
    GTest::gtest
    GTest::gtest_main
)
add_test(NAME BattleshipTests COMMAND battleship_tests)

# === Консольное приложение ===
add_executable(battleship_cli
    src/main.cpp
)
target_link_libraries(battleship_cli PRIVATE
    battleship_core
)

message(STATUS "🚢 Battleship++ configured successfully!")
