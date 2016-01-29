

#include "Vector.h"
#include "Matrix.h"

#include "GenericMatrixOperationImpl.cpp"

using namespace std;


// Constructors
Vector::Vector() : GenericMatrixOperationImpl(){

	isVertical = false;
}

Vector::Vector(int n) : GenericMatrixOperationImpl(1,n){
	isVertical = false;
}

Vector::Vector(const Vector& right){
	
	this->col = right.col;
	this->row = right.row;
	this->isVertical = right.isVertical;
	initializeFunctions();
	this->mat = new double*[col];
	for(int i=0; i<col; i++){
		mat[i] = new double[row];
	}
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			mat[i][j] = right.mat[i][j];
		}
	}
}

Vector::Vector(const Matrix& right){
	
	assert(right.getCol() == 1 || right.getRow()==1, "Vector type cast is able when row or col number is 1");

	this->col = right.getCol();
	this->row = right.getRow();
	if(col ==1){
		this->isVertical = false;
	}
	else{
		this->isVertical = true;
	}

	initializeFunctions();
	this->mat = new double*[col];
	for(int i=0; i<col; i++){
		mat[i] = new double[row];
	}
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			mat[i][j] = right(i+1,j+1);
		}
	}
}


Vector::Vector(string sentence) : GenericMatrixOperationImpl(sentence){
	assert(col==1 || row == 1 , "vector size must be (1,n) or (n,1)");
	if(col == 1)
		isVertical = false;
	else
		isVertical = true;
}

Vector::Vector(int l,int m):GenericMatrixOperationImpl(l,m){
	assert(col==1 || row == 1 , "vector size must be (1,n) or (n,1)");
	if(l == 1)
		isVertical = false;
	else if ( m == 1)
		isVertical = true;
}


// Static Factory Methods.
Vector Vector::Zeros(int n){
	Vector *retVec = new Vector(n);
	return *retVec;
}
Vector Vector::Ones(int n){
	Vector *retVec = new Vector(n);
	for(int i=0; i<n;i++){
		retVec->mat[0][i] = 1;
	}
	return *retVec;
}
Vector Vector::Rands(int n){
	srand((unsigned int)time(NULL));
	Vector *retVec = new Vector(n);
	
	for(int i=0; i<n; n++){
		retVec->mat[0][i] = (double)(rand()- RAND_MAX)*2./(double)RAND_MAX;
	}
	
	return *retVec;
}

// functions
Vector& Vector::T(){

	isVertical= !isVertical;	
	// functions

	Vector *retVec = new Vector();
	retVec->mat = new double*[row];
	for(int i=0; i<row; i++){
		retVec->mat[i] = new double[col];
	}
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			retVec->mat[i][j] = mat[j][i];
		}
	}
	retVec->row = col;
	retVec->col = row;
	retVec->isVertical = !(this->isVertical);
	
	return *retVec;
}

double Vector::dotProduct(const Vector& right) const{
	double retVal = 0;
	assert(isVertical == right.isVertical && isVertical == false, "dot product is able for parallel vectors.");
	assert(row == right.row , "dot product is able for same size vectors.");
	for(int i=0; i<row; i++){
		retVal += (*this)(i+1) * right(i+1);
	}
	return retVal;
}
Vector& Vector::crossProduct(const Vector& right) const{
	assert(isVertical == right.isVertical && isVertical == false, "cross product is able for parallel vectors.");
	assert(row == right.row && row == 3 , "cross product is able for same size vectors.");

	Matrix tmpMat(row,row);
	
	tmpMat.replace(1, Vector("1,1,1"));
	tmpMat.replace(2,*this);
	tmpMat.replace(3,right);

	Vector *retVec = new Vector(3);
	(*retVec)(1) = tmpMat.cofactor(1,1);
	(*retVec)(2) = tmpMat.cofactor(1,2);
	(*retVec)(3) = tmpMat.cofactor(1,3);

	return *retVec;
}




Vector* Vector::operateLoop(Vector* detMat, const Vector& right, string _operator) const{
	//initializeFunctions();
	function<double(double,double)> fnc = functions.at(_operator);
	
	for(int i=0; i<col ;i++){
		for(int j=0; j<row ;j++){
				detMat->mat[i][j] =  fnc(this->mat[i][j] , right.mat[i][j]);
		}
	}	
	return detMat;
}

Vector* Vector::operateLoop(Vector* detMat, double k , string _operator) const{
	//initializeFunctions();
	function<double(double,double)> fnc = functions.at(_operator);
	
	for(int i=0; i<col ;i++){
		for(int j=0; j<row ;j++){
				detMat->mat[i][j] =  fnc(this->mat[i][j] , k);
		}
	}	
	return detMat;
}

