#include "tuple.hpp"

#include <cstddef>
#include <gtest/gtest.h>

using namespace lghazarosyan;

TEST(TestTuple, testTupleWithBuildInType){
    lghazarosyan::tuple<int, int, int> tuple{1, 2, 3};
    EXPECT_EQ(lghazarosyan::get<int>(tuple), 1);
    EXPECT_EQ(lghazarosyan::get<0>(tuple), 1);
    EXPECT_EQ(lghazarosyan::get<1>(tuple), 2);
    EXPECT_EQ(lghazarosyan::get<2>(tuple), 3);
    auto tupo = tuple;
    lghazarosyan::tuple<int, int, int> tup{4, 5, 4};
    EXPECT_EQ(tupo, tuple);
    EXPECT_EQ(lghazarosyan::get<0>(tupo), 1);
    EXPECT_EQ(lghazarosyan::get<1>(tupo), 2);
    EXPECT_EQ(lghazarosyan::get<2>(tupo), 3);
    lghazarosyan::tuple<lghazarosyan::tuple<int, int, int>, lghazarosyan::tuple<int, int, int>, int, int> tuple1(tuple, tup, 1, 2);
    EXPECT_EQ(lghazarosyan::get<0>(tuple1), tuple);
    EXPECT_EQ(lghazarosyan::get<1>(tuple1), tup);
    EXPECT_EQ(lghazarosyan::get<2>(tuple1), 1);
    EXPECT_EQ(lghazarosyan::get<3>(tuple1), 2);
    EXPECT_NE(lghazarosyan::get<0>(tuple1), tup);
    EXPECT_NE(lghazarosyan::get<1>(tuple1), tuple);
    EXPECT_NE(tuple, tup);
    EXPECT_NE(tuple1, tup);
    auto size = lghazarosyan::tuple_size_v<lghazarosyan::tuple<int, int, int>>;
    EXPECT_EQ(size, 3);
    auto is_equal = is_same_v<lghazarosyan::tuple_element_t<0, lghazarosyan::tuple<int, int, int>>, int>;
    EXPECT_TRUE(is_equal);
    auto is_equal_1 = is_same_v<lghazarosyan::tuple_element_t<4, lghazarosyan::tuple<int, int, int>>, void>;
    EXPECT_TRUE(is_equal_1);
    auto is_equal_2 = is_same_v<lghazarosyan::tuple_element_t<2, lghazarosyan::tuple<int, int, int>>, int>;
    EXPECT_TRUE(is_equal_2);
    auto index = lghazarosyan::tuple_element_index_v<int, lghazarosyan::tuple<int, int, int>>;
    EXPECT_EQ(index, 0);
    auto index1 = lghazarosyan::tuple_element_index_v<int, lghazarosyan::tuple<lghazarosyan::tuple<int, int, int>, lghazarosyan::tuple<int, int, int>, int, int>>;
    EXPECT_EQ(index1, 2);
    auto index2 = lghazarosyan::tuple_element_index_v<float, lghazarosyan::tuple<lghazarosyan::tuple<int, int, int>, lghazarosyan::tuple<int, int, int>, int, float>>;
    EXPECT_EQ(index2, 3);
    auto index3 = lghazarosyan::tuple_element_index_v<lghazarosyan::tuple<int, int, int>, lghazarosyan::tuple<lghazarosyan::tuple<int, int, int>, lghazarosyan::tuple<int, int, int>, int, float>>;
    EXPECT_EQ(index3, 0);
    auto index4 = lghazarosyan::tuple_element_index_v<double, lghazarosyan::tuple<lghazarosyan::tuple<int, int, int>, lghazarosyan::tuple<int, int, int>, int, float>>;
    EXPECT_EQ(index4, static_cast<std::size_t>(-1));
}
