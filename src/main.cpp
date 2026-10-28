#include <iostream>
#include "core/Coordinate.hpp"

// Trailing return type для main (удовлетворяет clang-tidy)
auto main() -> int {
    std::cout << "🚢 Battleship++ Console Version is starting...\n\n";
    
    try {
        constexpr int test_x = 5;
        constexpr int test_y = 5;
        battleship::core::Coordinate coord(test_x, test_y);
        std::cout << "✅ Coordinate created successfully at (" 
                  << coord.getX() << ", " << coord.getY() << ")\n";
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << "\n";
    }

    std::cout << "\n🧪 Testing invalid coordinates...\n";
    try {
        // NOLINTBEGIN(readability-magic-numbers)
        battleship::core::Coordinate bad_coord(15, 5); 
        // NOLINTEND(readability-magic-numbers)
        std::cout << "❌ This should not be printed!\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "✅ Exception caught correctly: " << e.what() << "\n";
    }

    return 0;
}