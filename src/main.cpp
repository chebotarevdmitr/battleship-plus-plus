#include <iostream>
#include "../include/core/Coordinate.hpp"

int main() {
    std::cout << "🚢 Battleship++ Console Version is starting...\n";
    
    // Небольшая проверка, что наш класс работает
    try {
        battleship::core::Coordinate coord(5, 5);
        std::cout << "✅ Coordinate created successfully at (" 
                  << coord.getX() << ", " << coord.getY() << ")\n";
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << "\n";
    }

    return 0;
}