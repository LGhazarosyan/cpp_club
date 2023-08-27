#include "unique_ptr.hpp"

#include <gtest/gtest.h>

struct A {
	int a;
	int b;
	double c;
	A(int aa, int bb, double dd): a(aa), b(bb), c(dd){};
	bool operator == (const A& other) const {
		return (a == other.a) && (b == other.b) && (c == other.c);
	}
};

TEST(UniquePtrTest, testUniquePtr) {
	auto unique = lghazarosyan::make_unique<A>(10, 10, 10.0);
	A value = *unique;
	EXPECT_EQ(value, A(10, 10, 10.0) );
	EXPECT_EQ(unique->a, 10);

	A* ptr = unique.get();
	EXPECT_EQ(*ptr,value);

	A* ptr1 = unique.release();
	EXPECT_EQ(ptr, ptr1);
	delete ptr1;

	EXPECT_FALSE(unique);

	unique = lghazarosyan::make_unique<A>(5, 19, 5.0);
	unique.reset();
	EXPECT_FALSE(unique);
	
	auto unique1 = std::move(unique);
	EXPECT_FALSE(unique);
	EXPECT_FALSE(unique1);

	unique = lghazarosyan::make_unique<A>(5, 19, 5.0);
	unique1 = std::move(unique);
	EXPECT_FALSE(unique);
	EXPECT_TRUE(unique1);
	EXPECT_EQ(*unique1, A(5,19, 5.0));
}
