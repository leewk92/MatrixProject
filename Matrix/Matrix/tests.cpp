/* Reference : 
 * Definition : http://matrix.skku.ac.kr/sglee/linear/ocu/thm.html
 * Gaussian Elimination : http://matrix.skku.ac.kr/sglee/linear/ocu/20104.html
 * 2016.01.21 TODO :1. determinant 성능 개선
 *					2. 오버로드된 오퍼레이터들에 const 붙여야되는것들 붙이기 v
 *					3. << left값 안바뀌게
 *					4. value test 들 붙이기
 *					5. Vector로의 확장
 *					6. interpreter 로 인터페이스 확장 (Parser)
 *					7. Exception class 만들어붙이기
 */


#ifndef TESTS_CPP
#define TESTS_CPP
#include <gtest\gtest.h>
#include "Matrix.h"

const int INVERSE_MAX_SIZE = 4;
const int GAUSSIAN_INVERSE_MAX_SIZE = 80;

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
	EXPECT_EQ((A + B)+ C, A + (B + C));
}

TEST(MATRIX_ADD_TEST,IDENTITY_ELEMENT){
	EXPECT_EQ(A + Zeros, Zeros + A);
}

TEST(MATRIX_ADD_TEST,INVERSE_ELEMENT){
	EXPECT_EQ(A + (-A), (-A) + A);
	EXPECT_EQ(A + (-A), Zeros);
}

// 행렬 빼기
TEST(MATRIX_SUB_TEST,CHAINING){ 
	EXPECT_EQ(-(-A), A);
}

// 행렬과 행렬 곱하기 // TODO : Value test
TEST(MATRIX_MULTIPLY_TEST,ASSOCIATIVE_MULTIPLY){ 
	EXPECT_EQ(A * (B*C),(A*B) * C);
}
TEST(MATRIX_MULTIPLY_TEST,DISTRIBUTION_ADD_MULTIPLY){

	EXPECT_EQ((A + B)*C, A*C + B*C);
}
TEST(MATRIX_MULTIPLY_TEST,DISTRIBUTION_MULTIPLY_ADD){
	EXPECT_EQ(A*(B + C), A*B + A*C);
}
TEST(MATRIX_MULTIPLY_TEST,ASSOCIATIVE_CONSTANT_MULTIPLY){
	EXPECT_EQ((k*A) * B, k * (A*B));
	EXPECT_EQ(k * (A*B), A * (k*B));
}

// 행렬과 상수 더하기 // TODO : Value test

TEST(MATRIX_CONSTANT_ADD_TEST,COMMUATATIVE){
	EXPECT_EQ(k+A, A+k);
}
TEST(MATRIX_CONSTANT_ADD_TEST,SELF){
	Matrix tmp_A;
	tmp_A = A;
	tmp_A += k;
	EXPECT_EQ(tmp_A, A+k);
}

// 행렬과 상수 빼기 // TODO : Value test
TEST(MATRIX_CONSTANT_SUB_TEST,OTHER_COMMUTATIVE){ 
	EXPECT_EQ(k-A, -(A-k));
}
TEST(MATRIX_CONSTANT_SUB_TEST,SELF){
	Matrix tmp_A;
	tmp_A = A;
	tmp_A -=k;
	EXPECT_EQ(tmp_A, A-k);
}

// 행렬과 상수 곱하기 // TODO : Value test
TEST(MATRIX_CONSTANT_MULTIPLY_TEST,COMMUATATIVE){
	EXPECT_EQ(k*A, A*k);
}
TEST(MATRIX_CONSTANT_MULTIPLY_TEST,SELF){ // TODO
	Matrix tmp_A;
	tmp_A = A;
	tmp_A *=k;
	EXPECT_EQ(tmp_A, A*k);
}

// 행렬과 상수 나누기 // TODO : Value test
TEST(MATRIX_CONSTANT_DEVIDE_TEST,){		
	EXPECT_EQ(k*A/k, A);
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
	EXPECT_EQ((A.T()).T(), A);
}
TEST(MATRIX_TRANSPOSE_TEST,DISTRIBUTION){
	EXPECT_EQ((A + B).T(), A.T() + B.T());
}
TEST(MATRIX_TRANSPOSE_TEST,REVERSE){
	EXPECT_EQ((A*B).T(), B.T()*A.T());
}
TEST(MATRIX_TRANSPOSE_TEST,DISTRIBUTION_FOR_CONSTANT_MULTIPLY){
	EXPECT_EQ((k*A).T(), k*A.T());
}


