#ifndef INDEX_H
#define INDEX_H

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
	Index& operator ++();
};


#endif