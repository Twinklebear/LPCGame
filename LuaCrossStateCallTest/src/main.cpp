#include <iostream>
#include <string>
#include "luacscript.h"

template<class T>
std::ostream& print(std::ostream &os, const T &t){
	return os << t << std::endl;
}

template<class T, class... Args>
std::ostream& print(std::ostream &os, const T &t, const Args&... args){
	os << t << ", ";
	return print (os, args...);
}

template<class T>
void PairTest(T val){
	val.second(val.first);
}

template<class T, class... Args>
void PairTest(T val, Args... args){
	val.second(val.first);
	PairTest(args...);
}

void showStr(const std::string s){
	std::cout << s << std::endl;
}

void showD(const double d){
	std::cout << d << std::endl;
}

int main(int argc, char** argv){
    print(std::cout, 10, "hello", "chris", 104012.10);

    std::string str = "weehaawW";
    auto p1 = std::make_pair(str, showStr);
	auto p2 = std::make_pair(10.5, showD);
	PairTest(p1, p2);

    //The two scripts we'll be using to test this
    //LuaCScript sA("../res/scripts/scriptA.lua");
    //LuaCScript sB("../res/scripts/scriptB.lua");
    return 0;
}