#include "gtest/gtest.h"
#include "program.hpp"

string exec(string s){
    Program p{s};
    return p.executeString();
}

TEST(Program_test, test_OneLineProgram) {
    EXPECT_EQ (exec("1"), "1.000000");
    //basic operations
    EXPECT_EQ (exec("1+2"), "3.000000");
    EXPECT_EQ (exec("2/3"), "0.666667");
    EXPECT_EQ (exec("6*5"), "30.000000");
    EXPECT_EQ (exec("6-3"), "3.000000");
     //operations priorities
    EXPECT_EQ (exec("1+2*5"), "11.000000");
    EXPECT_EQ (exec("6/3-1"), "1.000000");
    EXPECT_EQ (exec("1-6*5"), "-29.000000");
    EXPECT_EQ (exec("6/3*5"), "10.000000");
    //parenthesis
    EXPECT_EQ (exec("(3+2)/2"), "2.500000");
    EXPECT_EQ (exec("2/(3+2)"), "0.400000");
    EXPECT_EQ (exec("2*(3+2)"), "10.000000");
    EXPECT_EQ (exec("2.35"), "2.350000");
    //no output when SEMI
    EXPECT_EQ (exec("1.27;"), "");
    EXPECT_EQ (exec("3/12.67;"), "");
    EXPECT_EQ (exec("(86.1-10)*48.12;37.11/2;"), "");
    EXPECT_EQ (exec("3/12.67;"), "");
}

TEST(Program_test, test_MultiLineProgram) {
    EXPECT_EQ (exec("6*5 \n 3*7"), "30.00000021.000000");
    //first line invisible
    EXPECT_EQ (exec("6*5;3*7+1"), "22.000000");
    //each line is invisible
    EXPECT_EQ (exec("(6*5)+32.5; \n 3*7; \n 11/12.5;"), "");
}

TEST(Program_test, test_Functions) {
    //declaration does not print
    EXPECT_EQ (exec("testfun = 2;"), "");
    //declaration expect alpha at the beggining, any other char after until space
    ASSERT_ANY_THROW(exec("_testfun = 2;"));
    ASSERT_NO_THROW(exec("test_fun = 2;"));
    ASSERT_NO_THROW(exec("TeStfUn = 2;"));
    ASSERT_NO_THROW(exec("T_estfUn__ = 2;"));
    ASSERT_NO_THROW(exec("T_eStfUn_10_ = 2;"));
    ASSERT_NO_THROW(exec("T_eStfUn_10_again_ = 2;"));
    //declaration + call
    //for multi line programs, ';' is expected at the end of the rvalue
    EXPECT_EQ (exec("testfun = 2; \n testfun+1"), "3.000000");
    EXPECT_EQ (exec("testfun = 2; \n testfun+testfun"), "4.000000");
    EXPECT_EQ (
        exec("testfun = 2; testfun2 = 10/2-1; \n testfun+testfun2"), "6.000000");
}
TEST(Program_test, test_FullPrograms){
    //circle diameter
    EXPECT_EQ (
        exec("pi = 3.14159; r = 3; diameter = 2*pi*r; diameter"),
         "18.849541");
    //power of 2 and 3
    EXPECT_EQ (    
        exec("input = 2; pow_2 = input*input; pow_3 = pow_2*input; pow_2 \n pow_3"),
         "4.0000008.000000");
    //area of triangle
    EXPECT_EQ (    
        exec("baseTriangle = 203; height_triangle = 137; area = 0.5*baseTriangle*height_triangle; area"),
         "13905.500000");
    //surface area and volume of a circular cylinder (results are 1943.859863 and 871.791748)
    EXPECT_EQ (
        exec(
    "r = 7.5; h = 11; pi = 3.141592; surface_area = 2*pi*r*h + 2*pi*r*r; volume=pi*r*r*h; volume \n surface_area"),
         "1943.859863871.791748");
    //slope of a line between 2 points
    EXPECT_EQ ( exec("x1 = 15; y1 = 8; x2 = 10; y2 = 7; slope = (y2-y1)/(x2-x1); slope"),
         "0.200000");
    
}

