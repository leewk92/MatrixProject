#include <iostream>
#include <gtest\gtest.h>

int add(int a, int b){
	return a+b;
}

TEST(ADD_TEST,ADD_1_1){
	EXPECT_EQ(2,add(1,1));
}

int main(int argc, char* argv[]){
	testing::InitGoogleTest(&argc,argv);
	RUN_ALL_TESTS();

	return 0;
}