#include <gtest/gtest.h>
#include "../include/core/Coordinate.hpp"

namespace battleship::core {

// Тест успешного создания корректных координат
TEST(CoordinateTest, ValidCoordinates) {
    Coordinate coord(0, 0);
    EXPECT_EQ(coord.getX(), 0);
    EXPECT_EQ(coord.getY(), 0);

    Coordinate max_coord(9, 9);
    EXPECT_EQ(max_coord.getX(), 9);
    EXPECT_EQ(max_coord.getY(), 9);
}

// Тест на выброс исключения при неверных координатах
TEST(CoordinateTest, InvalidCoordinatesThrowException) {
    // EXPECT_THROW проверяет, что код действительно выбрасывает ожидаемое исключение
    EXPECT_THROW(Coordinate(-1, 5), std::invalid_argument);
    EXPECT_THROW(Coordinate(5, 10), std::invalid_argument);
    EXPECT_THROW(Coordinate(15, 15), std::invalid_argument);
}

} // namespace battleship::core