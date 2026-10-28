#include "core/Coordinate.hpp"
#include <stdexcept>
#include <string>

namespace battleship::core {

void Coordinate::validate(int coord_x, int coord_y) {
    if (coord_x < MIN_COORDINATE || coord_x > MAX_COORDINATE ||
        coord_y < MIN_COORDINATE || coord_y > MAX_COORDINATE) {
        throw std::invalid_argument(
            "Координаты должны быть в диапазоне от " +
            std::to_string(MIN_COORDINATE) + " до " +
            std::to_string(MAX_COORDINATE) +
            ". Получено: (" + std::to_string(coord_x) + ", " + std::to_string(coord_y) + ")");
    }
}

Coordinate::Coordinate(int coord_x, int coord_y) : x_(coord_x), y_(coord_y) {
    validate(x_, y_);
}

}  // namespace battleship::core