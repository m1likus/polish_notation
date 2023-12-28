#include <gtest.h>
#include "polish_notation.h"

TEST(EXAMPLE1) {
    string str = "sin(5 + 5) + 146 * 15 * tg(145 * 4)";
    arithmeticExpr expr(str);
    EXPECT_EQ(expr.getPostfix(), "55+sin14615*1454*tg*+");
}
TEST(EXAMPLE2) {
    string str = "sin(5 + 5) + 146 * 15 * tg(145 * 4)";
    arithmeticExpr expr(str);
    EXPECT_EQ(expr.calculating(), (sin(5 + 5) + 146 * 15 * tan(145 * 4)));
}
TEST(EXAMPLE3) {
    string str = "18*(15))";
    ASSERT_ANY_THROW(arithmeticExpr expr(str));
}
TEST(EXAMPLE4) {
    string str = "-";
    ASSERT_ANY_THROW(arithmeticExpr expr(str));
}
TEST(EXAMPLE5) {
    string str = "-100";
    arithmeticExpr expr(str);
    EXPECT_EQ(expr.calculating(), -100);
}
TEST(EXAMPLE6) {
    string str = "()";
    ASSERT_ANY_THROW(arithmeticExpr expr(str));
}










int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}