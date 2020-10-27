#include "gtest/gtest.h"
#include "expression.hpp"

TEST(ExpressionToString_test, test_BinOp) {
    Expression expradd("+");
    EXPECT_EQ (expradd.print(), "Operateur(+)");
    Expression exprneg("-");
    EXPECT_EQ (exprneg.print(), "Operateur(-)");
    Expression exprdiv("/");
    EXPECT_EQ (exprdiv.print(), "Operateur(/)");
    Expression exprmul("*");
    EXPECT_EQ (exprmul.print(), "Operateur(*)");
    Expression exprmultiple("*+*/--");
    EXPECT_EQ (exprmultiple.print(), 
    "Operateur(*)Operateur(+)Operateur(*)Operateur(/)Operateur(-)Operateur(-)");
    Expression exprempty("");
    EXPECT_NE (exprempty.print(), "Operateur()");
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
}