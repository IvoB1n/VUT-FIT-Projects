//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     IVAN BOBROV <xbobro01@stud.fit.vutbr.cz>
// $Date:       $2020-03-03
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author IVAN BOBROV
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//#include <iomanip>

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//
// initialize matrix classes to test
class MatrixNoArguments : public ::testing::Test {
    protected:

    virtual void TearDown(){
        delete matrix;
    }
    
    Matrix *matrix = new Matrix;
};

class Matrix_1x1 : public ::testing::Test {
    protected:

    virtual void SetUp() {
        matrix->set(0, 0, 1.5);
    }

    virtual void TearDown(){
        delete matrix;
    }

    Matrix *matrix = new Matrix(1, 1);
};


class Matrix_1x2 : public ::testing::Test {
    protected:

    virtual void SetUp() {
        matrix->set(0, 0, 1.5);
        matrix->set(1, 0, 2.5);
    }
    
    virtual void TearDown(){
        delete matrix;
    }

    Matrix *matrix = new Matrix(1, 2);
};

class Matrix_2x1 : public ::testing::Test {
    protected:

    virtual void SetUp() {
        matrix->set(0, 0, 1.5);
        matrix->set(0, 1, 2.5);
    }

    virtual void TearDown(){
        delete matrix;
    }

    Matrix *matrix = new Matrix(2, 1);
};

class Matrix_2x2 : public ::testing::Test {
    protected:

    virtual void SetUp() {
        matrix->set(0, 0, 1.0);
        matrix->set(0, 1, 1.1);
        matrix->set(1, 0, 1.2);
        matrix->set(1, 1, 1.3);
    }

    virtual void TearDown(){
        delete matrix;
    }

    Matrix *matrix = new Matrix(2, 2);
};

class Matrix_3x3 : public ::testing::Test {
    protected:

    virtual void SetUp() {
        matrix->set(0, 0, 1.0);
        matrix->set(0, 1, 1.1);
        matrix->set(0, 2, 1.2);
        matrix->set(1, 0, 1.3);
        matrix->set(1, 1, 1.4);
        matrix->set(1, 2, 1.5);
        matrix->set(2, 0, 1.6);
        matrix->set(2, 1, 1.7);
        matrix->set(2, 2, 1.8);
    }

    virtual void TearDown(){
        delete matrix;
    }

    Matrix *matrix = new Matrix(3, 3);
};

class Matrix_4x4 : public ::testing::Test {
    protected:

    virtual void SetUp() {
        matrix->set(0, 0, 1);
        matrix->set(0, 1, 3);
        matrix->set(0, 2, 1);
        matrix->set(0, 3, 4);
        matrix->set(1, 0, 0);
        matrix->set(1, 1, 2);
        matrix->set(1, 2, 1);
        matrix->set(1, 3, 1);
        matrix->set(2, 0, 0);
        matrix->set(2, 1, 0);
        matrix->set(2, 2, 2);
        matrix->set(2, 3, 3);
        matrix->set(3, 0, 0);
        matrix->set(3, 1, 0);
        matrix->set(3, 2, 0);
        matrix->set(3, 3, 1);

    }

    virtual void TearDown(){
        delete matrix;
    }

    Matrix *matrix = new Matrix(4, 4);
};

TEST(WrongValuesMatrix, InitWithImplicitVal){
    // try to create matrix with implicit arguments
    Matrix *matrix;
    EXPECT_ANY_THROW(matrix = new Matrix(0, 0));
    EXPECT_ANY_THROW(matrix = new Matrix(0, 1));
    EXPECT_ANY_THROW(matrix = new Matrix(1, 0));
    EXPECT_ANY_THROW(matrix = new Matrix(-1, -1));
    EXPECT_ANY_THROW(matrix = new Matrix(-1, 1));
    EXPECT_ANY_THROW(matrix = new Matrix(1, -1));
}

TEST_F(MatrixNoArguments, Init) {
    // check if matrix was init with size 1x1 has no data
    ASSERT_NO_THROW(matrix->get(0, 0));
    EXPECT_EQ(0, matrix->get(0, 0));
    EXPECT_ANY_THROW(matrix->get(0, 1));
    EXPECT_ANY_THROW(matrix->get(1, 0));
}

TEST_F(Matrix_1x1, Init) {
    // check if matrix was init with size 1x1 and has data
    ASSERT_NO_THROW(matrix->get(0, 0));
    EXPECT_EQ(1.5, matrix->get(0, 0));
    EXPECT_ANY_THROW(matrix->get(0, 1));
    EXPECT_ANY_THROW(matrix->get(1, 0));
}

TEST_F(Matrix_2x2, Get) {
    // if matrix cell data can be accessible
    ASSERT_NO_THROW(matrix->get(0, 0));
    ASSERT_NO_THROW(matrix->get(1, 0));
    ASSERT_NO_THROW(matrix->get(0, 1));
    ASSERT_NO_THROW(matrix->get(1, 1));

    EXPECT_EQ(1.0, matrix->get(0, 0));
    EXPECT_EQ(1.2, matrix->get(1, 0));
    EXPECT_EQ(1.1, matrix->get(0, 1));
    EXPECT_EQ(1.3, matrix->get(1, 1));

    // try to get unaccessible cells
    EXPECT_ANY_THROW(matrix->get(0, 2));
    EXPECT_ANY_THROW(matrix->get(2, 0));
}

