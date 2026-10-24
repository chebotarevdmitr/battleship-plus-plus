#pragma once

#include <stdexcept>
#include <string>

namespace battleship::core {

/**
 * @brief Класс для представления координат на игровом поле (10x10).
 * Используем инкапсуляцию: данные скрыты, доступ только через геттеры.
 */
class Coordinate {
public:
    // Конструктор по умолчанию (создаёт невалидную координату -1, -1)
    Coordinate() = default;

    /**
     * @brief Конструктор с проверкой границ.
     * @param x Координата по горизонтали (0-9)
     * @param y Координата по вертикали (0-9)
     * @throws std::invalid_argument если координаты выходят за пределы поля
     */
    Coordinate(int x, int y);

    // [[nodiscard]] подсказывает компилятору предупреждать, если мы забыли использовать результат
    [[nodiscard]] int getX() const noexcept { return x_; }
    [[nodiscard]] int getY() const noexcept { return y_; }

    // Оператор сравнения на равенство (понадобится для тестов и логики)
    [[nodiscard]] bool operator==(const Coordinate& other) const noexcept {
        return x_ == other.x_ && y_ == other.y_;
    }

private:
    int x_{-1}; // Инициализация по умолчанию
    int y_{-1};
    
    // Вспомогательный приватный метод для валидации
    static void validate(int x, int y);
};

} // namespace battleship::core