// Operator overloadings

Vector& Vector::operator+ (const Vector& right) const {
	assert(row==right.row && col==right.col,"ERROR : size must be same");

	Vector *retMat = new Vector(col,row);
	operateLoop(retMat,right,"+");

	return *retMat;
}
Vector& Vector::operator- (const Vector& right) const {
	assert(row==right.row && col==right.col,"ERROR : size must be same");

	Vector *retMat = new Vector(col,row);
	operateLoop(retMat,right,"-");
	return *retMat;
}


Vector& Vector::operator+ (double k) const {
	Vector *retMat = new Vector(col,row);
	operateLoop(retMat,k,"+");
	return *retMat;
}
Vector& Vector::operator- (double k) const {
	Vector *retMat = new Vector(col,row);
	operateLoop(retMat,k,"-");
	return *retMat;
}
Vector& Vector::operator* (double k) const {
	Vector *retMat = new Vector(col,row);
	operateLoop(retMat,k,"*");
	return *retMat;
}
Vector& Vector::operator/ (double k) const {
	Vector *retMat = new Vector(col,row);
	operateLoop(retMat,k,"/");
	return *retMat;
}

Vector& Vector::operator-() const{
	Vector *retMat = new Vector(col,row);
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			retMat->mat[i][j] = - (this->mat[i][j]);
		}
	}
	return *retMat;
}

Vector& Vector::operator= (const Vector& right){
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


bool operator== (const Vector left, const Vector right) {
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
bool operator!= (const Vector left, const Vector right) {
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



double& Vector::operator()(Index i) const{
	
	assert(i>=1 ,"index >= 1");
	if(isVertical)
		return mat[i-1][0];
	else
		return mat[0][i-1];
}

//double& Vector::operator()(int l,int m){
//	assert(l>=1 && m >=1 ,"index >= 1");
//	assert(m<=row ,"index <= row");
//	assert(l<=col ,"index <= column");
//	return mat[l-1][m-1];
//}


void Vector::operator+= (double k){
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			mat[i][j] += k;
		}
	}
}
void Vector::operator-= (double k){
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			mat[i][j] -= k;
		}
	}
}
void Vector::operator*= (double k){
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			mat[i][j] *= k;
		}
	}
}
void Vector::operator/= (double k){
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			mat[i][j] /= k;
		}
	}
}

Vector& Vector::operator<< (const Vector& right) const{ // concatenate

	assert(col == right.col ,"col number must be same");

	Vector *retMat = new Vector(col, row + right.row);
	for(int i=0; i<col; i++){
		for(int j=0; j<row; j++){
			retMat->mat[i][j] = this->mat[i][j];
		}
		for(int j=0; j<right.row; j++){
			retMat->mat[i][this->row + j] = right.mat[i][j];
		}
	}

	return *retMat;
}

// 전역함수
Vector& operator+(double k, const Vector& right){
	Vector *retMat = new Vector(right.col,right.row);
	for(int i=0; i<right.col; i++){
		for(int j=0; j<right.row; j++){
			retMat->mat[i][j] = k+right.mat[i][j];
		}
	}
	return *retMat;
}

Vector& operator-(double k, const Vector& right){
	Vector *retMat = new Vector(right.col,right.row);
	for(int i=0; i<right.col; i++){
		for(int j=0; j<right.row; j++){
			retMat->mat[i][j] =k-right.mat[i][j];
		}
	}
	return *retMat;
}

Vector& operator*(double k, const Vector& right){
	Vector *retMat = new Vector(right.col,right.row);
	for(int i=0; i<right.col; i++){
		for(int j=0; j<right.row; j++){
			retMat->mat[i][j] =k*right.mat[i][j];
		}
	}
	return *retMat;
}
Matrix& Vector::operator*(const Vector& right) const{
	assert(row==right.col,"ERROR : left.row must be same to right.col");
	
	Matrix *retMat = new Matrix(col, right.row);
	for(int i=0; i<col; i++){
		for(int j=0; j<right.row;j++){
			for(int k=0; k<row; k++){
				(*retMat)(i+1,j+1) += mat[i][k] * right.mat[k][j];				
			}
		}
	}
	return *retMat;
}


ostream& operator<<(ostream& os, const Vector& right)
{
   for(int i=0; i<right.col; i++){
		for(int j=0; j<right.row; j++){
			os <<" "<< right.mat[i][j] << " ";
		}
		os << endl;
	}
    return os;
}

int Vector::getCol(){
	return col;
}
int Vector::getRow(){
	return row;
}

bool Vector::getIsVertical(){
	return isVertical;
}