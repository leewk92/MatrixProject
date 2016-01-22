/* Reference : 
 * Definition : http://matrix.skku.ac.kr/sglee/linear/ocu/thm.html
 * Gaussian Elimination : http://matrix.skku.ac.kr/sglee/linear/ocu/20104.html
 * 2016.01.21 TODO :1. determinant 성능 개선
 *					2. 오버로드된 오퍼레이터들에 const 붙여야되는것들 붙이기 v
 *					3. << left값 안바뀌게 v 
 *					4. value test 들 붙이기 v
 *					5. Vector로의 확장
 *					6. interpreter 로 인터페이스 확장 (Parser)
 *					7. Exception class 만들어붙이기
 */


#ifndef TESTS_CPP
#define TESTS_CPP
#include <gtest\gtest.h>
#include "Matrix.h"

const int INVERSE_MAX_SIZE = 4;
const int GAUSSIAN_INVERSE_MAX_SIZE = 40;

//typedef int Matrix;
static Matrix MATRIX;

Matrix Zeros = MATRIX.Zeros(2);
Matrix Eyes = MATRIX.Eyes(2);
double k = 2.;

Matrix A = Matrix("1,2;3,4");
Matrix B = Matrix("2,3;4,5");
Matrix C = Matrix("3,4;5,6");

Matrix A3 = Matrix("3,0,2;2,0,-2;0,1,1");
Matrix B3 = Matrix("1,2,6;3,4,5;1,0,5");


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
TEST(MATRIX_SUB_TEST,Value){ 
	Matrix Result = Matrix("-1 ,-1;-1,-1");
	EXPECT_EQ(A-B,Result );
}
TEST(MATRIX_SUB_TEST,CHAINING){ 
	EXPECT_EQ(-(-A), A);
}

// 행렬과 행렬 곱하기 
TEST(MATRIX_MULTIPLY_TEST,VALUE){ 
	Matrix Result = Matrix("10,13;22,29");
	EXPECT_EQ(A * B,Result);
}

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

// 행렬과 상수 더하기 
TEST(MATRIX_CONSTANT_ADD_TEST,VALUE1){
	Matrix Result = Matrix("3,4;5,6");
	EXPECT_EQ(k+A,Result);
}

TEST(MATRIX_CONSTANT_ADD_TEST,COMMUATATIVE){
	EXPECT_EQ(k+A, A+k);
}
TEST(MATRIX_CONSTANT_ADD_TEST,SELF){
	Matrix tmp_A;
	tmp_A = A;
	tmp_A += k;
	EXPECT_EQ(tmp_A, A+k);
}

// 행렬과 상수 빼기
TEST(MATRIX_CONSTANT_SUB_TEST,VALUE){ 
	Matrix Result = Matrix("-1,0;1,2");
	EXPECT_EQ(A-k, Result);
}
TEST(MATRIX_CONSTANT_SUB_TEST,OTHER_COMMUTATIVE){ 
	EXPECT_EQ(k-A, -(A-k));
}
TEST(MATRIX_CONSTANT_SUB_TEST,SELF){
	Matrix tmp_A;
	tmp_A = A;
	tmp_A -=k;
	EXPECT_EQ(tmp_A, A-k);
}

// 행렬과 상수 곱하기 
TEST(MATRIX_CONSTANT_MULTIPLY_TEST,VALUE){
	Matrix Result = Matrix("2,4;6,8");
	EXPECT_EQ(k*A, Result);
}
TEST(MATRIX_CONSTANT_MULTIPLY_TEST,COMMUATATIVE){
	EXPECT_EQ(k*A, A*k);
}
TEST(MATRIX_CONSTANT_MULTIPLY_TEST,SELF){ 
	Matrix tmp_A;
	tmp_A = A;
	tmp_A *=k;
	EXPECT_EQ(tmp_A, A*k);
}