TEST_F(Matrix_1x1, Set) {
    // set data using direct cells
    ASSERT_NO_THROW(matrix->set(0,0, 2));
    EXPECT_EQ(2, matrix->get(0, 0));
}

TEST_F(Matrix_1x1, SetVec) {
    // set data using vectors
    ASSERT_NO_THROW(matrix->set(std::vector<std::vector<double>>(1, std::vector<double>(1, 5))));
    EXPECT_EQ(5, matrix->get(0, 0));
}

TEST_F(Matrix_2x2, Set) {
    // set data using direct cells
    ASSERT_NO_THROW(matrix->set(0,0, 1));
    ASSERT_NO_THROW(matrix->set(1,0, 2));
    ASSERT_NO_THROW(matrix->set(0,1, 3));
    ASSERT_NO_THROW(matrix->set(1,1, 4));

    EXPECT_EQ(1, matrix->get(0, 0));
    EXPECT_EQ(2, matrix->get(1, 0));
    EXPECT_EQ(3, matrix->get(0, 1));
    EXPECT_EQ(4, matrix->get(1, 1));

    // try to set data using unaccessible cells
    EXPECT_EQ(false, matrix->set(3, 1, 4));
}

TEST_F(Matrix_2x2, SetVec) {
    // set data using vectors
    ASSERT_NO_THROW(matrix->set(std::vector<std::vector<double>>{{9, 8},{7, 6}}));
    EXPECT_EQ(9, matrix->get(0, 0));
    EXPECT_EQ(8, matrix->get(0, 1));
    EXPECT_EQ(7, matrix->get(1, 0));
    EXPECT_EQ(6, matrix->get(1, 1));
}

TEST_F(Matrix_2x2, ImplicitSetVec) {
    // set data using implicit vectors
    bool succeed = false;
    ASSERT_NO_THROW(succeed = matrix->set(std::vector<std::vector<double>>{{9, 8, 9},{7, 6}}));
    EXPECT_EQ(false, succeed);
    ASSERT_NO_THROW(succeed = matrix->set(std::vector<std::vector<double>>{{9, 8},{7, 6}, {1, 2}}));
    EXPECT_EQ(false, succeed);
}

TEST_F(Matrix_3x3, OperatorIsequal) {
    // equals two matrix
    Matrix *matrix_eq = new Matrix(3, 3);
    Matrix *matrix_empty = new Matrix(3, 3); 
    matrix_eq->set(0, 0, 1.0);
    matrix_eq->set(0, 1, 1.1);
    matrix_eq->set(0, 2, 1.2);
    matrix_eq->set(1, 0, 1.3);
    matrix_eq->set(1, 1, 1.4);
    matrix_eq->set(1, 2, 1.5);
    matrix_eq->set(2, 0, 1.6);
    matrix_eq->set(2, 1, 1.7);
    matrix_eq->set(2, 2, 1.8);

    EXPECT_EQ(true, matrix->operator==(*matrix_eq));
    EXPECT_EQ(false, matrix->operator==(*matrix_empty));
}

TEST_F(Matrix_3x3, OperatorIsEqualImlicitMatrix) {
    // try to equal two matrix with different size
    Matrix *matrix_eq = new Matrix(2, 2);
    Matrix *matrix_empty = new Matrix(3, 3); 

    ASSERT_ANY_THROW(matrix->operator==(*matrix_eq));
}

TEST_F(Matrix_3x3, OperatorAdd) {
    // addition of two matrix
    Matrix *matrix_to_add = new Matrix(3, 3); 
    Matrix *matrix_result = new Matrix(3,3);
    Matrix *matrix_eq = new Matrix(3, 3);
    
    matrix_to_add->set(0, 0, 1.0); matrix_eq->set(0, 0, 1.0 + 1.0);
    matrix_to_add->set(0, 1, 0.9); matrix_eq->set(0, 1, 1.1 + 0.9);
    matrix_to_add->set(0, 2, 0.8); matrix_eq->set(0, 2, 1.2 + 0.8);
    matrix_to_add->set(1, 0, 0.7); matrix_eq->set(1, 0, 1.3 + 0.7);
    matrix_to_add->set(1, 1, 0.6); matrix_eq->set(1, 1, 1.4 + 0.6);
    matrix_to_add->set(1, 2, 0.5); matrix_eq->set(1, 2, 1.5 + 0.5);
    matrix_to_add->set(2, 0, 0.4); matrix_eq->set(2, 0, 1.6 + 0.4);
    matrix_to_add->set(2, 1, 0.3); matrix_eq->set(2, 1, 1.7 + 0.3);
    matrix_to_add->set(2, 2, 0.2); matrix_eq->set(2, 2, 1.8 + 0.2);

    ASSERT_NO_THROW(*matrix_result = matrix->operator+(*matrix_to_add));
    EXPECT_EQ(*matrix_result, *matrix_eq);
}

