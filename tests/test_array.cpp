#include <iostream>
#include "reverse_iterator.hpp"
#include <vector>
#include <list>
#include <algorithm>
#include <forward_list>
#include "array.hpp"
#include <array>
class A{};

class B: public A{};

class C{
    public:
    C(){
    }
    C(const C&) = delete;
    C(C&&) = delete;
};
int main(){
    std::cout<<lghazarosyan::is_base_of_v<const A&,B>;
    lghazarosyan::array<int ,5> arr = {1,2,3,4,5};
    for (const auto & i: arr){
        std::cout<<i<<std::endl;
    }
    auto rb = arr.rbegin();
    auto re = arr.rend();
    std::for_each(rb,re,[](const auto &i){
        std::cout<<i<<std::endl;
    });

    arr.fill(5);

    for (const auto & i: arr){
        std::cout<<i<<std::endl;
    }

    arr.size();
    arr.back();
    arr.front();
    arr.at(2);
    arr[2];
    arr.empty();
    arr.data();
    arr.max_size();
    auto arr2 =arr;
    arr = arr2;

    std::list<int> l{1,2,3};
    auto rl = lghazarosyan::reverse_iterator(l.end());
    auto rit = arr.rbegin();
    ++rit;
    --rit;
    rit++;
    rit--;
    rit+=3;
    rit-=2;
    rit+2;
    rit-3;
    rit[2];
    auto crit = arr.crbegin();
    crit = rit;
    *crit;
    rb[5];
    lghazarosyan::array<C, 6> arro;


}