// 행렬과 상수 나누기 
TEST(MATRIX_CONSTANT_DEVIDE_TEST,VALUE){	
	Matrix Result("0.5,1;1.5,2");
	EXPECT_EQ(A/k, Result);
}
TEST(MATRIX_CONSTANT_DEVIDE_TEST,COMMUTATIVE){		
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


// 특정 원소 수정 
TEST(MATRIX_SPECIFIC_TEST,ACCESSOR){
	
	EXPECT_EQ(A(1,2),2);
}

TEST(MATRIX_SPECIFIC_TEST,MUTATOR){
	Matrix tmpA("1,2,3;4,5,6;7,8,9");
	Matrix tmpB("1,2,3;1,5,6;7,4,9");
	tmpA(2,1) = 1;
	tmpA(3,2) = 4;

	EXPECT_EQ(tmpA,tmpB);
}

// 단위행렬 테스트
TEST(MATRIX_EYES_TEST,VALUE){
	Matrix Eyes4 = MATRIX.Eyes(4);
	Matrix Result("1,0,0,0;0,1,0,0;0,0,1,0;0,0,0,1");
	EXPECT_EQ(Eyes4,Result);
}
TEST(MATRIX_EYES_TEST,IDENTITY){
	EXPECT_EQ(A,A*Eyes);
}
TEST(MATRIX_EYES_TEST,COMMUTATIVE){
	EXPECT_EQ(Eyes*A,A*Eyes);
}

// 소행렬 테스트
TEST(MATRIX_MINOR_TEST,VALUE){

	Matrix result("2,2,2;-2,3,3;0,-10,0");

	EXPECT_EQ(A3.minor(), result);
}

// 수반행렬 테스트
TEST(MATRIX_ADJOINT_TEST,VALUE){

	Matrix result("2,2,0;-2,3,10;2,-3,0");

	EXPECT_EQ(A3.adjoint(), result);
}
TEST(MATRIX_ADJOINT_TEST,INVERSE){ // 정리 21

	//EXPECT_EQ(A.inv(), 1/A.det()*A.adjoint());
	EXPECT_EQ(A3.inv(), 1/A3.det()*A3.adjoint());
}


// 행렬식 테스트
TEST(MATRIX_DETERMINENT_TEST,VALUE){
	double A3_det_result = 10.;
	EXPECT_DOUBLE_EQ(A3.det(), A3_det_result);
}
TEST(MATRIX_DETERMINENT_TEST,TRANSPOSE){ //정리 11
	EXPECT_DOUBLE_EQ(A.det(), A.T().det());
	//EXPECT_DOUBLE_EQ(A3.det(), A3.T().det());
}
TEST(MATRIX_DETERMINENT_TEST,DISTRIBUTION_FOR_MULTIPLY){ // 정리 18

	EXPECT_DOUBLE_EQ( (A*B).det() , A.det() * B.det() );
	EXPECT_DOUBLE_EQ( (A3*B3).det() , A3.det() * B3.det() );
}
TEST(MATRIX_DETERMINENT_TEST,REVERSE_FOR_INVERSE){ // 정리 18

	EXPECT_DOUBLE_EQ( (A.inv()).det() , 1/A.det() );
	EXPECT_DOUBLE_EQ( (A3.inv()).det() , 1/A3.det() );
}


// 역행렬 테스트 : 정리 7
TEST(MATRIX_INVERSE_TEST,VALUE){
	Matrix A3_Inv_result("0.2,0.2,0;-0.2,0.3,1;0.2,-0.3,0");
	EXPECT_EQ(A3.inv(), A3_Inv_result);
}
TEST(MATRIX_INVERSE_TEST,CHAINING){
	//Matrix A("3,0,2;2,0,-2;0,1,1");
	EXPECT_EQ(A.inv().inv(), A);
	//EXPECT_EQ(A3.inv().inv(), A3);
}
TEST(MATRIX_INVERSE_TEST,REVERSE){
	//Matrix A("3,0,2;2,0,-2;0,1,1");
	//Matrix B("1,2,6;3,4,5;1,0,5");
	EXPECT_EQ( (A*B).inv(), B.inv() * A.inv() );
	EXPECT_EQ( (A3*B3).inv(), B3.inv() * A3.inv() );
}
TEST(MATRIX_INVERSE_TEST, COMMUTATIVE_FOR_TRANSPOSE){

	EXPECT_EQ( (A.T()).inv(), (A.inv()).T());
	EXPECT_EQ( (A3.T()).inv(), (A3.inv()).T());
}
TEST(MATRIX_INVERSE_TEST, DISTRIBUTION_FOR_CONSTANT){

	EXPECT_EQ( (k*A).inv(), 1/k*A.inv());
	EXPECT_EQ( (k*A3).inv(), 1/k*A3.inv());
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
TEST(MATRIX_ROWMATRIX_TEST, VALUE){

	Matrix ThirdRowOfA("0,1,1");
	EXPECT_EQ(A3(3),ThirdRowOfA);
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
	Matrix tmpA = A<<B;
	Matrix C("1,2,2,3;3,4,4,5");
	EXPECT_EQ(tmpA,C);
}

// 가우스 소거법
TEST(MATRIX_GAUSSIAN_ELIMINATE_TEST,PROCESS){
	Matrix rref = A3.RREF();
	EXPECT_EQ(rref,MATRIX.Eyes(3));
}
TEST(MATRIX_GAUSSIAN_ELIMINATE_TEST,INVERSE_MATRIX_USING_GAUSSIAN_ELIMINATE){
	cout << A3;
	Matrix tmpA3 = A3<<MATRIX.Eyes(3);
	cout << endl<<tmpA3.RREF();
	EXPECT_EQ( tmpA3.RREF() , (MATRIX.Eyes(3)<<(A3.inv())) );
}

// 랭크
TEST(MATRIX_RANK_TEST,VALUE1){

	EXPECT_EQ(A3.rank() , 3);
}
TEST(MATRIX_RANK_TEST,VALUE2){
	Matrix tmpA("1,2;2,4");
	EXPECT_EQ(tmpA.rank() , 1);
}
TEST(MATRIX_RANK_TEST,VALUE3){
	Matrix tmpA("1,2;2,4;1,3;5,7");
	EXPECT_EQ(tmpA.rank() , 2);
}

// Slice
TEST(MATRIX_SLICE_TEST,VALUE){

	Matrix tmpA3 = A3.slice(1,1,2,2);
	Matrix result("3,0;2,0");
	EXPECT_EQ(tmpA3,result);
}

// 가우스 소거법을 이용한 역행렬
TEST(MATRIX_INVERSE_USING_GAUSSIAN_ELIMINATION_TEST,VALUE){

	EXPECT_EQ(A.gaussianInv(), A.inv());
	//EXPECT_EQ(A3.gaussianInv(), A3.inv());
}

TEST(MATRIX_INVERSE_USING_GAUSSIAN_ELIMINATION_TEST,LARGE){
	Matrix tmpA = MATRIX.Rands(GAUSSIAN_INVERSE_MAX_SIZE);
	EXPECT_TRUE (tmpA.gaussianInv()!=tmpA);
}

TEST(LU_DECOMPOSITION,MULTIPY){
	Matrix tmpA("4,3;6,3");
	Matrix tmpB("1,0;1.5,1");
	Matrix tmpC("4,3;0,-1.5");
	EXPECT_EQ(tmpA.det(),tmpB.det() * tmpC.det());
}


TEST(TRIANGULAR_DETERMINANT,VALUE){
	Matrix tmpA("3,5,6;0,6,4;0,0,4");

	EXPECT_EQ(tmpA.det(),4*6*3);
}
TEST(TRIANGULAR_DETERMINANT,VALUE2){
	Matrix tmpA("1,-5,6,-3;3,-1,1,-2;4,-5,4,-5;3,-4,-3,-6");

	EXPECT_EQ(tmpA.det(),1*7*3*3/7);
}

TEST(TRIANGULAR_DETERMINANT,VALUE4){
	Matrix tmpA("1,7,2,5;2,4,3,6;5,4,2,9;3,3,1,2");
	cout << "1.det : " << tmpA.det()<<endl;
	EXPECT_DOUBLE_EQ(tmpA.det(),1*-10*-4.9*(-5.8+3.2/4.9*3.6));
}
TEST(TRIANGULAR_DETERMINANT,VALUE5){
	Matrix tmpA("2,4,3,6;1,7,2,5;5,4,2,9;3,3,1,2");
	cout << "2.det : " <<tmpA.det()<<endl;
	EXPECT_DOUBLE_EQ(tmpA.det(),-49*(-5.8+3.6/4.9*3.2));
}

// elementaryRowOperation
TEST(ELEMENTARY_ROW_OPERATION_TEST,VALUE){
	Matrix tmpA("2,4,3,6;1,7,2,5;5,4,2,9;3,3,1,2");
	cout << tmpA.elementaryRowOperation();
	EXPECT_DOUBLE_EQ(tmpA.det(),-49*(-5.8+3.6/4.9*3.2));
}

// 행렬식 using elementaryRowOperation
TEST(DET_ELEMENTARY_ROW_OPERATION_TEST,VALUE1){
	Matrix tmpA("2,4,3,6;1,7,2,5;5,4,2,9;3,3,1,2");
	EXPECT_DOUBLE_EQ(tmpA.det(), tmpA.elementaryRowOperationDet());
}

TEST(DET_ELEMENTARY_ROW_OPERATION_TEST,VALUE2){
	
	EXPECT_DOUBLE_EQ(A.det(), A.elementaryRowOperationDet());
}

TEST(DET_ELEMENTARY_ROW_OPERATION_TEST,VALUE3){

	EXPECT_DOUBLE_EQ(A3.det(), A3.elementaryRowOperationDet());
}
#endif