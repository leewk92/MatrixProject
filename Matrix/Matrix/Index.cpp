#include "Index.h"


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
Index& Index::operator++(){
	index += 1;
	return *this;
}