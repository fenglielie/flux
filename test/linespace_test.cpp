#include "linespace.hpp"

#include "gtest/gtest.h"

using namespace flux;      // NOLINT

TEST(LinespaceTest, IncludeEndTrue) {
    double start = 0.0;
    double end = 10.0;
    size_t num = 5;
    bool include_end = true;
    double step = 0.0;

    std::vector<double> result = linespace(start, end, num, include_end, step);

    ASSERT_EQ(result.size(), num);
    EXPECT_DOUBLE_EQ(step, (end - start) / static_cast<double>(num - 1));

    double expected_value = start;
    for (double value : result) {
        EXPECT_DOUBLE_EQ(value, expected_value);
        expected_value += step;
    }
}

TEST(LinespaceTest, IncludeEndFalse) {
    double start = 0.0;
    double end = 10.0;
    size_t num = 5;
    bool include_end = false;
    double step = 0.0;

    std::vector<double> result = linespace(start, end, num, include_end, step);

    ASSERT_EQ(result.size(), num);
    EXPECT_DOUBLE_EQ(step, (end - start) / static_cast<double>(num));

    double expected_value = start;
    for (double value : result) {
        EXPECT_DOUBLE_EQ(value, expected_value);
        expected_value += step;
    }
}

TEST(LinespaceMidTest, LinespaceMidTest) {
    double start = 0.0;
    double end = 10.0;
    size_t num = 5;
    double step = 0.0;

    std::vector<double> result = linespace_mid(start, end, num, step);

    ASSERT_EQ(result.size(), num);
    EXPECT_DOUBLE_EQ(step, (end - start) / static_cast<double>(num));

    double expected_value = start + (0.5 * step);
    for (double value : result) {
        EXPECT_DOUBLE_EQ(value, expected_value);
        expected_value += step;
    }
}
