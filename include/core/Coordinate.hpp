#pragma once

#include <stdexcept>
#include <string>

namespace battleship::core {
     
// Константы для размера поля (отличный подход для избавления от магических чисел!)
constexpr int BOARD_SIZE = 10;
constexpr int MIN_COORDINATE = 0;
constexpr int MAX_COORDINATE = BOARD_SIZE - 1; 

/**
 * @brief Класс для представления координат на игровом поле.
 */
class Coordinate {
public:
    // Явно удаляем конструктор по умолчанию, чтобы запретить создание объекта без координат
    Coordinate() = delete; 

    /**
     * @brief Конструктор с проверкой границ.
     * @param coord_x Координата по горизонтали
     * @param coord_y Координата по вертикали
     * @throws std::invalid_argument если координаты выходят за пределы поля
     */
    Coordinate(int coord_x, int coord_y);

    // Для простых типов (int, bool) явный возврат читается легче, чем trailing return type (auto ->)
    [[nodiscard]] int getX() const noexcept { return x_; }
    [[nodiscard]] int getY() const noexcept { return y_; }

    // Оператор сравнения на равенство
    [[nodiscard]] bool operator==(const Coordinate& other) const noexcept {
        return x_ == other.x_ && y_ == other.y_;
    }
  
    // Хорошая практика: если есть operator==, стоит добавить и operator!=
    [[nodiscard]] bool operator!=(const Coordinate& other) const noexcept {
        return !(*this == other);
    }

private:
    int x_{0};
    int y_{0};
   
    // Приватный статический метод для валидации, чтобы не перегружать конструктор
    static void validate(int x, int y);
};
} 