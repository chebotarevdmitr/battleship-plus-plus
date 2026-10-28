#pragma once

#include <stdexcept>
#include <string>

namespace battleship::core {
     
constexpr int BOARD_SIZE = 10;
constexpr int MIN_COORDINATE = 0;
constexpr int MAX_COORDINATE = BOARD_SIZE - 1; 

class Coordinate {
public:
    Coordinate() = delete; 

    Coordinate(int coord_x, int coord_y);

    // Современный синтаксис с trailing return type (auto ... -> type)
    [[nodiscard]] auto getX() const noexcept -> int { return x_; }
    [[nodiscard]] auto getY() const noexcept -> int { return y_; }

    [[nodiscard]] auto operator==(const Coordinate& other) const noexcept -> bool {
        return x_ == other.x_ && y_ == other.y_;
    }
  
    [[nodiscard]] auto operator!=(const Coordinate& other) const noexcept -> bool {
        return !(*this == other);
    }

private:
    int x_{0};
    int y_{0};
   
    // Переименовали параметры для удовлетворения readability-identifier-length
    static void validate(int coord_x, int coord_y);
};
} 