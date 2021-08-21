#include "optional.hpp"

#include "gtest/gtest.h"
#include <vector>
#include <initializer_list>

using namespace lghazarosyan;

TEST(TestOptional, testWithBuildInType){
    optional<int> opt;
    EXPECT_EQ(opt, nullopt);
    EXPECT_FALSE(opt.has_value());
    EXPECT_FALSE(opt);
    opt = 7;
    EXPECT_TRUE(opt.has_value());
    EXPECT_EQ(opt.value(), 7);
    EXPECT_EQ(*opt, opt.value());
    opt.reset();
    EXPECT_FALSE(opt.has_value());
    try{
        opt.value();
        EXPECT_TRUE(false);
    }catch(...){

    }
    EXPECT_EQ(opt.value_or(1000), 1000);
    opt.emplace(10);
    EXPECT_EQ(opt.value(), 10);
    EXPECT_EQ(*opt, opt.value());

    optional<int> opt2(10);
    EXPECT_EQ(opt, opt2);
    opt2 = 11;
    EXPECT_NE(opt, opt2);
    opt2.reset();
    EXPECT_NE(opt, opt2);
    opt.reset();
    EXPECT_EQ(opt, opt2);
    opt = opt2;
    EXPECT_EQ(opt, opt2);
    auto opt3 = make_optional<int>(10);
    EXPECT_TRUE(opt3);
    EXPECT_EQ(*opt3, 10);
    optional<int> opt4(opt3);
    EXPECT_EQ(opt3, opt4);

}

TEST(TestOptional, testWithComplexType){
    optional<std::vector<int>> optVec(5, 10);
    EXPECT_TRUE(optVec.has_value());
    optVec.reset();
    EXPECT_EQ(optVec, nullopt);
    EXPECT_FALSE(optVec.has_value());
    EXPECT_FALSE(optVec);

    optVec.emplace(std::initializer_list<int>{1,2,3,4,5,6});
    EXPECT_EQ(optVec->size(), 6);
    for (int i = 0; i < 6; ++i ){
        EXPECT_EQ((*optVec)[i], i+1);
    }

    auto optVec2 = make_optional<std::vector<int>>(5, 10);
    EXPECT_TRUE(optVec2);
    EXPECT_EQ(optVec2->size(), 5);
    optional<std::vector<int>> optVec3 = optVec2;
    EXPECT_EQ(optVec2, optVec3);
    optVec3 = nullopt;
    optional<std::vector<int>> optVec4 = std::vector<int>({1,2,3,4,5,6});
    EXPECT_EQ(optVec4->size(), 6);
    for (int i = 0; i < 6; ++i ){
        EXPECT_EQ((*optVec4)[i], i+1);
    }

    EXPECT_EQ(*optVec4, std::vector<int>({1,2,3,4,5,6}));
    EXPECT_EQ(optVec4.value(), std::vector<int>({1,2,3,4,5,6}));
    optVec4.reset();
    EXPECT_EQ(optVec4.value_or(std::initializer_list<int>{1,2,3,4,5}), std::vector<int>({1,2,3,4,5}));
    EXPECT_EQ(optional<std::vector<int>>(std::initializer_list<int>{1,2,3,4,5,6}).value(), std::vector<int>({1,2,3,4,5,6}));
    EXPECT_EQ(optional<std::vector<int>>(std::initializer_list<int>{1,2,3,4,5,6}).value_or(std::initializer_list<int>{1,2,3,4}), std::vector<int>({1,2,3,4,5,6}));
    EXPECT_EQ(optional<std::vector<int>>().value_or(std::initializer_list<int>{1,2,3,4}), std::vector<int>({1,2,3,4}));
}
