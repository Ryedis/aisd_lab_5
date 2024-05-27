#include "map.cpp"
#include <gtest/gtest.h>

using namespace custom_map;

int main(){
	Map<int, int> test(10);
	test.insert(10, 13);
	test.insert(11, 23);
	test.insert(12, 33);
	test.insert(13, 43);
	test.print();
	return 0;

}

//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}