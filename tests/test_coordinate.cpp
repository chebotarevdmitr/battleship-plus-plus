#include <gtest/gtest.h>
#include "core/Coordinate.hpp"

namespace battleship::core {

// 1. Тест успешного создания корректных координат (включая граничные значения)
TEST(CoordinateTest, ValidCoordinates) {
    // Нижняя граница
    Coordinate coord_min(0, 0);
    EXPECT_EQ(coord_min.getX(), 0);
    EXPECT_EQ(coord_min.getY(), 0);

    // Верхняя граница
    Coordinate coord_max(9, 9);
    EXPECT_EQ(coord_max.getX(), 9);
    EXPECT_EQ(coord_max.getY(), 9);
    
    // Середина поля
    Coordinate coord_mid(4, 7);
    EXPECT_EQ(coord_mid.getX(), 4);
    EXPECT_EQ(coord_mid.getY(), 7);
}

// 2. Тест на выброс исключения при неверных координатах
TEST(CoordinateTest, InvalidCoordinatesThrowException) {
    // Выход за нижнюю границу
    EXPECT_THROW(Coordinate(-1, 5), std::invalid_argument);
    EXPECT_THROW(Coordinate(5, -10), std::invalid_argument);
    
    // Выход за верхнюю границу
    EXPECT_THROW(Coordinate(5, 10), std::invalid_argument);
    EXPECT_THROW(Coordinate(15, 15), std::invalid_argument);
}

// 3. Тест операторов сравнения (новое дополнение)
TEST(CoordinateTest, EqualityOperators) {
    Coordinate coord1(3, 4);
    Coordinate coord2(3, 4);
    Coordinate coord3(3, 5);

    // Проверяем operator==
    EXPECT_TRUE(coord1 == coord2);
    EXPECT_FALSE(coord1 == coord3);

    // Проверяем operator!=
    EXPECT_FALSE(coord1 != coord2);
    EXPECT_TRUE(coord1 != coord3);
}

}  // namespace battleship::core