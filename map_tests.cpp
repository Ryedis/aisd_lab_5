#include "map.cpp"
#include <gtest/gtest.h>

using namespace custom_map;

TEST(CustomMapTest, InsertMethod) {
    Map<int, int> map(10);
    map.insert(10, 12);
    map.insert(10, 21);

    map.print();
    ASSERT_TRUE(map.contains(10));
}

TEST(CustomMapTest, InsertOrAssignMethod) {
    Map<int, int> map(10);
    map.insert_or_assign(10, 12);
    map.insert_or_assign(10, 21);

    map.print();
    ASSERT_TRUE(map.contains(10));
}

TEST(CustomMapTest, CopyConstructor) {
    Map<int, int> map1(10);
    map1.insert(11, 5);

    Map<int, int> map2(map1);

    ASSERT_TRUE(map2.contains(11));
}

TEST(CustomMapTest, AssignmentOperator) {
    Map<int, int> map1(10);
    map1.insert(11, 5);

    Map<int, int> map2(10);
    map2 = map1;

    ASSERT_TRUE(map2.contains(11));
}

TEST(CustomMapTest, PrintMethod) {
    Map<int, int> map(10);
    map.insert(1, 12);
    map.insert(2, 32);
    map.insert(3, 1);
    map.insert(5, 82);
    map.insert(6, 0);
    map.insert(4, 43);

    map.print();
}

TEST(CustomMapTest, ContainsMethod) {
    Map<int, int> map(10);
    map.insert(0, 7);

    ASSERT_TRUE(map.contains(0));
    ASSERT_FALSE(map.contains(1));
}

TEST(CustomMapTest, EraseMethod) {
    Map<int, int> map(10);
    map.insert(4, 12);
    map.erase(4);

    ASSERT_FALSE(map.contains(4));
}

TEST(CustomMapTest, SearchTest) {
    Map<int, int> map(10);
    map.insert(4, 12);
    
    EXPECT_EQ(*map.search(4) , 12);
    EXPECT_EQ(map.search(5), nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}