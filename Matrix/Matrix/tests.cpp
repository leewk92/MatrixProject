#include <gtest\gtest.h>
#include "Matrix.h"

//typedef int Matrix;
static Matrix MATRIX;

void testAllCases(){
	
}	
// 행렬 더하기
TEST(MATRIX_ADD_TEST,COMMUTATIVE){
	Matrix a,b;
	a = MATRIX.Zeros(3);
	EXPECT_EQ(a+b, b+a);
}

TEST(MATRIX_ADD_TEST,ASSOCIATIVE){
	Matrix a,b,c;

	EXPECT_EQ((a+b)+c, a+(b+c));
}

TEST(MATRIX_ADD_TEST,IDENTITY_ELEMENT){
	Matrix a,zeros;

	EXPECT_EQ(a+zeros, zeros+a);
}

TEST(MATRIX_ADD_TEST,INVERSE_ELEMENT){
	Matrix a,inverseElement,zeros;

	EXPECT_EQ(a+(-a), (-a)+a);
	EXPECT_EQ(a+(-a),zeros);
}


// 행렬 빼기
TEST(MATRIX_SUB_TEST,){ // TODO
	Matrix a,b;

	EXPECT_EQ(-(-a), a);
}

// 행렬과 행렬 곱하기
TEST(MATRIX_MULTIPLY_TSET,ASSOCIATIVE_MULTIPLY){
	Matrix A,B,C;

	EXPECT_EQ(A*(B*C),(A*B)*C);
}
TEST(MATRIX_MULTIPLY_TSET,DISTRIBUTION_ADD_MULTIPLY){
	Matrix A,B,C;

	EXPECT_EQ((A + B)*C,A*C + B*C);
}
TEST(MATRIX_MULTIPLY_TSET,DISTRIBUTION_MULTIPLY_ADD){
	Matrix A,B,C;

	EXPECT_EQ(A*(B + C),A*B + A*C);
}
TEST(MATRIX_MULTIPLY_TSET,ASSOCIATIVE_CONSTANT_MULTIPLY){
	Matrix A,B;
	double k;
	EXPECT_EQ((k*A)*B,k*(A*B));
	EXPECT_EQ(k*(A*B),A*(k*B));
}

// 행렬과 상수 더하기
TEST(MATRIX_CONSTANT_ADD_TSET,COMMUATATIVE){
	Matrix A;
	double k;

	EXPECT_EQ(k+A,A+k);
}
// 행렬과 상수 빼기
TEST(MATRIX_CONSTANT_SUB_TSET,){ // TODO
	Matrix A;
	double k;

	EXPECT_EQ(k-A,-(A-k));
}
// 행렬과 상수 곱하기
TEST(MATRIX_CONSTANT_MULTIPLY_TSET,COMMUATATIVE){
	Matrix A;
	double k;

	EXPECT_EQ(k*A,A*k);
}

// 행렬과 상수 나누기
TEST(MATRIX_CONSTANT_DEVIDE_TSET,){		// TODO
	Matrix A,B;
	double k;

	EXPECT_EQ(A/k,B);
}

