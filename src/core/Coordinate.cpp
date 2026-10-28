#include "core/Coordinate.hpp"
#include <stdexcept>
#include <string>

namespace battleship::core {

// Реализация метода валидации
void Coordinate::validate(int x, int y) {
    if (x < MIN_COORDINATE || x > MAX_COORDINATE ||
        y < MIN_COORDINATE || y > MAX_COORDINATE) {
        // Добавил в сообщение фактические полученные значения для удобства отладки
        throw std::invalid_argument(
            "Координаты должны быть в диапазоне от " +
            std::to_string(MIN_COORDINATE) + " до " +
            std::to_string(MAX_COORDINATE) +
            ". Получено: (" + std::to_string(x) + ", " + std::to_string(y) + ")");
    }
}

Coordinate::Coordinate(int coord_x, int coord_y) : x_(coord_x), y_(coord_y) {
    // Вызываем валидацию после инициализации полей.
    // Если координаты некорректны, будет выброшено исключение, и объект не будет создан.
    validate(x_, y_);
}

}  // namespace battleship::core