// 특정 원소 수정 // TODO : ACCESSOR test
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
	Matrix A("3,0,2;2,0,-2;0,1,1"); // TODO : 따로 위에 정의
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
TEST(MATRIX_INVERSE_TEST, IDENTITY){
	Matrix A = MATRIX.Rands(3); // TODO : 둘이 다른지, 사이즈가 원하는대로 만들어졌는지
	EXPECT_EQ( A.inv() * A, MATRIX.Eyes(3));
}

TEST(MATRIX_INVERSE_TEST, LARGE_MATRIX){
	Matrix A = MATRIX.Rands(INVERSE_MAX_SIZE);
	EXPECT_EQ( A.inv(), A.gaussianInv());
}

// 열 구하기
TEST(MATRIX_ROWMATRIX_TEST, OPERATOR){
	Matrix A("3,0,2;2,0,-2;0,1,1");
	Matrix A3("0,1,1");
	EXPECT_EQ(A(3),A3);
}

// 열 치환
TEST(MATRIX_REPLACE_ROW_TEST, REPLACE_TWO_ROW_INDEX){
	Matrix A("3,0,2;2,0,-2;0,1,1");
	Matrix B("0,1,1;2,0,-2;3,0,2");
	A.replace(1,3);
	EXPECT_EQ(A,B);
}
TEST(MATRIX_REPLACE_ROW_TEST, REPLACE_ROW_WITH_MATRIX){
	Matrix A("3,0,2;2,0,-2;0,1,1");
	Matrix row("7,7,7");
	Matrix B("3,0,2;7,7,7;0,1,1");
	A.replace(2,row);
	EXPECT_EQ(A,B);
}

// 행렬 이어붙이기  // TODO : rvalue 로  
TEST(MATRIX_CONCATENATE_TEST,OPERATOR){
	A = A<<B;
	Matrix C("1,2,2,3;3,4,4,5");
	EXPECT_EQ(A,C);
}

// 가우스 소거법
TEST(MATRIX_GAUSSIAN_ELIMINATE_TEST,PROCESS){
	Matrix A("3,0,2;2,0,-2;0,1,1");
	Matrix rref = A.RREF();
	EXPECT_EQ(rref,MATRIX.Eyes(3));
}
TEST(MATRIX_GAUSSIAN_ELIMINATE_TEST,INVERSE_MATRIX_USING_GAUSSIAN_ELIMINATE){
	Matrix A("3,0,2;2,0,-2;0,1,1");
	Matrix B("3,0,2;2,0,-2;0,1,1");
	A = A<<MATRIX.Eyes(3);
	
	EXPECT_EQ( A.RREF() , (MATRIX.Eyes(3)<<(B.inv())) );
}

// 랭크
TEST(MATRIX_RANK_TEST,VALUE1){
	Matrix A("3,0,2;2,0,-2;0,1,1");
	EXPECT_EQ(A.rank() , 3);
}
TEST(MATRIX_RANK_TEST,VALUE2){
	Matrix A("1,2;2,4");
	EXPECT_EQ(A.rank() , 1);
}
TEST(MATRIX_RANK_TEST,VALUE3){
	Matrix A("1,2;2,4;1,3;5,7");
	EXPECT_EQ(A.rank() , 2);
}

// Slice
TEST(MATRIX_SLICE_TEST,VALUE){
	Matrix A("3,0,2;2,0,-2;0,1,1");
	Matrix B = A.slice(1,1,2,2);
	Matrix result("3,0;2,0");
	EXPECT_EQ(B,result);
}

// 가우스 소거법을 이용한 역행렬
TEST(MATRIX_INVERSE_USING_GAUSSIAN_ELIMINATION_TEST,VALUE){
	Matrix A("3,0,2;2,0,-2;0,1,1");
	EXPECT_EQ(A.gaussianInv(), A.inv());
}

TEST(MATRIX_INVERSE_USING_GAUSSIAN_ELIMINATION_TEST,LARGE){
	Matrix A = MATRIX.Rands(GAUSSIAN_INVERSE_MAX_SIZE);
	EXPECT_TRUE (A.gaussianInv()!=A);
}


#endif