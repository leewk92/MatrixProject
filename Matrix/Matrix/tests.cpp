#ifndef TESTS_CPP
#define TESTS_CPP
#include <gtest\gtest.h>
#include "Matrix.h"

//typedef int Matrix;
static Matrix MATRIX;

Matrix Zeros = MATRIX.Zeros(2);
double k = 2.;

Matrix A = Matrix("1,2;3,4");
Matrix B = Matrix("2,3;4,5");
Matrix C = Matrix("3,4;5,6");


// ��� ���ϱ�
TEST(MATRIX_ADD_TEST,VALUE){

	Matrix result("3,5;7,9");
	EXPECT_EQ(A + B, result);
}

TEST(MATRIX_ADD_TEST,COMMUTATIVE){
	EXPECT_EQ(A + B, B + A);
}

TEST(MATRIX_ADD_TEST,ASSOCIATIVE){
	EXPECT_EQ((A+B)+ C, A+(B + C));
}

TEST(MATRIX_ADD_TEST,IDENTITY_ELEMENT){
	EXPECT_EQ(A+Zeros, Zeros+A);
}

TEST(MATRIX_ADD_TEST,INVERSE_ELEMENT){
	EXPECT_EQ(A+(-A), (-A)+A);
	EXPECT_EQ(A+(-A),Zeros);
}

// ��� ����
TEST(MATRIX_SUB_TEST,){ // TODO
	EXPECT_EQ(-(-A), A);
}

// ��İ� ��� ���ϱ�
TEST(MATRIX_MULTIPLY_TEST,ASSOCIATIVE_MULTIPLY){
	EXPECT_EQ(A*(B*C),(A*B)*C);
}
TEST(MATRIX_MULTIPLY_TEST,DISTRIBUTION_ADD_MULTIPLY){

	EXPECT_EQ((A + B)*C,A*C + B*C);
}
TEST(MATRIX_MULTIPLY_TEST,DISTRIBUTION_MULTIPLY_ADD){
	EXPECT_EQ(A*(B + C),A*B + A*C);
}
TEST(MATRIX_MULTIPLY_TEST,ASSOCIATIVE_CONSTANT_MULTIPLY){
	EXPECT_EQ((k*A)*B,k*(A*B));
	EXPECT_EQ(k*(A*B),A*(k*B));
}

// ��İ� ��� ���ϱ�
TEST(MATRIX_CONSTANT_ADD_TEST,COMMUATATIVE){
	EXPECT_EQ(k+A,A+k);
}
TEST(MATRIX_CONSTANT_ADD_TEST,SELF){
	Matrix tmp_A;
	tmp_A = A;
	tmp_A += k;
	EXPECT_EQ(tmp_A,A+k);
}

// ��İ� ��� ����
TEST(MATRIX_CONSTANT_SUB_TEST,){ 
	EXPECT_EQ(k-A,-(A-k));
}
TEST(MATRIX_CONSTANT_SUB_TEST,SELF){
	Matrix tmp_A;
	tmp_A = A;
	tmp_A -=k;
	EXPECT_EQ(tmp_A, A-k);
}

// ��İ� ��� ���ϱ�
TEST(MATRIX_CONSTANT_MULTIPLY_TEST,COMMUATATIVE){
	EXPECT_EQ(k*A,A*k);
}
TEST(MATRIX_CONSTANT_MULTIPLY_TEST,SELF){ // TODO
	Matrix tmp_A;
	tmp_A = A;
	tmp_A *=k;
	EXPECT_EQ(tmp_A, A*k);
}

// ��İ� ��� ������
TEST(MATRIX_CONSTANT_DEVIDE_TEST,){		
	EXPECT_EQ(k*A/k,A);
}
TEST(MATRIX_CONSTANT_DEVIDE_TEST,SELF){ // TODO
	Matrix tmp_A;
	tmp_A = A;
	tmp_A /=k;
	EXPECT_EQ(tmp_A, A/k);
}
#endif