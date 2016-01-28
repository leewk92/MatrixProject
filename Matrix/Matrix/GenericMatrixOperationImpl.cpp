#include "GenericMatrixOperationImpl.h"


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
