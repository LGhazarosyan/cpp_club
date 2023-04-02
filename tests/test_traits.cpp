#include "type_traits.hpp"
#include "value_traits.hpp"

#include "gtest/gtest.h"

using namespace lghazarosyan;

template <typename... Ts>
void func(Ts... args) {}

struct CallableTester {
	void operator()(bool, bool) {}

	void operator()(bool) {}

	int operator()(int) { return 0;}

};

TEST(TestValueTraits, testCallable) {
	EXPECT_TRUE( (is_callable_v<void, decltype(func<int>), int>) );
	EXPECT_TRUE ( (is_same_v<void, return_type_t<decltype(func<int>), int>>) );

	EXPECT_TRUE( (is_callable_v<void, decltype(func<int, int, int>), int, int, int>) );
	EXPECT_TRUE( (is_same_v<void, return_type_t<decltype(func<int, int, int>), int, int, int>>) );

	EXPECT_TRUE( (is_callable_v<void, decltype(func<int, int, int, int>), int, int, int, int>) );
	EXPECT_FALSE( (is_callable_v<void, CallableTester, int>) );
	EXPECT_TRUE( (is_callable_v<int, CallableTester, int>) );
	EXPECT_FALSE( (is_callable_v<int, CallableTester, bool>) );

	auto foo = [](int, int){
		return true;
	};

	EXPECT_TRUE( (is_callable_v<bool, decltype(foo), int, int>) );
	EXPECT_FALSE( (is_callable_v<bool, decltype(foo), int>) );	
}

class A {};
class B : public A{};
class C : private A{};
class D : protected A {};

TEST(TestValueTraits, testIsBase) {
	EXPECT_FALSE( (is_base_of_v<int, float>) );
	EXPECT_TRUE( (is_base_of_v<A, B>) );
	EXPECT_TRUE( (is_base_of_v<A, C>) );
	EXPECT_TRUE( (is_base_of_v<A, D>) );
} 

