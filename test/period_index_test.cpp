#include "period_index.hpp"

#include "gtest/gtest.h"

using namespace flux;      // NOLINT

class PeriodIndexTest : public ::testing::Test {
protected:
    size_t n = 10;
    size_t i = 3;

    void SetUp() override {}

    void TearDown() override {}

    PeriodIndex index{n, i};
};

TEST_F(PeriodIndexTest, cindex) { EXPECT_EQ(index.c(), i); }

TEST_F(PeriodIndexTest, lindex) {
    EXPECT_EQ(index.l(), (i + n - 1) % n);
    size_t step = 3;
    EXPECT_EQ(index.l(step), (i + n - step) % n);
}

TEST_F(PeriodIndexTest, rindex) {
    EXPECT_EQ(index.r(), (i + 1) % n);
    size_t step = 3;
    EXPECT_EQ(index.r(step), (i + step) % n);
}
