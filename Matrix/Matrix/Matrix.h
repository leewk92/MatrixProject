/* TODO list
 * Assert 말고 Throw 로 Exception 객체 만들어서 던지기.
 * 그 안에서 Error code 설정.
 * Refactoring 필요, 상속 및 객체지향 구조 적용
 *
 */



#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

class Matrix{
private:
	double **mat;
	int row;
	int col;
public:

	// Constructors
	Matrix();
	Matrix(int n);
	Matrix(int l,int m);

	// static Factory methods
	static Matrix Zeros(int n);
	static Matrix Zeros(int l,int m);
	static Matrix Ones(int n);
	static Matrix Ones(int l, int m);
	static Matrix Eyes(int n);
	

	// operator overload
	Matrix& operator+ (const Matrix& right);
	Matrix& operator- (const Matrix& right);
	Matrix& operator* (const Matrix& right);
	Matrix& operator+ (double k);
	Matrix& operator- (double k);
	Matrix& operator* (double k);
	Matrix& operator/ (double k);
	Matrix& operator- ();
	friend bool operator== (const Matrix left, const Matrix right);
	friend Matrix& operator+(double k, const Matrix& right);
	friend Matrix& operator*(double k, const Matrix& right);
	friend Matrix& operator-(double k, const Matrix& right);
	
	double& operator()(int l,int m);
		
	//getter, setter
	int getRow();
	int getCol();

	//print 
	void print();
};

// Constructors
Matrix::Matrix(){
}
Matrix::Matrix(int n){
	this->mat = new double*[n];
	for(int i=0; i<n; i++){
		mat[i] = new double[n];
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			mat[i][j] = 0;
		}
	}
	this->row = n;
	this->col = n;
}
Matrix::Matrix(int l,int m){
	this->mat = new double*[l];
	for(int i=0; i<l; i++){
		mat[i] = new double[m];
	}
	for(int i=0; i<l; i++){
		for(int j=0; j<m; j++){
			mat[i][j] = 0;
		}
	}
	this->col = l;
	this->row = m;
}

// static factory methods
Matrix Matrix::Zeros(int n){
	Matrix retMat = Matrix(n);
	return retMat;
}
Matrix Matrix::Zeros(int l,int m){
	Matrix retMat = Matrix(l,m);
	return retMat;
}


// Operator overloadings
Matrix& Matrix::operator+ (const Matrix& right) {
	cout << row << ","<<col<<endl;
	cout << right.row << ","<<right.col<<endl;
	assert(row==right.row && col==right.col,"ERROR : size must be same");

	Matrix retMat(col,row);
	for(int i=0; i<col ;i++){
		for(int j=0; j<row ;j++){
			retMat.mat[i][j] = this->mat[i][j] + right.mat[i][j];
		}
	}
//	retMat.col = col;
//	retMat.row = row;
	return retMat;
}
Matrix& Matrix::operator- (const Matrix& right) {
	Matrix retMat;
	return retMat;
}
Matrix& Matrix::operator* (const Matrix& right) {
	Matrix retMat;
	return retMat;
}
Matrix& Matrix::operator+ (double k) {
	Matrix retMat;
	return retMat;
}
Matrix& Matrix::operator- (double k) {
	Matrix retMat;
	return retMat;
}
Matrix& Matrix::operator* (double k) {
	Matrix retMat;
	return retMat;
}
Matrix& Matrix::operator/ (double k) {
	Matrix retMat;
	return retMat;
}
Matrix& Matrix::operator-(){
	Matrix retMat;
	return retMat;
}
bool operator== (const Matrix left, const Matrix right){
	assert(left.row == right.row && left.col==right.col,"size must be same");
	int col = left.col;
	int row = left.row;
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			if(left.mat[i][j] != right.mat[i][j])
				return false;
		}
	}
	return true;
}

double& Matrix::operator()(int l,int m){
	assert(l>=1 && m >=1 ,"index >= 1");
	assert(m<=row ,"index <= row");
	assert(l<=col ,"index <= column");
	return mat[l-1][m-1];
}

void Matrix::print(){
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			cout <<" "<< mat[i][j] << " ";
		}
		cout << endl;
	}
}


// 전역함수
Matrix& operator+(double k, const Matrix& right){
	Matrix retMat;
	return retMat;
}

Matrix& operator-(double k, const Matrix& right){
	Matrix retMat;
	return retMat;
}

Matrix& operator*(double k, const Matrix& right){
	Matrix retMat;
	return retMat;
}




#endif