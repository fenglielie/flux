#include "error_and_order.hpp"

#include <cmath>

#include "gtest/gtest.h"

using namespace flux;  // NOLINT

TEST(ErrorTest, ErrorFunction1) {
    std::vector<double> u1 = {1.3, 2.4, 3.0};
    std::vector<double> u2 = {1.5, 2.5, 3.5};
    double dx = 0.1;

    double result_0 = error(u1, u2, dx, ErrorType::Linf);
    EXPECT_NEAR(result_0, 0.5, 1e-8);

    double result_1 = error(u1, u2, dx, ErrorType::L1);
    EXPECT_NEAR(result_1, 0.08, 1e-8);

    double result_2 = error(u1, u2, dx, ErrorType::L2);
    EXPECT_NEAR(result_2, std::sqrt(0.03), 1e-8);
}

TEST(ErrorTest, ErrorFunction2) {
    std::vector<double> u1 = {1.3, 2.4, 3.0};
    std::vector<double> u2 = {1.5, 2.5, 3.5};
    double dx = 0.1;

    auto error_code = ::testing::ExitedWithCode(1);

    std::vector<double> u1_invalid = {1.3, 2.4, 3.0, 4.0};
    EXPECT_EXIT(error(u1_invalid, u2, dx, ErrorType::Linf), error_code, ".*");
}

TEST(OrderTest, OrderFunction1) {
    std::vector<double> err = {0.1, 0.05, 0.025};
    std::vector<size_t> nlist = {10, 20, 40};
    std::vector<double> result = order(err, nlist);

    ASSERT_EQ(result.size(), err.size());
    EXPECT_DOUBLE_EQ(result[0], 0.0);
    EXPECT_DOUBLE_EQ(result[1], 1.0);
    EXPECT_DOUBLE_EQ(result[2], 1.0);

    std::vector<double> err_close = {1.0, 0.24, 0.061};
    std::vector<size_t> nlist_close = {20, 40, 80};
    std::vector<double> result_close = order(err_close, nlist_close);

    ASSERT_EQ(result_close.size(), err_close.size());
    EXPECT_DOUBLE_EQ(result_close[0], 0.0);
    EXPECT_NEAR(result_close[1], 2.06, 1e-2);
    EXPECT_NEAR(result_close[2], 1.98, 1e-2);
}

TEST(OrderTest, OrderFunction2) {
    auto error_code = ::testing::ExitedWithCode(1);

    EXPECT_EXIT(order(std::vector<double>{}, std::vector<size_t>{}), error_code,
                ".*");

    std::vector<double> err_single = {0.1};
    std::vector<size_t> nlist_single = {10};
    EXPECT_EXIT(order(err_single, nlist_single), error_code, ".*");

    std::vector<double> err_invalid = {0.1, 0.05};
    std::vector<size_t> nlist_invalid = {10, 20, 40};
    EXPECT_EXIT(order(err_invalid, nlist_invalid), error_code, ".*");

    std::vector<double> err_invalid_single = {0.1, 0.05, 0.025};
    std::vector<size_t> nlist_invalid_single = {10};
    EXPECT_EXIT(order(err_invalid_single, nlist_invalid_single), error_code,
                ".*");
}
