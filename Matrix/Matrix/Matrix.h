/* TODO list
 * Assert 말고 Throw 로 Exception 객체 만들어서 던지기.
 * 그 안에서 Error code 설정.
 * Refactoring 필요, 상속 및 객체지향 구조 적용
 *
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Index.h"
#include "Global.h"
#include <functional>
#include <string>
#include <map>

using namespace std;

class Matrix{
private:
	double **mat;
	int row;
	int col;
	map<string, function<double(double,double)>> functions;

	// functions
	void initializeFunctions();
	bool makeFirstLeadingEntryNotZero(Index i);
	void gaussianElimination(bool isRREF);	// ifRREF is false then it makes REF
	Matrix* operateLoop(Matrix* detMat, const Matrix& right, string _operator);
	Matrix* operateLoop(Matrix* detMat, double k , string _operator);

public:

	// Constructors
	Matrix();
	explicit  Matrix(int n);
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
	static Matrix Rands(int n);

	// functions
	Matrix& T();			// transpose
	Matrix& inv();			// inverse 
	double det();			// determinant;
	double cofactor(Index l, Index m);		// cofactor;
	Matrix& adjoint();		// adjoint matrix
	Matrix& minor();		// minor matrix
	Matrix& replace(Index firstRow,Index secondRow);
	Matrix& replace(Index detRow,const Matrix& srcMat);

	Matrix& makeREF();		// 사다리꼴 행렬
	Matrix& makeRREF();		// 기약행 사다리꼴 행렬

	int rank();
	Matrix& slice(Index colStart, Index colEnd, Index rowStart, Index rowEnd);
	Matrix& gaussianInv();			// inverse by using gaussian elimination
	

	// operator overload
	Matrix& operator+ (const Matrix& right) const;
	Matrix& operator- (const Matrix& right);
	Matrix& operator* (const Matrix& right);
	Matrix& operator+ (double k);
	Matrix& operator- (double k);
	Matrix& operator* (double k);
	Matrix& operator/ (double k);
	Matrix& operator- ();
	Matrix& operator= (const Matrix& right);
	Matrix& operator<< (const Matrix& right);

	void operator+= (double k);
	void operator-= (double k);
	void operator*= (double k);
	void operator/= (double k);

	friend bool operator== (const Matrix left, const Matrix right);
	friend bool operator!= (const Matrix left, const Matrix right);
	friend Matrix& operator+(double k, const Matrix& right);
	friend Matrix& operator*(double k, const Matrix& right);
	friend Matrix& operator-(double k, const Matrix& right);
	friend ostream& operator<<(ostream& os, const Matrix& right);
	
	//double& operator()(int l,int m);
	double& operator()(Index l,Index m);
	Matrix& operator()(Index col);

	//getter, setter
	int getRow();
	int getCol();

};

// Constructors
Matrix::Matrix(){
	initializeFunctions();
}
Matrix::Matrix(int n){
	initializeFunctions();

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
	initializeFunctions();
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

void Matrix::initializeFunctions(){
	functions["+"] = add;
	functions["-"] = sub;
	functions["*"] = mult;
	functions["/"] = devi;
}


Matrix::Matrix(string sentence){
	initializeFunctions();
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
Matrix Matrix::Rands(int n){
	srand((unsigned int)time(NULL));
	Matrix *retMat = new Matrix(n);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			retMat->mat[i][j] = (double)(rand()- RAND_MAX)*2./(double)RAND_MAX;
		}
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
	if (row==1){
		return mat[0][0];
	}
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
	int colIndex=1;
	for(int i=1; i<=col; i++){
		int rowIndex=1;
		if(i==l) continue;
		for(int j=1; j<=row; j++){			
			if(j==m) continue;			
			tmpMat(colIndex,rowIndex) = (*this)(i,j);
			rowIndex++;
		}
		colIndex++;
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
	

Matrix& Matrix::replace(Index firstRow,Index secondRow){
	assert(firstRow >=1 && secondRow >=1,"Index >=1");
	
	double* tmpRowPtr = mat[firstRow-1];
	mat[firstRow-1] = mat[secondRow-1];
	mat[secondRow-1] = tmpRowPtr;

	return *this;
}
Matrix& Matrix::replace(Index detRow,const Matrix& srcMat){
	assert(detRow >=1,"Index >=1");
	assert(srcMat.col == 1 && srcMat.row == row , "srcMatrix must have 1 column. also row number must be same with destination matrix."); 

	for(int i=0; i<row; i++){
		mat[detRow-1][i] = srcMat.mat[0][i];
	}
	return *this;
}

void Matrix::gaussianElimination(bool isRREF){
	
	for(int i=0; i<col; i++){
		
		Index iIndex = i+1;
		if(makeFirstLeadingEntryNotZero(iIndex) == false)
			continue;
		double devideFactor = 1 / mat[i][i];
		replace(iIndex,devideFactor * (*this)(iIndex));

		// 기약형 사다리꼴 행렬(RREF)을 만들기 위한 반복문
		if(isRREF == true){
			for(int upper = 0; upper < i; upper ++){
				Index refIndex = upper+1;
				if(mat[upper][i] != 0){
					double multiplyFactor =  mat[upper][i];

					replace(refIndex, (*this)(refIndex)- multiplyFactor*(*this)(iIndex));
				}
			}
		}

		for(int lower=i+1; lower<col; lower++){
			Index currColumn = lower+1;
			if(abs(mat[lower][i]) <SMALLVAL || abs(mat[i][i]) < SMALLVAL)
				continue;
			double devideFactor = mat[i][i] / mat[lower][i];

			replace(currColumn, (*this)(iIndex) - (*this)(currColumn)*devideFactor);
		}
	}
}

Matrix& Matrix::makeREF(){
	gaussianElimination(false);
	return *this;
}

Matrix& Matrix::makeRREF(){
	gaussianElimination(true);
	return *this;
}


bool Matrix::makeFirstLeadingEntryNotZero(Index iIndex){
	Index k=2;
	while(mat[iIndex-1][iIndex-1] == 0){
		if(k == col){
			break;
		}
		replace(iIndex, k++); 	
	}
	if(abs(mat[iIndex-1][iIndex-1]) < SMALLVAL)			
		return false;
	else 
		return true;
}


int Matrix::rank(){
	Matrix REF = makeREF();
	int rank=col;
	Matrix MATRIX;
	for(int i=0; i<col; i++){
		Index iIndex = i+1;
		if(REF(iIndex) == MATRIX.Zeros(1,row)){
			rank--;
		}
	}
	return rank;
}

Matrix& Matrix::slice(Index colStart,Index rowStart, Index colEnd , Index rowEnd){
	assert(colStart <= colEnd && rowStart <= rowEnd,"index of end must be equal or larger than index of start");
	assert(colEnd <= col+1 && rowEnd <= row+1,"index of end must be equal or smaller than size of matrix");
	assert(colStart >=1 && rowStart >=1 , "Index of start must be equal or larger than 1");
	Matrix *retMat = new Matrix(colEnd-colStart+1,rowEnd-rowStart+1);
	for(Index i=1; i<= retMat->col; i++){
		for(Index j=1; j<= retMat->row; j++){
			(*retMat)(i,j) = (*this)(colStart + i -1, rowStart + j -1 );
		}
	}
	return *retMat;
}

Matrix& Matrix::gaussianInv(){
	Matrix* retMat = new Matrix(col,row);
	Matrix tmp = *this;
	tmp << Eyes(col);
	*retMat = tmp.makeRREF().slice(1,row+1,col,row*2);
	return *retMat;
}


Matrix* Matrix::operateLoop(Matrix* detMat, const Matrix& right, string _operator){
	//initializeFunctions();
	function<double(double,double)> fnc = functions[_operator];
	
	for(int i=0; i<col ;i++){
		for(int j=0; j<row ;j++){
				detMat->mat[i][j] =  fnc(this->mat[i][j] , right.mat[i][j]);
		}
	}	
	return detMat;
}

Matrix* Matrix::operateLoop(Matrix* detMat, double k , string _operator){
	//initializeFunctions();
	function<double(double,double)> fnc = functions[_operator];
	
	for(int i=0; i<col ;i++){
		for(int j=0; j<row ;j++){
				detMat->mat[i][j] =  fnc(this->mat[i][j] , k);
		}
	}	
	return detMat;
}


// Operator overloadings
Matrix& Matrix::operator+ (const Matrix& right) {
	assert(row==right.row && col==right.col,"ERROR : size must be same");

	Matrix *retMat = new Matrix(col,row);
	operateLoop(retMat,right,"+");

	return *retMat;
}
Matrix& Matrix::operator- (const Matrix& right) {
	assert(row==right.row && col==right.col,"ERROR : size must be same");

	Matrix *retMat = new Matrix(col,row);
	operateLoop(retMat,right,"-");
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
	operateLoop(retMat,k,"+");
	return *retMat;
}
Matrix& Matrix::operator- (double k) {
	Matrix *retMat = new Matrix(col,row);
	operateLoop(retMat,k,"-");
	return *retMat;
}
Matrix& Matrix::operator* (double k) {
	Matrix *retMat = new Matrix(col,row);
	operateLoop(retMat,k,"*");
	return *retMat;
}
Matrix& Matrix::operator/ (double k) {
	Matrix *retMat = new Matrix(col,row);
	operateLoop(retMat,k,"/");
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
bool operator!= (const Matrix left, const Matrix right){
	assert(left.row == right.row && left.col==right.col,"size must be same");
	int col = left.col;
	int row = left.row;
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			if(abs(left.mat[i][j] - right.mat[i][j]) > SMALLVAL)			//  compare double values 
				return true;
		}
	}
	return false;
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

Matrix& Matrix::operator()(Index col){
	assert(col >=1 && col <= this->col, "1<= Index <= col ");
	Matrix *retMat = new Matrix(1,row);
	for(int i=0; i<row; i++){
		retMat->mat[0][i] = this->mat[col-1][i];
	}
	return *retMat;
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

Matrix& Matrix::operator<< (const Matrix& right){ // concatenate

	assert(col == right.col ,"col number must be same");

	Matrix *retMat = new Matrix(col, row + right.row);
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			retMat->mat[i][j] = this->mat[i][j];
		}
		for(int j=0; j<right.row; j++){
			retMat->mat[i][this->row + j] = right.mat[i][j];
		}
	}
	this->row = retMat->row;
	this->col = retMat->col;
	this->mat = retMat->mat;
	return *this;
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


// getter, setter
int Matrix::getCol(){
	return col;
}
int Matrix::getRow(){
	return row;
}




#endif