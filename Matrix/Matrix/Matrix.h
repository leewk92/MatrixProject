/* TODO list
 * Assert 말고 Throw 로 Exception 객체 만들어서 던지기.
 * 그 안에서 Error code 설정.
 * Refactoring 필요, 상속 및 객체지향 구조 적용
 *
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <deque>
#include "Index.h"
using namespace std;

const double SMALLVAL = 0.0000001;

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
	Matrix(string sentence);

	// Destructor
	~Matrix();
	// static Factory methods
	static Matrix Zeros(int n);
	static Matrix Zeros(int l,int m);
	static Matrix Ones(int n);
	static Matrix Ones(int l, int m);
	static Matrix Eyes(int n);
	
	// functions
	Matrix& T();			// transpose
	Matrix& inv();			// inverse 
	double det();			// determinant;
	double cofactor(Index l, Index m);		// cofactor;
	Matrix& adjoint();		// adjoint matrix
	Matrix& minor();		// minor matrix

	// operator overload
	Matrix& operator+ (const Matrix& right);
	Matrix& operator- (const Matrix& right);
	Matrix& operator* (const Matrix& right);
	Matrix& operator+ (double k);
	Matrix& operator- (double k);
	Matrix& operator* (double k);
	Matrix& operator/ (double k);
	Matrix& operator- ();
	Matrix& operator= (const Matrix& right);



	void operator+= (double k);
	void operator-= (double k);
	void operator*= (double k);
	void operator/= (double k);

	friend bool operator== (const Matrix left, const Matrix right);
	friend Matrix& operator+(double k, const Matrix& right);
	friend Matrix& operator*(double k, const Matrix& right);
	friend Matrix& operator-(double k, const Matrix& right);
	friend ostream& operator<<(ostream& os, const Matrix& right);
	
	//double& operator()(int l,int m);
	double& operator()(Index l,Index m);
	
	//getter, setter
	int getRow();
	int getCol();

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

void Tokenize(const string& str, vector<string>& tokens, const string& silcer = " ")
{
    // 맨 첫 글자가 구분자인 경우 무시
    string::size_type lastPos = str.find_first_not_of(silcer, 0);
    // 구분자가 아닌 첫 글자를 찾는다
    string::size_type pos = str.find_first_of(silcer, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // token을 찾았으니 vector에 추가한다
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // 구분자를 뛰어넘는다. 
        lastPos = str.find_first_not_of(silcer, pos);
        // 다음 구분자가 아닌 글자를 찾는다
        pos = str.find_first_of(silcer, lastPos);
    }
}

Matrix::Matrix(string sentence){
	vector<string> row_string;
	//assert(sentence[0] =='[' && sentence[sentence.size()-1]==']',"sentence must be start with '[' and end with ']'");
	Tokenize(sentence, row_string,";");
	this->col = row_string.size();
	mat = new double*[col];
	for(int i=0; i<col; i++){
		vector<string> col_string;
		Tokenize(row_string[i],col_string,",");
		if(i !=0) {
			assert(this->row == col_string.size(),"row size must be consistent");
		}
		this->row = col_string.size();
		mat[i] = new double[row];
		for(int j=0; j<row; j++){
			mat[i][j] = stod(col_string[j]);
		}
	}	
}

// Destructor
Matrix::~Matrix(){
}

// static factory methods
Matrix Matrix::Zeros(int n){
	Matrix *retMat = new Matrix(n);
	return *retMat;
}
Matrix Matrix::Zeros(int l,int m){
	Matrix *retMat = new Matrix(l,m);
	return *retMat;
}

Matrix Matrix::Ones(int n){
	Matrix *retMat = new Matrix(n);
	for(int i=0; i<n; i++){
		for(int j=0; j<n;j++){
			retMat->mat[i][j] = 1;
		}
	}
	return *retMat;
}
Matrix Matrix::Ones(int l,int m){
	Matrix *retMat = new Matrix(l,m);
	for(int i=0; i<l; i++){
		for(int j=0; j<m;j++){
			retMat->mat[i][j] = 1;
		}
	}
	return *retMat;
}
Matrix Matrix::Eyes(int n){
	Matrix *retMat = new Matrix(n);
	for(int i=0; i<n; i++){
		retMat->mat[i][i] = 1;
	}
	return *retMat;
}

// functions
Matrix& Matrix::T(){
	Matrix *retMat = new Matrix(row,col);
	for(int i=0; i<retMat->col; i++){
		for(int j=0; j<retMat->row; j++){
			retMat->mat[i][j] = this->mat[j][i];
		}
	}
	return *retMat;
}

Matrix& Matrix::inv(){			// inverse 
	assert(row == col , "row and col number must be same for calculating inverse matrix");
	assert(det() != 0 , "determinant must not be zero for obtaining inverse matrix");
	return 1./det() * adjoint();
}
double Matrix::det(){			// determinent
	double retVal = 0.;

	assert(row == col , "row and col number must be same for calculating determindet");
	if(row == 2){
		retVal = mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
		return retVal;
	}
	Matrix minorMatrix;
	minorMatrix = minor();
	for(int i=1; i<=row; i++){
		retVal += (*this)(1,i) * minorMatrix(1,i) * pow(-1,(i+1));
	}
	return retVal;
}

Matrix& Matrix::minor(){
	assert(row == col , "row and col number must be same for calculating minor matrix");
	Matrix* retMat = new Matrix(col,row);
	for(int i=1; i<=col; i++){
		for(int j=1; j<=row; j++){
			(*retMat)(i,j) = cofactor(i,j);	
			if((i+j) %2 ==1)	
				(*retMat)(i,j) *= -1;
		}
	}
	return *retMat;
}

double Matrix::cofactor(Index l, Index m){
	Matrix tmpMat(col-1,row-1);
	int col_index=1;
	for(int i=1; i<=col; i++){
		int row_index=1;
		if(i==l) continue;
		for(int j=1; j<=row; j++){			
			if(j==m) continue;			
			tmpMat(col_index,row_index) = (*this)(i,j);
			row_index++;
		}
		col_index++;
	}
	double retVal= tmpMat.det();
	
	if((l+m) %2 != 0){
		retVal = retVal* (-1);
	}
	return retVal;
}

Matrix& Matrix::adjoint(){		// adjoint matrix
	Matrix* retMat = new Matrix(col,row);
	*retMat = minor();
	for(int i=1; i<=col; i++){
		for(int j=1; j<=row; j++){
			if((i+j) %2 == 1){
				(*retMat)(i,j) *= -1;		
			}
		}
	}
	return (*retMat).T();
}
	

// Operator overloadings
Matrix& Matrix::operator+ (const Matrix& right) {
	assert(row==right.row && col==right.col,"ERROR : size must be same");

	Matrix *retMat = new Matrix(col,row);
	for(int i=0; i<col ;i++){
		for(int j=0; j<row ;j++){
			retMat->mat[i][j] = this->mat[i][j] + right.mat[i][j];
		}
	}
	return *retMat;
}
Matrix& Matrix::operator- (const Matrix& right) {
	assert(row==right.row && col==right.col,"ERROR : size must be same");

	Matrix *retMat = new Matrix(col,row);
	for(int i=0; i<col ;i++){
		for(int j=0; j<row ;j++){
			retMat->mat[i][j] = this->mat[i][j] - right.mat[i][j];
		}
	}
	return *retMat;
}
Matrix& Matrix::operator* (const Matrix& right) {
	assert(row==right.col,"ERROR : left.row must be same to right.col");
	
	Matrix *retMat = new Matrix(this->col, right.row);
	for(int i=0; i<this->col; i++){
		for(int j=0; j<right.row;j++){
			for(int k=0; k<this->row; k++){
				retMat->mat[i][j] += this->mat[i][k] * right.mat[k][j];				
			}
		}
	}
	return *retMat;
}

Matrix& Matrix::operator+ (double k) {
	Matrix *retMat = new Matrix(col,row);
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			retMat->mat[i][j] =mat[i][j]+k;
		}
	}
	return *retMat;
}
Matrix& Matrix::operator- (double k) {
	Matrix *retMat = new Matrix(col,row);
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			retMat->mat[i][j] =mat[i][j]-k;
		}
	}
	return *retMat;
}
Matrix& Matrix::operator* (double k) {
	Matrix *retMat = new Matrix(col,row);
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			retMat->mat[i][j] =mat[i][j]*k;
		}
	}
	return *retMat;
}
Matrix& Matrix::operator/ (double k) {
	Matrix *retMat = new Matrix(col,row);
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			retMat->mat[i][j] = mat[i][j]/k;
		}
	}
	return *retMat;
}
Matrix& Matrix::operator-(){
	Matrix *retMat = new Matrix(col,row);
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			retMat->mat[i][j] = - (this->mat[i][j]);
		}
	}
	return *retMat;
}

Matrix& Matrix::operator= (const Matrix& right){
	row = right.row;
	col = right.col;
	mat = new double*[col];
	for(int i=0; i<col; i++){
		mat[i] = new double[row];
		for(int j=0; j<row; j++){
			mat[i][j] = right.mat[i][j];
		}
	}
	return *this;
}

bool operator== (const Matrix left, const Matrix right){
	assert(left.row == right.row && left.col==right.col,"size must be same");
	int col = left.col;
	int row = left.row;
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			if(abs(left.mat[i][j] - right.mat[i][j]) > SMALLVAL)			//  compare double values 
				return false;
		}
	}
	return true;
}


double& Matrix::operator()(Index l,Index m){
	
	assert(l>=1 && m >=1 ,"index >= 1");
	assert(m<=row ,"index <= row");
	assert(l<=col ,"index <= column");
	return mat[l-1][m-1];
}


//double& Matrix::operator()(int l,int m){
//	assert(l>=1 && m >=1 ,"index >= 1");
//	assert(m<=row ,"index <= row");
//	assert(l<=col ,"index <= column");
//	return mat[l-1][m-1];
//}


void Matrix::operator+= (double k){
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			mat[i][j] += k;
		}
	}
}
void Matrix::operator-= (double k){
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			mat[i][j] -= k;
		}
	}
}
void Matrix::operator*= (double k){
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			mat[i][j] *= k;
		}
	}
}
void Matrix::operator/= (double k){
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			mat[i][j] /= k;
		}
	}
}



// 전역함수
Matrix& operator+(double k, const Matrix& right){
	Matrix *retMat = new Matrix(right.col,right.row);
	for(int i=0; i<right.col; i++){
		for(int j=0; j<right.row; j++){
			retMat->mat[i][j] = k+right.mat[i][j];
		}
	}
	return *retMat;
}

Matrix& operator-(double k, const Matrix& right){
	Matrix *retMat = new Matrix(right.col,right.row);
	for(int i=0; i<right.col; i++){
		for(int j=0; j<right.row; j++){
			retMat->mat[i][j] =k-right.mat[i][j];
		}
	}
	return *retMat;
}

Matrix& operator*(double k, const Matrix& right){
	Matrix *retMat = new Matrix(right.col,right.row);
	for(int i=0; i<right.col; i++){
		for(int j=0; j<right.row; j++){
			retMat->mat[i][j] =k*right.mat[i][j];
		}
	}
	return *retMat;
}

ostream& operator<<(ostream& os, const Matrix& right)
{
   for(int i=0; i<right.col; i++){
		for(int j=0; j<right.row; j++){
			os <<" "<< right.mat[i][j] << " ";
		}
		os << endl;
	}
    return os;
}


#endif