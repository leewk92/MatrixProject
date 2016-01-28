#ifndef GENERICMATRIXOPERATIONIMPL_H
#define GENERICMATRIXOPERATIONIMPL_H

#include <iostream>
#include <functional>
#include <map>

using namespace std;


template <typename CT>
class GenericMatrixOperationImpl{
protected:
	double **mat;
	int row;
	int col;
	map<string, function<double(double,double)>> functions;
	void initializeFunctions();
public:
	GenericMatrixOperationImpl();
	GenericMatrixOperationImpl(int n);
	GenericMatrixOperationImpl(int l, int m);
	GenericMatrixOperationImpl(string sentence);
	
	virtual ~GenericMatrixOperationImpl(){};

	// operator overload
	virtual CT& operator+ (const CT& right) const=0;
	virtual CT& operator- (const CT& right) const=0;
	virtual CT& operator+ (double k) const=0;
	virtual CT& operator- (double k) const=0;
	virtual CT& operator* (double k) const=0;
	virtual CT& operator/ (double k) const=0;
	virtual CT& operator- () const=0;
	virtual CT& operator= (const CT& right)=0;
	virtual CT& operator<< (const CT& right) const=0;

	virtual void operator+= (double k)=0;
	virtual void operator-= (double k)=0;
	virtual void operator*= (double k)=0;
	virtual void operator/= (double k)=0;

	// functions
	virtual CT& T()=0; 
};

#endif
