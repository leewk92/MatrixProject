#ifndef INDEX_H
#define INDEX_H

#include <iostream>
using namespace std;

class Index{
private:
	int row;
	int col;
	int index;
public:
	Index();
	Index(const int& index);
    Index& operator= (const int& i) ;	// conversion from int (assignment):
    operator int();	// conversion to int (type-cast operator)
};

Index::Index(){
}
Index::Index(const int& index){
	this->index = index;
}

Index& Index::operator= (const int& i){
	index = i;
	return *this;
}
Index::operator int() {
	return index;
}

#endif