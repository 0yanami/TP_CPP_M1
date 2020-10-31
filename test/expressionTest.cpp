#include "gtest/gtest.h"
#include "expression.hpp"

#include<map>

string toTk(string s){
    map<string, float> mem = {};
    auto res = get<0>(Expression::tokensFromString(s,mem).at(0));
    return Expression::print(res);
}

TEST(ExpressionToString_test, test_BinOp) {
    EXPECT_EQ (toTk("+"), "BinaryOp(+)");
    EXPECT_EQ (toTk("-"), "BinaryOp(-)");
    EXPECT_EQ (toTk("/"), "BinaryOp(/)");
    EXPECT_EQ (toTk("*"), "BinaryOp(*)");
    EXPECT_EQ (toTk("*+-/--"),
    "BinaryOp(*)BinaryOp(+)BinaryOp(-)BinaryOp(/)BinaryOp(-)BinaryOp(-)");
}

TEST(ExpressionToString_test, test_Literal) {
    EXPECT_EQ (toTk("1"), "Literal(1)");
    EXPECT_EQ (toTk("32768"), "Literal(32768)");
    // 000000 perceived as 0
    EXPECT_EQ (toTk("000000"), "Literal(0)");
    EXPECT_NE (toTk("000000"), "Literal(000000)");
    EXPECT_NE (toTk("-1"), "BinaryOp(-1)");
    EXPECT_EQ (toTk("-1"), "BinaryOp(-)Literal(1)");
    EXPECT_NE (toTk("23 4567"), "Literal(234567)");
    EXPECT_EQ (toTk("23 4567"), "Literal(23)Literal(4567)");
}
TEST(ExpressionToString_test, test_Reals) {
    EXPECT_EQ (toTk("1.15"), "Literal(1.15)");
    EXPECT_EQ (toTk("32768.1"), "Literal(32768.1)");
    // 000000.0 perceived as 0
    EXPECT_EQ (toTk("000000.0"), "Literal(0)");
    EXPECT_NE (toTk("000000.0"), "Literal(000000)");
    EXPECT_NE (toTk("-1.451"), "BinaryOp(-1.451)");
    EXPECT_EQ (toTk("-1.451"), "BinaryOp(-)Literal(1.451)");
    EXPECT_NE (toTk("23 4567.3"), "Literal(234567.3)");
    EXPECT_EQ (toTk("23 4567.3"), "Literal(23)Literal(4567.3)");
}

TEST(ExpressionToString_test, test_Parenthesis) {
    EXPECT_EQ (toTk("("), "(Left Parenthesis)");
    EXPECT_EQ (toTk(")"), "(Right Parenthesis)");
    EXPECT_EQ (toTk("(1)"), 
    "(Left Parenthesis)Literal(1)(Right Parenthesis)");
    EXPECT_EQ (toTk(")()(("), 
    "(Right Parenthesis)(Left Parenthesis)(Right Parenthesis)(Left Parenthesis)(Left Parenthesis)");
}

TEST(ExpressionToString_test, test_Expression) {
    EXPECT_EQ (toTk("1+1"), "Literal(1)BinaryOp(+)Literal(1)");
    EXPECT_EQ (toTk("1 + 1"), "Literal(1)BinaryOp(+)Literal(1)");
    EXPECT_EQ (toTk("327-68"), "Literal(327)BinaryOp(-)Literal(68)");
    EXPECT_EQ (toTk("0/0"), "Literal(0)BinaryOp(/)Literal(0)");
    EXPECT_EQ (toTk("35*7721"), "Literal(35)BinaryOp(*)Literal(7721)");
    EXPECT_EQ (toTk("(41-7)*7721"), "(Left Parenthesis)Literal(41)BinaryOp(-)Literal(7)(Right Parenthesis)BinaryOp(*)Literal(7721)");
    EXPECT_EQ (toTk("12*4/11-1337+0"), 
    "Literal(12)BinaryOp(*)Literal(4)BinaryOp(/)Literal(11)BinaryOp(-)Literal(1337)BinaryOp(+)Literal(0)");
}