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
	Matrix(string sentence);

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
	
	double& operator()(int l,int m);
	
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

void Tokenize(const string& str, vector<string>& tokens, const string& delimiters = " ")
{
    // 맨 첫 글자가 구분자인 경우 무시
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // 구분자가 아닌 첫 글자를 찾는다
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // token을 찾았으니 vector에 추가한다
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // 구분자를 뛰어넘는다.  "not_of"에 주의하라
        lastPos = str.find_first_not_of(delimiters, pos);
        // 다음 구분자가 아닌 글자를 찾는다
        pos = str.find_first_of(delimiters, lastPos);
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
		this->row = col_string.size();
		mat[i] = new double[row];
		for(int j=0; j<row; j++){
			mat[i][j] = stod(col_string[j]);
		}
	}	
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