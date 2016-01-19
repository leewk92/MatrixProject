#ifndef TESTS_CPP
#define TESTS_CPP
#include <gtest\gtest.h>
#include "Matrix.h"

//typedef int Matrix;
static Matrix MATRIX;

Matrix A(2),B(2),C(2);
Matrix Zeros = MATRIX.Zeros(2);
double k;
void prepareTest(){
	A(1,1) = 1;
	A(1,2) = 2;
	A(2,1) = 3;
	A(2,2) = 4;
	B(1,1) = 2;
	B(1,2) = 3;
	B(2,1) = 4;
	B(2,2) = 5;
	C(1,1) = 3;
	C(1,2) = 4;
	C(2,1) = 5;
	C(2,2) = 6;
	k = 2.;
}	
// 행렬 더하기
TEST(MATRIX_ADD_TEST,COMMUTATIVE){
	prepareTest();
	EXPECT_EQ(A+B, B+A);
}

TEST(MATRIX_ADD_TEST,ASSOCIATIVE){
	prepareTest();
	EXPECT_EQ((A+B)+C, A+(B+C));
}

TEST(MATRIX_ADD_TEST,IDENTITY_ELEMENT){
	prepareTest();
	EXPECT_EQ(A+Zeros, Zeros+A);
}

TEST(MATRIX_ADD_TEST,INVERSE_ELEMENT){
	prepareTest();
	EXPECT_EQ(A+(-A), (-A)+A);
	EXPECT_EQ(A+(-A),Zeros);
}


// 행렬 빼기
TEST(MATRIX_SUB_TEST,){ // TODO
	prepareTest();
	EXPECT_EQ(-(-A), A);
}

// 행렬과 행렬 곱하기
TEST(MATRIX_MULTIPLY_TSET,ASSOCIATIVE_MULTIPLY){
	prepareTest();

	EXPECT_EQ(A*(B*C),(A*B)*C);
}
TEST(MATRIX_MULTIPLY_TSET,DISTRIBUTION_ADD_MULTIPLY){

	prepareTest();
	EXPECT_EQ((A + B)*C,A*C + B*C);
}
TEST(MATRIX_MULTIPLY_TSET,DISTRIBUTION_MULTIPLY_ADD){
	prepareTest();
	EXPECT_EQ(A*(B + C),A*B + A*C);
}
TEST(MATRIX_MULTIPLY_TSET,ASSOCIATIVE_CONSTANT_MULTIPLY){
	prepareTest();
	EXPECT_EQ((k*A)*B,k*(A*B));
	EXPECT_EQ(k*(A*B),A*(k*B));
}

// 행렬과 상수 더하기
TEST(MATRIX_CONSTANT_ADD_TSET,COMMUATATIVE){

	prepareTest();
	EXPECT_EQ(k+A,A+k);
}
// 행렬과 상수 빼기
TEST(MATRIX_CONSTANT_SUB_TSET,){ // TODO
	prepareTest();

	EXPECT_EQ(k-A,-(A-k));
}
// 행렬과 상수 곱하기
TEST(MATRIX_CONSTANT_MULTIPLY_TSET,COMMUATATIVE){

	prepareTest();
	EXPECT_EQ(k*A,A*k);
}

// 행렬과 상수 나누기
TEST(MATRIX_CONSTANT_DEVIDE_TSET,){		// TODO

	prepareTest();
	EXPECT_EQ(A/k,B);
}

#endif