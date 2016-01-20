/* Reference : http://matrix.skku.ac.kr/sglee/linear/ocu/thm.html
 * 
 * 
 */


#ifndef TESTS_CPP
#define TESTS_CPP
#include <gtest\gtest.h>
#include "Matrix.h"

//typedef int Matrix;
static Matrix MATRIX;

Matrix Zeros = MATRIX.Zeros(2);
Matrix Eyes = MATRIX.Eyes(2);
double k = 2.;

Matrix A = Matrix("1,2;3,4");
Matrix B = Matrix("2,3;4,5");
Matrix C = Matrix("3,4;5,6");


// 행렬 더하기
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

// 행렬 빼기
TEST(MATRIX_SUB_TEST,CHAINING){ 
	EXPECT_EQ(-(-A), A);
}

// 행렬과 행렬 곱하기
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

// 행렬과 상수 더하기
TEST(MATRIX_CONSTANT_ADD_TEST,COMMUATATIVE){
	EXPECT_EQ(k+A,A+k);
}
TEST(MATRIX_CONSTANT_ADD_TEST,SELF){
	Matrix tmp_A;
	tmp_A = A;
	tmp_A += k;
	EXPECT_EQ(tmp_A,A+k);
}

// 행렬과 상수 빼기
TEST(MATRIX_CONSTANT_SUB_TEST,OTHER_COMMUTATIVE){ 
	EXPECT_EQ(k-A,-(A-k));
}
TEST(MATRIX_CONSTANT_SUB_TEST,SELF){
	Matrix tmp_A;
	tmp_A = A;
	tmp_A -=k;
	EXPECT_EQ(tmp_A, A-k);
}

// 행렬과 상수 곱하기
TEST(MATRIX_CONSTANT_MULTIPLY_TEST,COMMUATATIVE){
	EXPECT_EQ(k*A,A*k);
}
TEST(MATRIX_CONSTANT_MULTIPLY_TEST,SELF){ // TODO
	Matrix tmp_A;
	tmp_A = A;
	tmp_A *=k;
	EXPECT_EQ(tmp_A, A*k);
}

// 행렬과 상수 나누기
TEST(MATRIX_CONSTANT_DEVIDE_TEST,){		
	EXPECT_EQ(k*A/k,A);
}
TEST(MATRIX_CONSTANT_DEVIDE_TEST,SELF){ // TODO
	Matrix tmpA;
	tmpA = A;
	tmpA /=k;
	EXPECT_EQ(tmpA, A/k);
}

// 전치행렬(Transpose) : 정리4 
TEST(MATRIX_TRANSPOSE_TEST,VALUE){
	Matrix tmpA("1,2,3;4,5,6");
	Matrix tmpTransposeA("1,4;2,5;3,6");
	EXPECT_EQ(tmpA.T(), tmpTransposeA);
}
TEST(MATRIX_TRANSPOSE_TEST,CHAINING){
	EXPECT_EQ(A.T().T(),A);
}
TEST(MATRIX_TRANSPOSE_TEST,DISTRIBUTION){
	EXPECT_EQ((A+B).T(), A.T()+B.T());
}
TEST(MATRIX_TRANSPOSE_TEST,REVERSE){
	EXPECT_EQ((A*B).T(), B.T()*A.T());
}
TEST(MATRIX_TRANSPOSE_TEST,DISTRIBUTION_FOR_CONSTANT_MULTIPLY){
	EXPECT_EQ((k*A).T(), k*A.T());
}


// 특정 원소 수정
TEST(MATRIX_ACCESS_TEST,VALUE){
	Matrix tmpA("1,2,3;4,5,6;7,8,9");
	Matrix tmpB("1,2,3;1,5,6;7,4,9");
	tmpA(2,1) = 1;
	tmpA(3,2) = 4;

	EXPECT_EQ(tmpA,tmpB);
}

// 단위행렬 테스트
TEST(MATRIX_EYES_TEST,IDENTITY){
	EXPECT_EQ(A,A*Eyes);
}
TEST(MATRIX_EYES_TEST,COMMUTATIVE){
	EXPECT_EQ(Eyes*A,A*Eyes);
}

// 소행렬 테스트
TEST(MATRIX_MINOR_TEST,VALUE){

	Matrix A("3,0,2;2,0,-2;0,1,1");
	Matrix result("2,2,2;-2,3,3;0,-10,0");

	EXPECT_EQ(A.minor(), result);
}

// 수반행렬 테스트
TEST(MATRIX_ADJOINT_TEST,VALUE){

	Matrix A("3,0,2;2,0,-2;0,1,1");
	Matrix result("2,2,0;-2,3,10;2,-3,0");

	EXPECT_EQ(A.adjoint(), result);
}
TEST(MATRIX_ADJOINT_TEST,INVERSE){ // 정리 21

	Matrix A("3,0,2;2,0,-2;0,1,1");
	
	EXPECT_EQ(A.inv(), 1/A.det()*A.adjoint());
}


// 행렬식 테스트
TEST(MATRIX_DETERMINENT_TEST,VALUE){
	Matrix A("3,0,2;2,0,-2;0,1,1");
	double result = 10.;
	EXPECT_EQ(A.det(), result);
}
TEST(MATRIX_DETERMINENT_TEST,TRANSPOSE){ //정리 11
	//Matrix A("3,0,2;2,0,-2;0,1,1");
	EXPECT_EQ(A.det(), A.T().det());
}
TEST(MATRIX_DETERMINENT_TEST,DISTRIBUTION_FOR_MULTIPLY){ // 정리 18
	//Matrix A("3,0,2;2,0,-2;0,1,1");
	//Matrix B("1,2,6;3,4,5;1,0,5");
	EXPECT_EQ( (A*B).det() , A.det() * B.det() );
}
TEST(MATRIX_DETERMINENT_TEST,REVERSE_FOR_INVERSE){ // 정리 18
	//Matrix A("3,0,2;2,0,-2;0,1,1");
	EXPECT_EQ( (A.inv()).det() , 1/A.det() );
}


// 역행렬 테스트 : 정리 7
TEST(MATRIX_INVERSE_TEST,VALUE){
	Matrix A("3,0,2;2,0,-2;0,1,1");
	Matrix result("0.2,0.2,0;-0.2,0.3,1;0.2,-0.3,0");
	EXPECT_EQ(A.inv(), result);
}
TEST(MATRIX_INVERSE_TEST,CHAINING){
	//Matrix A("3,0,2;2,0,-2;0,1,1");
	EXPECT_EQ(A.inv().inv(), A);
}
TEST(MATRIX_INVERSE_TEST,REVERSE){
	Matrix A("3,0,2;2,0,-2;0,1,1");
	Matrix B("1,2,6;3,4,5;1,0,5");
	EXPECT_EQ( (A*B).inv(), B.inv() * A.inv() );
}
TEST(MATRIX_INVERSE_TEST, COMMUTATIVE_FOR_TRANSPOSE){
	Matrix A("3,0,2;2,0,-2;0,1,1");
	EXPECT_EQ( (A.T()).inv(), (A.inv()).T());
}
TEST(MATRIX_INVERSE_TEST, DISTRIBUTION_FOR_CONSTANT){
	Matrix A("3,0,2;2,0,-2;0,1,1");
	EXPECT_EQ( (k*A).inv(), 1/k*A.inv());
}



#endif