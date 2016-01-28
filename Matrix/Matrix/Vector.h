#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "Global.h"
#include "GenericMatrixOperationImpl.h"


using namespace std;

class Matrix;
class Index;

class Vector : public GenericMatrixOperationImpl<Vector>  {

private:
	bool isVertical;
	Vector(int l, int m);
	Vector* operateLoop(Vector* detMat, const Vector& right, string _operator) const;
	Vector* operateLoop(Vector* detMat, double k , string _operator) const;

public:

	// Constructor
	Vector();
	Vector(int n);
	explicit Vector(string s);
	Vector(const Matrix& right);
	Vector(const Vector& right);

	// Destructor
	~Vector(){};

	// static factory methods
	static Vector Zeros(int n);
	static Vector Ones(int n);
	static Vector Rands(int n);

	//functions
	Vector& T() override;
	double dotProduct(const Vector& right) const;
	Vector& crossProduct(const Vector& right) const;


	// operator overriding 
	Vector& operator+ (const Vector& right) const override;
	Vector& operator- (const Vector& right) const override;
	Vector& operator+ (double k) const override;
	Vector& operator- (double k) const override;
	Vector& operator* (double k) const override;
	Vector& operator/ (double k) const override;
	Vector& operator- () const override;
	Vector& operator= (const Vector& right) override;
	Vector& operator<< (const Vector& right) const override;
	
	Matrix& operator*(const Vector& right) const;
	
	void operator+= (double k) override;
	void operator-= (double k) override;
	void operator*= (double k) override;
	void operator/= (double k) override;

	friend bool operator== (const Vector left, const Vector right);
	friend bool operator!= (const Vector left, const Vector right);
	friend Vector& operator+(double k, const Vector& right);
	friend Vector& operator*(double k, const Vector& right);

	friend Vector& operator-(double k, const Vector& right);
	friend ostream& operator<<(ostream& os, const Vector& right);

	double& operator()(Index i) const;

	int getCol();
	int getRow();
	bool getIsVertical();
};

#endif
