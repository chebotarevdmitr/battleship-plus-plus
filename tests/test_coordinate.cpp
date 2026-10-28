#include <gtest/gtest.h>
#include "core/Coordinate.hpp"

namespace battleship::core {

TEST(CoordinateTest, ValidCoordinates) {
    // Используем константы вместо магических чисел
    Coordinate coord_min(MIN_COORDINATE, MIN_COORDINATE);
    EXPECT_EQ(coord_min.getX(), MIN_COORDINATE);
    EXPECT_EQ(coord_min.getY(), MIN_COORDINATE);

    Coordinate coord_max(MAX_COORDINATE, MAX_COORDINATE);
    EXPECT_EQ(coord_max.getX(), MAX_COORDINATE);
    EXPECT_EQ(coord_max.getY(), MAX_COORDINATE);
    
    constexpr int mid_x = 4;
    constexpr int mid_y = 7;
    Coordinate coord_mid(mid_x, mid_y);
    EXPECT_EQ(coord_mid.getX(), mid_x);
    EXPECT_EQ(coord_mid.getY(), mid_y);
}

TEST(CoordinateTest, InvalidCoordinatesThrowException) {
    // NOLINTBEGIN(readability-magic-numbers)
    // Здесь магические числа намеренны: мы тестируем реакцию на некорректные данные
    EXPECT_THROW(Coordinate(-1, 5), std::invalid_argument);
    EXPECT_THROW(Coordinate(5, 10), std::invalid_argument);
    EXPECT_THROW(Coordinate(15, 15), std::invalid_argument);
    // NOLINTEND(readability-magic-numbers)
}

TEST(CoordinateTest, EqualityOperators) {
    Coordinate coord1(3, 4);
    Coordinate coord2(3, 4);
    constexpr int diff_y = 5;
    Coordinate coord3(3, diff_y);

    EXPECT_TRUE(coord1 == coord2);
    EXPECT_FALSE(coord1 == coord3);

    EXPECT_FALSE(coord1 != coord2);
    EXPECT_TRUE(coord1 != coord3);
}

}  // namespace battleship::core