TEST_F(Matrix_3x3, OperatorAddImplicitVal) {
    // addition of two matrix different size
    Matrix *matrix_to_add = new Matrix(2, 2); 
    
    ASSERT_ANY_THROW(matrix->operator+(*matrix_to_add));
}

TEST_F(Matrix_2x2, OperatorMult) {
    // multiply two matrix
    Matrix *matrix_to_mul = new Matrix(2, 2); 
    Matrix *matrix_result = new Matrix(2, 2);
    Matrix *matrix_eq = new Matrix(2, 2);
    
    matrix_to_mul->set(0, 0, 1); matrix_eq->set(0, 0, 1.0*1+1.1*3);
    matrix_to_mul->set(0, 1, 2); matrix_eq->set(0, 1, 1.0*2+1.1*4);
    matrix_to_mul->set(1, 0, 3); matrix_eq->set(1, 0, 1.2*1+1.3*3);
    matrix_to_mul->set(1, 1, 4); matrix_eq->set(1, 1, 1.2*2+1.3*4);

    ASSERT_NO_THROW(*matrix_result = matrix->operator*(*matrix_to_mul));
    EXPECT_EQ(*matrix_result, *matrix_eq);
}

TEST_F(Matrix_2x2, OperatorMultConst) {
    // multiply matrix with constant value
    Matrix *matrix_eq = new Matrix(2, 2);
    double scalar = 5.6;    
    matrix_eq->set(0, 0, 1.0*5.6);
    matrix_eq->set(0, 1, 1.1*5.6);
    matrix_eq->set(1, 0, 1.2*5.6);
    matrix_eq->set(1, 1, 1.3*5.6);

    ASSERT_NO_THROW(*matrix = matrix->operator*(scalar));
    EXPECT_EQ(*matrix, *matrix_eq);
}

TEST_F(Matrix_2x2, OperatorMultImplicitMatrix) {
    // try to multiply two matrix with different size

    Matrix *matrix_to_mul = new Matrix(4, 4);

    ASSERT_ANY_THROW(*matrix = matrix->operator*(*matrix_to_mul));
}

//try to solve an equation with different size matrix
TEST_F(Matrix_1x1, solveEquation1x1){
    std::vector<double> result;
    std::vector<double> result_eq = {1};
    std::vector<double> right_side = {1.5};

    ASSERT_NO_THROW(result = matrix->solveEquation(right_side));
    EXPECT_EQ(result, result_eq);
}

TEST_F(Matrix_1x2, solveEquation1x2){
    // try to solve an equation with wrong right side
    std::vector<double> right_side = {1.5, 2};

    ASSERT_ANY_THROW(matrix->solveEquation(right_side));
}

TEST_F(Matrix_2x1, solveEquation2x1){
    // try to solve an equation with wrong right side
    std::vector<double> right_side = {1.5};

    ASSERT_ANY_THROW(matrix->solveEquation(right_side));
}

TEST_F(Matrix_2x2, solveEquation2x2){
    std::vector<double> result;
    std::vector<double> result_eq = {1.0, 1.0};
    std::vector<double> right_side = {1, 3};

    matrix->set(0, 0, 1); matrix->set(1, 0, 1);
    matrix->set(0, 1, 0); matrix->set(1, 1, 2);
    ASSERT_NO_THROW(result = matrix->solveEquation(right_side));
    EXPECT_EQ(result, result_eq);
}

TEST_F(Matrix_2x2, solveEquation2x2_ImplicitVal){
    // try to solve an equation with wrong right side
    std::vector<double> right_side = {2.1, 2.5, 3};

    ASSERT_ANY_THROW(matrix->solveEquation(right_side));
}

TEST_F(Matrix_2x2, solveEquation2x2_ImplicitMatrix){
    // try to solve an equation with det = 0
    std::vector<double> right_side = {2.1, 2.5};

    matrix->set(0, 0, 1); matrix->set(1, 0, -2);
    matrix->set(0, 1, -2); matrix->set(1, 1, 4);
    ASSERT_ANY_THROW(matrix->solveEquation(right_side));
}

TEST_F(Matrix_3x3, solveEquation3x3){
    std::vector<double> result;
    std::vector<double> result_eq = {1, 1, 1};
    std::vector<double> right_side = {2, 2, 1};
    matrix = new Matrix(3, 3);
    matrix->set(0, 0, 1);
    matrix->set(0, 2, 1);
    matrix->set(1, 1, 2);
    matrix->set(2, 2, 1);

    ASSERT_NO_THROW(result = matrix->solveEquation(right_side));
    EXPECT_EQ(result, result_eq);
}
TEST_F(Matrix_4x4, solveEquation4x4){
    std::vector<double> result;
    std::vector<double> result_eq = {1, 1, 1, 1};
    std::vector<double> right_side = {9, 4, 5, 1};

    ASSERT_NO_THROW(result = matrix->solveEquation(right_side));
    EXPECT_EQ(result, result_eq);
}
/*** Konec souboru white_box_tests.cpp ***/
    