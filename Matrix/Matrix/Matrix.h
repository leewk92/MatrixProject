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
#include <functional>
#include <string>
#include <map>
#include <cassert>
#include "Index.h"
#include "Global.h"
#include "GenericMatrixOperationImpl.h"

class Vector;

using namespace std;

class Matrix : public GenericMatrixOperationImpl<Matrix> {
	
protected:
	
	// functions
	//void initializeFunctions();
	bool makeFirstLeadingEntryNotZero(Index i);
	int makeNCommaNNotZero(Index n);
	Matrix& gaussianElimination(bool isRREF) const ;	// ifRREF is false then it makes REF
	Matrix* operateLoop(Matrix* detMat, const Matrix& right, string _operator) const;
	Matrix* operateLoop(Matrix* detMat, double k , string _operator) const;

public:
	
	// Constructors
	Matrix();
	Matrix(Vector right);
	explicit Matrix(int n);
	Matrix(int l,int m);
	explicit Matrix(string sentence);
	Matrix(const Matrix& matrix);
	

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
	Matrix& T() override;			// transpose
	Matrix& inv() const;			// inverse 
	double det() const;			// determinant;
	double cofactor(Index l, Index m) const;		// cofactor;
	Matrix& adjoint() const;		// adjoint matrix
	Matrix& minor() const;		// minor matrix
	Matrix& replace(Index firstRow,Index secondRow);
	Matrix& replace(Index detRow,const Matrix& srcMat);

	Matrix& REF() const;		// 사다리꼴 행렬
	Matrix& RREF() const;		// 기약행 사다리꼴 행렬

	int rank() const;
	Matrix& slice(Index colStart, Index colEnd, Index rowStart, Index rowEnd) const;
	Matrix& gaussianInv() const;			// inverse by using gaussian elimination
	Matrix& elementaryRowOperationInv() const;			
	Matrix& elementaryRowOperation(int &changeNum) const;
	double elementaryRowOperationDet() const;

	// operator overriding 
	Matrix& operator+ (const Matrix& right) const override;
	Matrix& operator- (const Matrix& right) const override;
	Matrix& operator+ (double k) const override;
	Matrix& operator- (double k) const override;
	Matrix& operator* (double k) const override;
	Matrix& operator/ (double k) const override;
	Matrix& operator- () const override;
	Matrix& operator= (const Matrix& right) override;
	Matrix& operator<< (const Matrix& right) const override;

	void operator+= (double k) override;
	void operator-= (double k) override;
	void operator*= (double k) override;
	void operator/= (double k) override;

	Matrix& operator* (const Matrix& right) const;

	friend bool operator== (const Matrix left, const Matrix right);
	friend bool operator!= (const Matrix left, const Matrix right);
	friend Matrix& operator+(double k, const Matrix& right);
	friend Matrix& operator*(double k, const Matrix& right);
	friend Matrix& operator-(double k, const Matrix& right);
	friend ostream& operator<<(ostream& os, const Matrix& right);
	
	//double& operator()(int l,int m);
	double& operator()(Index l,Index m) const;
	Matrix& operator()(Index col) const;
	
	//getter, setter
	int getRow() const;
	int getCol() const;

};




#endif