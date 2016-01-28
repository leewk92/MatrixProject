

#include "Matrix.h"
#include "Vector.h"
#include "GenericMatrixOperationImpl.cpp"

// Constructors
Matrix::Matrix():GenericMatrixOperationImpl(){
}
Matrix::Matrix(int n):GenericMatrixOperationImpl(n){	
}
Matrix::Matrix(int l,int m):GenericMatrixOperationImpl(l,m){
}

Matrix::Matrix(const Matrix& right){
	this->col = right.col;
	this->row = right.row;
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
//
//void Matrix::initializeFunctions(){
//	functions["+"] = add;
//	functions["-"] = sub;
//	functions["*"] = mult;
//	functions["/"] = devi;
//}

Matrix::Matrix(Vector right){
	

	this->col = right.getCol();
	this->row = right.getRow();
	bool isVertical = right.getIsVertical();
	initializeFunctions();
	this->mat = new double*[col];
	for(int i=0; i<col; i++){
		mat[i] = new double[row];
	}

	if(isVertical){
		for(int i=0; i<col; i++){
			mat[i][0] = right(i+1);
		}
	}
	else{
		for(int i=0; i<row; i++){
			mat[0][row] = right(i+1);
		}
	}
}

Matrix::Matrix(string sentence):GenericMatrixOperationImpl(sentence){
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
Matrix& Matrix::T() {
	Matrix *retMat = new Matrix(row,col);
	for(int i=0; i<retMat->col; i++){
		for(int j=0; j<retMat->row; j++){
			retMat->mat[i][j] = this->mat[j][i];
		}
	}
	return *retMat;
}

Matrix& Matrix::inv() const {			// inverse 
	assert(row == col , "row and col number must be same for calculating inverse matrix");
//	assert(det() != 0 , "determinant must not be zero for obtaining inverse matrix");
//	return 1./det() * adjoint();
	assert(elementaryRowOperationDet() != 0 , "determinant must not be zero for obtaining inverse matrix");
	return 1./elementaryRowOperationDet() * adjoint();
	
}
double Matrix::det() const {			// determinent
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



Matrix& Matrix::minor() const{
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

double Matrix::cofactor(Index l, Index m) const {
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
	//double retVal= tmpMat.det();								// original ver
	double retVal= tmpMat.elementaryRowOperationDet();			// new ver
	if((l+m) %2 != 0){
		retVal = retVal* (-1);
	}
	return retVal;
}

Matrix& Matrix::adjoint() const {		// adjoint matrix
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

Matrix& Matrix::gaussianElimination(bool isRREF) const{
	Matrix tmp = Matrix(*this);
	
	for(int i=0; i<col; i++){
		
		Index iIndex = i+1;
		if(tmp.makeFirstLeadingEntryNotZero(iIndex) == false)
			continue;
		double devideFactor = 1 / tmp.mat[i][i];
		tmp.replace(iIndex,devideFactor * (tmp)(iIndex));

		// 기약형 사다리꼴 행렬(RREF)을 만들기 위한 반복문
		if(isRREF == true){
			for(int upper = 0; upper < i; upper ++){
				Index refIndex = upper+1;
				if(tmp.mat[upper][i] != 0){
					double multiplyFactor =  tmp.mat[upper][i];

					tmp.replace(refIndex, (tmp)(refIndex)- multiplyFactor*(tmp)(iIndex));
				}
			}
		}

		for(int lower=i+1; lower<col; lower++){
			Index currColumn = lower+1;
			if(abs(tmp.mat[lower][i]) <SMALLVAL || abs(tmp.mat[i][i]) < SMALLVAL)
				continue;
			double devideFactor = tmp.mat[i][i] / tmp.mat[lower][i];

			tmp.replace(currColumn, (tmp)(iIndex) - (tmp)(currColumn)*devideFactor);
		}
	}
	Matrix *retMat = new Matrix(tmp);
	return *retMat;
}

Matrix& Matrix::REF() const{
	
	return gaussianElimination(false);
}

Matrix& Matrix::RREF() const{

	return gaussianElimination(true);
}


bool Matrix::makeFirstLeadingEntryNotZero(Index iIndex) {
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


int Matrix::rank() const {

	Matrix ref = REF();
	int rank=col;
	Matrix MATRIX;
	for(int i=0; i<col; i++){
		Index iIndex = i+1;
		if(ref(iIndex) == MATRIX.Zeros(1,row)){
			rank--;
		}
	}
	return rank;
}

Matrix& Matrix::slice(Index colStart,Index rowStart, Index colEnd , Index rowEnd) const {
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

Matrix& Matrix::gaussianInv() const {
	Matrix* retMat = new Matrix(col,row);
	Matrix tmp = *this;
	tmp = tmp << Eyes(col);
	*retMat = tmp.RREF().slice(1,row+1,col,row*2);
	return *retMat;
}


Matrix* Matrix::operateLoop(Matrix* detMat, const Matrix& right, string _operator) const{
	//initializeFunctions();
	function<double(double,double)> fnc = functions.at(_operator);
	
	for(int i=0; i<col ;i++){
		for(int j=0; j<row ;j++){
				detMat->mat[i][j] =  fnc(this->mat[i][j] , right.mat[i][j]);
		}
	}	
	return detMat;
}

Matrix* Matrix::operateLoop(Matrix* detMat, double k , string _operator) const{
	//initializeFunctions();
	function<double(double,double)> fnc = functions.at(_operator);
	
	for(int i=0; i<col ;i++){
		for(int j=0; j<row ;j++){
				detMat->mat[i][j] =  fnc(this->mat[i][j] , k);
		}
	}	
	return detMat;
}

int Matrix::makeNCommaNNotZero(Index n) {
	Index k=n+1;
	int changeNum=0;
	while(mat[n-1][n-1] == 0){
		if(k == n){
			continue;
		}
		if(k == col+1)
			k = 1;

		replace(n, k); 
		k++;
		changeNum++;
		break;
	}
	return changeNum;
}

Matrix& Matrix::elementaryRowOperation(int &changeNum) const{

	Matrix *retMat = new Matrix(*this);
	
	for(int i=0; i<col; i++){
		
		Index n = i+1;
		changeNum += retMat->makeNCommaNNotZero(n);
//		if(changeNum ==col-1)
//			continue;
		for(int j=i+1; j<col; j++){

			if(retMat->mat[j][i] == 0 ) continue;
			double devideFactor = retMat->mat[i][i]/ retMat->mat[j][i] ;
			retMat->replace(j+1, (*retMat)(j+1) - (*retMat)(i+1)/devideFactor ) ;
		}
	}
//	if(changeNum %2 == 1) (*retMat)(1,1)*(-1);

	return *retMat;
}

double Matrix::elementaryRowOperationDet() const {			// determinent
	double retVal = 1.;
	assert(row == col , "row and col number must be same for calculating determindet");
	Matrix tmp = Matrix(*this);
	int changeNum =0;
	
	Matrix resultMat = Matrix(tmp.elementaryRowOperation(changeNum));
	for(Index i=1; i<=row; i++){
		retVal *= resultMat(i,i);
	}
	
	if(changeNum %2 == 1)
		retVal *= -1;

	return retVal;
}

Matrix& Matrix::elementaryRowOperationInv() const {

	return Matrix(1);
}


// Operator overloadings

Matrix& Matrix::operator+ (const Matrix& right) const {
	assert(row==right.row && col==right.col,"ERROR : size must be same");

	Matrix *retMat = new Matrix(col,row);
	operateLoop(retMat,right,"+");

	return *retMat;
}
Matrix& Matrix::operator- (const Matrix& right) const {
	assert(row==right.row && col==right.col,"ERROR : size must be same");

	Matrix *retMat = new Matrix(col,row);
	operateLoop(retMat,right,"-");
	return *retMat;
}
Matrix& Matrix::operator* (const Matrix& right) const {

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

Matrix& Matrix::operator+ (double k) const {
	Matrix *retMat = new Matrix(col,row);
	operateLoop(retMat,k,"+");
	return *retMat;
}
Matrix& Matrix::operator- (double k) const {
	Matrix *retMat = new Matrix(col,row);
	operateLoop(retMat,k,"-");
	return *retMat;
}
Matrix& Matrix::operator* (double k) const {
	Matrix *retMat = new Matrix(col,row);
	operateLoop(retMat,k,"*");
	return *retMat;
}
Matrix& Matrix::operator/ (double k) const {
	Matrix *retMat = new Matrix(col,row);
	operateLoop(retMat,k,"/");
	return *retMat;
}

Matrix& Matrix::operator-() const{
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


bool operator== (const Matrix left, const Matrix right) {
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
bool operator!= (const Matrix left, const Matrix right) {
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



double& Matrix::operator()(Index l,Index m) const{
	
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

Matrix& Matrix::operator()(Index col) const{
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

Matrix& Matrix::operator<< (const Matrix& right) const{ // concatenate

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

	return *retMat;
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
int Matrix::getCol() const{
	return col;
}
int Matrix::getRow() const{
	return row;
}
