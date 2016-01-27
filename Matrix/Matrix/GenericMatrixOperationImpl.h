#ifndef GENERICMATRIXOPERATIONIMPL_H
#define GENERICMATRIXOPERATIONIMPL_H

#include <iostream>
#include <functional>

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

template<typename CT>
GenericMatrixOperationImpl<CT>::GenericMatrixOperationImpl(){
	initializeFunctions();
}

template<typename CT>
GenericMatrixOperationImpl<CT>::GenericMatrixOperationImpl(int n){
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
template <typename CT>
GenericMatrixOperationImpl<CT>::GenericMatrixOperationImpl(int l,int m){
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

template <typename CT>
void GenericMatrixOperationImpl<CT>::initializeFunctions(){
	functions["+"] = add;
	functions["-"] = sub;
	functions["*"] = mult;
	functions["/"] = devi;
}

template<typename CT>
GenericMatrixOperationImpl<CT>::GenericMatrixOperationImpl(string sentence){
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

#endif
