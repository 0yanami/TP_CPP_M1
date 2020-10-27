#include "gtest/gtest.h"
#include "expression.hpp"

TEST(ExpressionToString_test, test_BinOp) {
    Expression add("+");
    EXPECT_EQ (add.print(), "Operateur(+)");
    Expression neg("-");
    EXPECT_EQ (neg.print(), "Operateur(-)");
    Expression div("/");
    EXPECT_EQ (div.print(), "Operateur(/)");
    Expression mul("*");
    EXPECT_EQ (mul.print(), "Operateur(*)");
    Expression multiple("*+*/--");
    EXPECT_EQ (multiple.print(), 
    "Operateur(*)Operateur(+)Operateur(*)Operateur(/)Operateur(-)Operateur(-)");
    Expression empty("");
    EXPECT_NE (empty.print(), "Operateur()");
}

TEST(ExpressionToString_test, test_Numeral) {
    Expression one("1");
    EXPECT_EQ (one.print(), "Numeral(1)");
    Expression integ("32768");
    EXPECT_EQ (integ.print(), "Numeral(32768)");
    Expression zeros("000000");
    // 0000 est percu comme une valeur int = 0
    EXPECT_EQ (zeros.print(), "Numeral(0)");
    EXPECT_NE (zeros.print(), "Numeral(000000)");
    Expression exprneg("-1");
    EXPECT_NE (exprneg.print(), "Operateur(-1)");
    EXPECT_EQ (exprneg.print(), "Operateur(-)Numeral(1)");
    Expression spaces("23 4567");
    EXPECT_NE (spaces.print(), "Numeral(23 4567)");
    EXPECT_EQ (spaces.print(), "Numeral(23)Numeral(4567)");
}

TEST(ExpressionToString_test, test_NumeralAndBinop) {
    Expression add("1+1");
    EXPECT_EQ (add.print(), "Numeral(1)Operateur(+)Numeral(1)");
    Expression space("1 + 1");
    EXPECT_EQ (space.print(), "Numeral(1)Operateur(+)Numeral(1)");
    Expression sub("327-68");
    EXPECT_EQ (sub.print(), "Numeral(327)Operateur(-)Numeral(68)");
    Expression div("0/0");
    EXPECT_EQ (div.print(), "Numeral(0)Operateur(/)Numeral(0)");
    Expression mul("35*7721");
    EXPECT_EQ (mul.print(), "Numeral(35)Operateur(*)Numeral(7721)");

    Expression multi("12*4/11-1337+0");
    EXPECT_EQ (multi.print(), 
    "Numeral(12)Operateur(*)Numeral(4)Operateur(/)Numeral(11)Operateur(-)Numeral(1337)Operateur(+)Numeral(0)");
}