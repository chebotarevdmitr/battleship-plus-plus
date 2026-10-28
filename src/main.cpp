#include <iostream>
#include "core/Coordinate.hpp"

int main() {
    std::cout << "🚢 Battleship++ Console Version is starting...\n\n";
    
    // 1. Проверка корректного создания координат
    try {
        battleship::core::Coordinate coord(5, 5);
        std::cout << "✅ Coordinate created successfully at (" 
                  << coord.getX() << ", " << coord.getY() << ")\n";
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << "\n";
    }

    // 2. Демонстрация работы валидации (попытка создать некорректные координаты)
    std::cout << "\n🧪 Testing invalid coordinates...\n";
    try {
        // 15 выходит за пределы MAX_COORDINATE (9)
        battleship::core::Coordinate bad_coord(15, 5); 
        std::cout << "❌ This should not be printed!\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "✅ Exception caught correctly: " << e.what() << "\n";
    }

    return 0;
}