#include <iostream>
#include "BigInt.h"
#include "ModularExp.h"

using namespace ModularExp;

int main(){
    BigInt a = BigInt("999900283772999222876655999002837729992228766559");
    BigInt b = BigInt("12288919293783828829"); 
    BigInt c = BigInt("28888888292920209");
    std::cout << "a: ";
    a.print();
    std::cout << "b: ";
    b.print();
    std::cout << "c: ";
    c.print();
    BigInt d = fastExp(a, b, c);
    std::cout << std::endl;
    std::cout << "(a^b)%c: ";
    d.print();
}
