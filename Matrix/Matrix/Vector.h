#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;

class Vector : public Matrix {
private:
	bool isVertical;
public:
	Vector();
	Vector(int n);
	Vector(string s);
	Vector(const Matrix& m);

	// static factory methods
	static Vector Zeros(int n);
	static Vector Ones(int n);
	static Vector Rands(int n);

	//functions
	virtual Vector& T() ;
};

Vector::Vector(){
	Matrix();
	isVertical = false;
}

Vector::Vector(int n) : Matrix(1,n){
	isVertical = false;
}

Vector::Vector(const Matrix& m) : Matrix(m){
	if(m.getCol() == 1 && m.getRow() != 1){
		isVertical = false;
	}else if(m.getCol() != 1 && m.getRow() == 1){
		isVertical = true;
	}
}

Vector::Vector(string sentence) : Matrix(sentence){
	assert(col==1 || row == 1 , "vector size must be (1,n) or (n,1)");
}

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
	Vector *retVec = new Vector(Matrix::T());
	return *retVec;
}


#endif
