#include<iostream>
#include<string>
#include"URL_TYPE.hpp"
#include"URL.hpp"

URL::URL(uint16_t L = 0, std::string A = "", URL_TYPE T = URL_TYPE::NO)
    : level{L}, 
	address{A}, 
	type{T} {}

const char *URL::getAddress() { return address.c_str(); }

void URL::print() { std::cout << address << std::endl; }
