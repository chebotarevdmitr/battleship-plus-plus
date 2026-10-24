#include "core/Coordinate.hpp"

namespace battleship::core {

Coordinate::Coordinate(int x, int y) : x_(x), y_(y) {
    validate(x, y);
}

void Coordinate::validate(int x, int y) {
    // Классическое поле 10x10: индексы строго от 0 до 9
    if (x < 0 || x > 9 || y < 0 || y > 9) {
        throw std::invalid_argument(
            "Координаты должны быть в диапазоне 0-9. Получено: x=" + 
            std::to_string(x) + ", y=" + std::to_string(y)
        );
    }
}

} // namespace battleship::core